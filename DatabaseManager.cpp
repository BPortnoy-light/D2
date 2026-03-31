/*
HintonMarket D2 – DatabaseManager (SQLite Integration)

This class is responsible for:
- Connecting to SQLite database
- Creating tables and seeding default data
- Handling all booking and waitlist operations

Business Rules Enforced:
1. Vendors can only have ONE active booking at a time
2. Maximum capacity per week:
   - 2 Food vendors
   - 2 Artisan vendors
3. Waitlist is FIFO (first-come, first-served)
4. Data persists between program runs

All operations update BOTH:
- SQLite database (persistent storage)
- In-memory system (via higher-level classes)
*/

#include "DatabaseManager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

//Constructor
DatabaseManager::DatabaseManager() {}

//Destructor ensures database is properly closed
DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();  //prevent resource leaks
    }
}

//Singleton instance (ensures only ONE database connection exists)
DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

// Initializes database:
// 1. Opens SQLite file
// 2. Creates tables if missing
// 3. Seeds default data ONLY if database is empty
bool DatabaseManager::initialize(const QString& dbPath)
{
    if (!openDatabase(dbPath)) {
        return false;
    }

    if (!createTables()) {
        return false;
    }

    if (!seedDefaultDataIfEmpty()) {
        return false;
    }

    qDebug() << "Database initialized successfully.";
    return true;
}

//Opens SQLite database (creates file if not exists)
bool DatabaseManager::openDatabase(const QString& dbPath)
{
    //Reuse existing connection if available
    if (QSqlDatabase::contains()) {
        db = QSqlDatabase::database();
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbPath);
    }

    //Attempt to open database
    if (!db.open()) {
        qDebug() << "Database open error:" << db.lastError().text();
        return false;
    }

    //Enable foreign key constraints (important for data integrity)
    QSqlQuery pragma(db);
    pragma.exec("PRAGMA foreign_keys = ON;");

    return true;
}

//Creates tables by executing schema.sql
bool DatabaseManager::createTables()
{
    return executeSqlFile("schema.sql");
}

//Inserts default data ONLY if database is empty
bool DatabaseManager::seedDefaultDataIfEmpty()
{
    if (!userTableIsEmpty()) {
        return true; //already populated
    }

    return executeSqlFile("seed.sql");
}

//Executes SQL script file (schema.sql or seed.sql)
bool DatabaseManager::executeSqlFile(const QString& filePath)
{
    QFile file(filePath);

    //Open SQL file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open SQL file:" << filePath;
        return false;
    }

    QTextStream in(&file);
    QString sql = in.readAll();  //read entire SQL script
    file.close();

    //Split into individual SQL statements
    QStringList statements = sql.split(';', Qt::SkipEmptyParts);

    //Execute each statement separately
    for (QString statement : statements) {
        statement = statement.trimmed();

        if (statement.isEmpty()) {
            continue;
        }

        QSqlQuery query(db);

        if (!query.exec(statement)) {
            qDebug() << "SQL error in file" << filePath;
            qDebug() << "Statement:" << statement;
            qDebug() << "Error:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

//Checks if User table is empty (used to avoid reseeding)
bool DatabaseManager::userTableIsEmpty()
{
    QSqlQuery query(db);

    if (!query.exec("SELECT COUNT(*) FROM User")) {
        qDebug() << "Count query failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() == 0;
    }

    return true;
}

//Retrieves vendor category (Food / Artisan)
QString DatabaseManager::getVendorCategory(const QString& username)
{
    QSqlQuery query(db);

    query.prepare("SELECT Category FROM Vendor WHERE Username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "getVendorCategory failed:" << query.lastError().text();
        return "";
    }

    if (query.next()) {
        return query.value(0).toString();
    }

    return "";
}

//Business rule: vendor can only have ONE active booking
bool DatabaseManager::vendorAlreadyBooked(const QString& username)
{
    QSqlQuery query(db);

    query.prepare("SELECT COUNT(*) FROM Booking WHERE Username = :username AND Status = 'Booked'");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "vendorAlreadyBooked failed:" << query.lastError().text();
        return true;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return true;
}

//Counts how many vendors are already booked for a specific week + category
int DatabaseManager::countActiveBookingsForWeekCategory(int weekId, const QString& category)
{
    QSqlQuery query(db);

    query.prepare("SELECT COUNT(*) FROM Booking WHERE WeekID = :weekId AND Category = :category AND Status = 'Booked'");
    query.bindValue(":weekId", weekId);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "countActiveBookingsForWeekCategory failed:" << query.lastError().text();
        return 0;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

//Retrieves capacity (2 Food OR 2 Artisan per week)
int DatabaseManager::getCapacityForWeekCategory(int weekId, const QString& category)
{
    QSqlQuery query(db);

    if (category == "Food") {
        query.prepare("SELECT FoodCapacity FROM MarketSchedule WHERE WeekID = :weekId");
    } else {
        query.prepare("SELECT ArtisanCapacity FROM MarketSchedule WHERE WeekID = :weekId");
    }

    query.bindValue(":weekId", weekId);

    if (!query.exec()) {
        qDebug() << "getCapacityForWeekCategory failed:" << query.lastError().text();
        return 0;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}

//Creates a booking request record
bool DatabaseManager::addBookingRequest(const QString& username, int weekId, const QString& category, int& requestIdOut)
{
    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO BookingRequest (Username, WeekID, Category, Status, RequestTime)
        VALUES (:username, :weekId, :category, 'Pending', :requestTime)
    )");

    query.bindValue(":username", username);
    query.bindValue(":weekId", weekId);
    query.bindValue(":category", category);
    query.bindValue(":requestTime", QDateTime::currentDateTime().toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "addBookingRequest failed:" << query.lastError().text();
        return false;
    }

    requestIdOut = query.lastInsertId().toInt();
    return true;
}

//Inserts confirmed booking
bool DatabaseManager::addBooking(const QString& username, int weekId, const QString& category)
{
    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO Booking (Username, WeekID, Category, Status)
        VALUES (:username, :weekId, :category, 'Booked')
    )");

    query.bindValue(":username", username);
    query.bindValue(":weekId", weekId);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "addBooking failed:" << query.lastError().text();
        return false;
    }

    return true;
}

//Finds next position in waitlist queue (FIFO)
int DatabaseManager::nextWaitlistPosition(int weekId, const QString& category)
{
    QSqlQuery query(db);

    query.prepare("SELECT COALESCE(MAX(Position), 0) + 1 FROM Waitlist WHERE WeekID = :weekId AND Category = :category");
    query.bindValue(":weekId", weekId);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "nextWaitlistPosition failed:" << query.lastError().text();
        return 1;
    }

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 1;
}

