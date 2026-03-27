#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DatabaseManager
{
public:
    static DatabaseManager& instance();

    bool initialize(const QString& dbPath);

    bool createBooking(const QString& username, int weekId);
    bool cancelBooking(const QString& username, int weekId);
    bool removeFromWaitlist(const QString& username, int weekId);

private:
    DatabaseManager();
    ~DatabaseManager();

    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    QSqlDatabase db;

    bool openDatabase(const QString& dbPath);
    bool createTables();
    bool seedDefaultDataIfEmpty();

    bool executeSqlFile(const QString& filePath);
    bool userTableIsEmpty();

    QString getVendorCategory(const QString& username);
    bool vendorAlreadyBooked(const QString& username);
    int countActiveBookingsForWeekCategory(int weekId, const QString& category);
    int getCapacityForWeekCategory(int weekId, const QString& category);

    bool addBookingRequest(const QString& username, int weekId, const QString& category, int& requestIdOut);
    bool addBooking(const QString& username, int weekId, const QString& category);
    bool addToWaitlist(int weekId, const QString& category, int requestId);

    bool promoteFirstWaitlistedVendor(int weekId, const QString& category);
    int nextWaitlistPosition(int weekId, const QString& category);
};

#endif // DATABASEMANAGER_H