//Adds vendor to waitlist queue
bool DatabaseManager::addToWaitlist(int weekId, const QString& category, int requestId)
{
    const int position = nextWaitlistPosition(weekId, category);

    QSqlQuery query(db);

    query.prepare(R"(
        INSERT INTO Waitlist (WeekID, Category, RequestID, Position)
        VALUES (:weekId, :category, :requestId, :position)
    )");

    query.bindValue(":weekId", weekId);
    query.bindValue(":category", category);
    query.bindValue(":requestId", requestId);
    query.bindValue(":position", position);

    if (!query.exec()) {
        qDebug() << "addToWaitlist failed:" << query.lastError().text();
        return false;
    }

    //Update request status
    QSqlQuery update(db);
    update.prepare("UPDATE BookingRequest SET Status = 'Waitlisted' WHERE RequestID = :requestId");
    update.bindValue(":requestId", requestId);
    update.exec();

    return true;
}

//Main booking logic
bool DatabaseManager::createBooking(const QString& username, int weekId)
{
    QString category = getVendorCategory(username);

    if (category.isEmpty()) {
        qDebug() << "Vendor not found.";
        return false;
    }

    if (vendorAlreadyBooked(username)) {
        qDebug() << "Vendor already has one active booking.";
        return false;
    }

    int requestId = -1;

    if (!addBookingRequest(username, weekId, category, requestId)) {
        return false;
    }

    int bookedCount = countActiveBookingsForWeekCategory(weekId, category);
    int capacity = getCapacityForWeekCategory(weekId, category);

    //If space available to book
    if (bookedCount < capacity) {

        if (!addBooking(username, weekId, category)) {
            return false;
        }

        QSqlQuery update(db);
        update.prepare("UPDATE BookingRequest SET Status = 'Approved' WHERE RequestID = :requestId");
        update.bindValue(":requestId", requestId);
        update.exec();

        qDebug() << "Booking created.";
        return true;
    }

    //Otherwise to waitlist
    if (!addToWaitlist(weekId, category, requestId)) {
        return false;
    }

    qDebug() << "No space. Vendor added to waitlist.";
    return true;
}

//Promotes first vendor in waitlist (FIFO)
bool DatabaseManager::promoteFirstWaitlistedVendor(int weekId, const QString& category)
{
    QSqlQuery query(db);

    query.prepare(R"(
        SELECT W.RequestID, BR.Username
        FROM Waitlist W
        JOIN BookingRequest BR ON W.RequestID = BR.RequestID
        WHERE W.WeekID = :weekId AND W.Category = :category
        ORDER BY W.Position ASC
        LIMIT 1
    )");

    query.bindValue(":weekId", weekId);
    query.bindValue(":category", category);

    if (!query.exec()) {
        qDebug() << "promoteFirstWaitlistedVendor select failed:" << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        return true; // no one in waitlist
    }

    int requestId = query.value(0).toInt();
    QString username = query.value(1).toString();

    //Create booking for next vendor
    if (!addBooking(username, weekId, category)) {
        return false;
    }

    //Update request status
    QSqlQuery updateRequest(db);
    updateRequest.prepare("UPDATE BookingRequest SET Status = 'Approved' WHERE RequestID = :requestId");
    updateRequest.bindValue(":requestId", requestId);
    updateRequest.exec();

    //Remove from waitlist
    QSqlQuery deleteWait(db);
    deleteWait.prepare("DELETE FROM Waitlist WHERE RequestID = :requestId");
    deleteWait.bindValue(":requestId", requestId);
    deleteWait.exec();

    //Shift queue positions
    QSqlQuery shift(db);
    shift.prepare(R"(
        UPDATE Waitlist
        SET Position = Position - 1
        WHERE WeekID = :weekId AND Category = :category AND Position > 1
    )");

    shift.bindValue(":weekId", weekId);
    shift.bindValue(":category", category);
    shift.exec();

    qDebug() << "First waitlisted vendor promoted.";
    return true;
}

//Cancels booking and promotes next vendor
bool DatabaseManager::cancelBooking(const QString& username, int weekId)
{
    QString category = getVendorCategory(username);

    if (category.isEmpty()) {
        return false;
    }

    QSqlQuery query(db);

    query.prepare(R"(
        UPDATE Booking
        SET Status = 'Cancelled'
        WHERE Username = :username AND WeekID = :weekId AND Status = 'Booked'
    )");

    query.bindValue(":username", username);
    query.bindValue(":weekId", weekId);

    if (!query.exec()) {
        qDebug() << "cancelBooking failed:" << query.lastError().text();
        return false;
    }

    if (query.numRowsAffected() <= 0) {
        qDebug() << "No active booking found to cancel.";
        return false;
    }

    return promoteFirstWaitlistedVendor(weekId, category);
}

//Removes vendor from waitlist
bool DatabaseManager::removeFromWaitlist(const QString& username, int weekId)
{
    QString category = getVendorCategory(username);

    if (category.isEmpty()) {
        return false;
    }

    QSqlQuery find(db);

    find.prepare(R"(
        SELECT W.RequestID, W.Position
        FROM Waitlist W
        JOIN BookingRequest BR ON W.RequestID = BR.RequestID
        WHERE BR.Username = :username
          AND W.WeekID = :weekId
          AND W.Category = :category
        LIMIT 1
    )");

    find.bindValue(":username", username);
    find.bindValue(":weekId", weekId);
    find.bindValue(":category", category);

    if (!find.exec()) {
        qDebug() << "removeFromWaitlist find failed:" << find.lastError().text();
        return false;
    }

    if (!find.next()) {
        qDebug() << "Vendor not found in waitlist.";
        return false;
    }

    int requestId = find.value(0).toInt();
    int removedPosition = find.value(1).toInt();

    //Remove entry
    QSqlQuery del(db);
    del.prepare("DELETE FROM Waitlist WHERE RequestID = :requestId");
    del.bindValue(":requestId", requestId);

    if (!del.exec()) {
        qDebug() << "removeFromWaitlist delete failed:" << del.lastError().text();
        return false;
    }

    //Update request status
    QSqlQuery updateRequest(db);
    updateRequest.prepare("UPDATE BookingRequest SET Status = 'Removed' WHERE RequestID = :requestId");
    updateRequest.bindValue(":requestId", requestId);
    updateRequest.exec();

    //Shift queue positions
    QSqlQuery shift(db);
    shift.prepare(R"(
        UPDATE Waitlist
        SET Position = Position - 1
        WHERE WeekID = :weekId
          AND Category = :category
          AND Position > :removedPosition
    )");

    shift.bindValue(":weekId", weekId);
    shift.bindValue(":category", category);
    shift.bindValue(":removedPosition", removedPosition);

    if (!shift.exec()) {
        qDebug() << "removeFromWaitlist shift failed:" << shift.lastError().text();
        return false;
    }

    return true;
}
