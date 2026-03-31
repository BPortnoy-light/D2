#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DashboardControl.h"
#include "AccountStorage.h"

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // setup mainwindow
    ui->setupUi(this);

    // menu bar hidden before login
    ui->menubar->setVisible(false);

    // connecting stacked widget with main window page handler
    connect(ui->vendorDashboardSW, &QStackedWidget::currentChanged,this, &MainWindow::onPageChange);

    database=QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath()+"/OurDatabaseName.db";

}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}


// Page change handler
void MainWindow::onPageChange(int index)
{

    QWidget* current = ui->vendorDashboardSW->widget(index);

    if (current == ui->dashboardPage)
    {
        onDashboard(index);
    }
    else if (current == ui->schedulePage)
    {
        loadMarketSchedule();
    }
    else if (current == ui->operatorHomePage)
    {
        onOperatorHomePage(index);
    }
    else if (current == ui->sysAdminHomePage)
    {
        onSysAdminHomePage(index);
    }


}




// Login Fuctions

// Loginbutton
// TODO: ADD SQL FUNCTIONALITY
void MainWindow::on_loginButton_clicked()
{
    // clear active user
    ActiveUser=nullptr;

    QString username = ui->usernameInput->text().trimmed();

    // TODO: REPLACE THIS WITH DATABASE QUERY FOR USERNAME
    // check if text is in accounts
    if(username.isEmpty())
    {
        QMessageBox::warning(this,"Login","Invalid username");
        return;
    }
    // refresh handle to opened database
    database = QSqlDatabase::database();

    if (!database.isOpen())
    {
        QMessageBox::warning(this,"Login","Database is not open");
        return;
    }
    // TODO: CHANGE THIS TO BUILD FROM SQL
    // build and set current user
    ActiveUser=this->accounts.getUser(username.toStdString());
    //std::cout << ActiveUser->displayPermission()<< std::endl;
    if (ActiveUser == nullptr)
    {
        QMessageBox::warning(this,"Login","Failed to load user");
        return;
    }
    switch (ActiveUser->getPermission())
        {
            case 0: // vendor
                // change page and make appropriate options visible and enabled
                ui->vendorDashboardSW->setCurrentWidget(ui->dashboardPage);
                ui->menubar->setVisible(true);
                ui->menuVendor->setEnabled(true);
                ui->menuOperator->setDisabled(true);
                ui->menuSys_Admin->setDisabled(true);
                break;

            case 1: // operator
                ui->vendorDashboardSW->setCurrentWidget(ui->operatorHomePage);
                ui->menubar->setVisible(true);
                ui->menuVendor->setDisabled(true);
                ui->menuOperator->setEnabled(true);
                ui->menuSys_Admin->setDisabled(true);
                break;

            case 2: // admin
                ui->vendorDashboardSW->setCurrentWidget(ui->sysAdminHomePage);
                ui->menubar->setVisible(true);
                ui->menuSys_Admin->setEnabled(true);
                ui->menuOperator->setDisabled(true);
                ui->menuVendor->setDisabled(true);
                break;
        }

}

// REFRESH FUNCTIONS

// TODO: ADD SQL TO THIS
// refreshes vendor dashboard
void MainWindow::onDashboard(int index)
{
    Q_UNUSED(index);

    if(ActiveUser == nullptr)
    {
        return;
    }

    database = QSqlDatabase::database();
    if(!database.isOpen())
    {
        qDebug() << "Database is not open in onDashboard.";
        return;
    }

    Vendor* activeVendor = dynamic_cast<Vendor*>(ActiveUser);
    if(activeVendor == nullptr)
    {
        return;
    }
    // clear all tables
    ui->WLtableWidget->clear();
    ui->dashboardComplianceTableView->clear();
    ui->dashboardNotificationTableView->clear();
    ui->activeStallBookingTableView->clear();


    //Dashboard object: delete this when connect database
    DashboardControl dc;
    //Waitlist Table View - delete this
    /*
    ui->WLtableWidget->setHorizontalHeaderLabels({"Date", "Position"});
    ui->WLtableWidget->setRowCount(8);
    ui->WLtableWidget->setColumnCount(2);

    ui->WLtableWidget->setItem(0,0,new QTableWidgetItem("2026-05-03"));
    ui->WLtableWidget->setItem(0,1,new QTableWidgetItem("1"));

    ui->WLtableWidget->setItem(1,0,new QTableWidgetItem("2026-05-10"));
    ui->WLtableWidget->setItem(1,1,new QTableWidgetItem("2"));

    ui->WLtableWidget->setItem(2,0,new QTableWidgetItem("2026-05-17"));
    ui->WLtableWidget->setItem(2,1,new QTableWidgetItem("1"));

    ui->WLtableWidget->setItem(3,0,new QTableWidgetItem("2026-05-24"));
    ui->WLtableWidget->setItem(3,1,new QTableWidgetItem("3"));
    */

    // Populate username, category, phone, email, mailing from active user
    ui->vendorNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));
    ui->BICategoryLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getCategory()));
    ui->BIOwnerNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));
    ui->BIEmailLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getEmail()));
    ui->BIPhoneLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getPhone()));
    ui->BIMailingLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getMailing()));


    // Populate Compliance Docs table view
    // setup table with headers
    QTableWidget *complianceDocumentsTable = ui->dashboardComplianceTableView;
    complianceDocumentsTable->setColumnCount(3);
    complianceDocumentsTable->setHorizontalHeaderLabels({"Document Type","Status","Exp Date"});

    // PLACEHOLDER -- INSERT SQL CALL HERE
    QSqlQuery userComplianceDocumentsQuery;
    userComplianceDocumentsQuery.prepare("SELECT TYPE, STATUS, EXPIRATIONDATE FROM COMPLIANCEDOCUMENTATION WHERE USERNAME=:username");
    userComplianceDocumentsQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));

    int row = 0;

    if(!userComplianceDocumentsQuery.exec())
    {
        qDebug() << "Compliance query failed:" << userComplianceDocumentsQuery.lastError().text();
    }

    while (userComplianceDocumentsQuery.next())
    {
        complianceDocumentsTable->insertRow(row);

        complianceDocumentsTable->setItem(row, 0, new QTableWidgetItem(userComplianceDocumentsQuery.value(0).toString()));
        complianceDocumentsTable->setItem(row, 1, new QTableWidgetItem(userComplianceDocumentsQuery.value(1).toString()));
        complianceDocumentsTable->setItem(row, 2, new QTableWidgetItem(userComplianceDocumentsQuery.value(2).toString()));
        row++;
    }

    // Setup Waitlist table view
    QTableWidget *waitlistTable = ui->WLtableWidget;
    waitlistTable->setColumnCount(3);
    waitlistTable->setHorizontalHeaderLabels({"Week Number","Type","Queue Position"});

    // Populate Waitlist table view
    // PLACEHOLDER -- INSERT SQL CALL HERE
    QSqlQuery waitlistPopulateQuery;
    waitlistPopulateQuery.prepare("SELECT WEEK_ID, CATEGORY, POSITION FROM WAITLIST JOIN WAITLIST_ENTRY ON WAITLIST_ENTRY.WAITLIST_ID=WAITLIST.WAITLIST_ID JOIN VENDOR ON VENDOR.VENDOR_ID=WAITLIST_ENTRY.VENDOR_ID WHERE USERNAME=:username" );
    waitlistPopulateQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));

    row = 0;

    if(!waitlistPopulateQuery.exec())
    {
        qDebug() << "Waitlist query failed:" << waitlistPopulateQuery.lastError().text();
    }
    while (waitlistPopulateQuery.next())
    {
        waitlistTable->insertRow(row);

        waitlistTable->setItem(row, 0, new QTableWidgetItem(waitlistPopulateQuery.value(0).toString()));
        waitlistTable->setItem(row, 1, new QTableWidgetItem(waitlistPopulateQuery.value(1).toString()));
        waitlistTable->setItem(row, 2, new QTableWidgetItem(waitlistPopulateQuery.value(2).toString()));
        row++;
    }


    // Setup Active Bookings table view
    QTableWidget *activeBookingTable = ui->activeStallBookingTableView;
    activeBookingTable->setColumnCount(2);
    activeBookingTable->setHorizontalHeaderLabels({"Week Number","Category"});

    // Populate Active Bookings table view
    // PLACEHOLDER -- INSERT SQL CALL HERE
    QSqlQuery activeBookingPopulateQuery;
    activeBookingPopulateQuery.prepare("SELECT WEEK_ID, CATEGORY FROM BOOKINGREQUEST JOIN VENDOR ON VENDOR.VENDOR_ID=BOOKINGREQUEST.VENDOR_ID WHERE USERNAME=:username" );
    activeBookingPopulateQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));

    row = 0;

    if(!activeBookingPopulateQuery.exec())
    {
        qDebug() << "Active booking query failed:" << activeBookingPopulateQuery.lastError().text();
    }
    while (activeBookingPopulateQuery.next())
    {
        activeBookingTable->insertRow(row);

        activeBookingTable->setItem(row, 0, new QTableWidgetItem(activeBookingPopulateQuery.value(0).toString()));
        activeBookingTable->setItem(row, 1, new QTableWidgetItem(activeBookingPopulateQuery.value(1).toString()));
        row++;
    }


    // Setup Notification table view
    QTableWidget *notificationsTable = ui->dashboardNotificationTableView;
    notificationsTable->setColumnCount(1);
    notificationsTable->setHorizontalHeaderLabels({"Message"});

    // Populate Notification table view
    // PLACEHOLDER -- INSERT SQL CALL HERE
    QSqlQuery notificationPopulateQuery;
    notificationPopulateQuery.prepare("SELECT MESSAGE FROM NOTIFICATION JOIN VENDOR ON VENDOR.VENDOR_ID=NOTIFICATION.VENDOR_ID WHERE USERNAME=:username" );
    notificationPopulateQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));

    row = 0;

    while (notificationPopulateQuery.next())
    {
        notificationsTable->insertRow(row);

        notificationsTable->setItem(row, 0, new QTableWidgetItem(notificationPopulateQuery.value(0).toString()));
        row++;
    }
}


//TODO: OUTSOURCE QUERYBUILDING TO DATABASE MANAGER / DISPLAY REQUEST
void MainWindow::onOperatorHomePage(int index)
{
    Q_UNUSED(index);

    if (ActiveUser == nullptr)
    {
        return;
    }

    database = QSqlDatabase::database();
    if (!database.isOpen())
    {
        qDebug() << "Database is not open in onOperatorHomePage.";
        return;
    }

    ui->operatorVendorSelectList->clear();

    // update operatorNameLabel with operator username from active user
    ui->operatorNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));

    // update operatorVendorSelect list with usernames of all vendors in vendors table

    // build query -- this should likely by a display request
    QSqlQuery vendorUsernamequery(database);
    vendorUsernamequery.prepare("SELECT Username FROM Vendor ORDER BY Username");

    if(!vendorUsernamequery.exec())
    {
        qDebug() << "Vendor list query failed:" << vendorUsernamequery.lastError().text();
        return;
    }

    while(vendorUsernamequery.next())
    {
        QString username = vendorUsernamequery.value(0).toString();
        ui->operatorVendorSelectList->addItem(username);
    }

}


// Done
void MainWindow::onSysAdminHomePage(int index)
{
    // update sysAdminNameLabel with sysAdmin username from active user
    ui->sysAdminNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));
}



//Refresh Dashboardbutton
void MainWindow::on_refreshDashboardButton_clicked()
{
    onDashboard(2);
}


// TODO: add sql
//loadMarketschedule
void MainWindow::loadMarketSchedule()
{
    if(ActiveUser == nullptr)
    {
        return;
    }

    database = QSqlDatabase::database();
    if(!database.isOpen())
    {
        qDebug() << "Database is not open in loadMarketSchedule.";
        return;
    }

    Vendor* activeVendor = dynamic_cast<Vendor*>(ActiveUser);
    if(activeVendor == nullptr)
    {
        return;
    }

    QString myCategory = QString::fromStdString(activeVendor->getCategory());
    // table setup
    QTableWidget *marketScheduleTable=ui->marketTable;
    marketScheduleTable->clearContents();
    marketScheduleTable->setRowCount(0);
    marketScheduleTable->setColumnCount(3);
    marketScheduleTable->setHorizontalHeaderLabels({"Week Number","Available Spots","Category"});

    // Populate Market Schedule -- replace with sql function
    QSqlQuery marketSchedulePopulateQuery(database);
    marketSchedulePopulateQuery.prepare(R"(
        SELECT WeekID,
               CASE
                   WHEN :myCategory = 'Food' THEN
                       FoodCapacity - (
                           SELECT COUNT(*)
                           FROM Booking B
                           WHERE B.WeekID = MarketSchedule.WeekID
                             AND B.Category = 'Food'
                             AND B.Status = 'Booked'
                       )
                   ELSE
                       ArtisanCapacity - (
                           SELECT COUNT(*)
                           FROM Booking B
                           WHERE B.WeekID = MarketSchedule.WeekID
                             AND B.Category = 'Artisan'
                             AND B.Status = 'Booked'
                       )
               END AS AvailableSpots
        FROM MarketSchedule
        ORDER BY WeekID
    )");
    marketSchedulePopulateQuery.bindValue(":myCategory",QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getCategory()));

    int row = 0;
    if(!marketSchedulePopulateQuery.exec())
    {
        qDebug() << "Market schedule query failed:" << marketSchedulePopulateQuery.lastError().text();
    }


    while (marketSchedulePopulateQuery.next())
    {
        marketScheduleTable->insertRow(row);

        marketScheduleTable->setItem(row, 0, new QTableWidgetItem(marketSchedulePopulateQuery.value(0).toString()));
        marketScheduleTable->setItem(row, 1, new QTableWidgetItem(marketSchedulePopulateQuery.value(1).toString()));
        marketScheduleTable->setItem(row, 2, new QTableWidgetItem(marketSchedulePopulateQuery.value(2).toString()));
        row++;
    }

    // table setup
    QTableWidget *MSActiveBookingTable=ui->ScheduleactiveBookingTable;
    MSActiveBookingTable->clearContents();
    MSActiveBookingTable->setRowCount(0);
    MSActiveBookingTable->setColumnCount(2);
    MSActiveBookingTable->setHorizontalHeaderLabels({"Week Number","Category"});

    // Populate Active Bookings -- replace with sql function
    QSqlQuery MSactiveBookingPopulateQuery(database);
    MSactiveBookingPopulateQuery.prepare(
        "SELECT WeekID, Category "
        "FROM Booking "
        "WHERE Username = :username AND Status = 'Booked' "
        "ORDER BY WeekID"
    );
    MSactiveBookingPopulateQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));


    row = 0;
    if(!MSactiveBookingPopulateQuery.exec())
    {
        qDebug() << "Schedule active booking query failed:" << MSactiveBookingPopulateQuery.lastError().text();
    }

    while (MSactiveBookingPopulateQuery.next())
    {
        MSActiveBookingTable->insertRow(row);

        MSActiveBookingTable->setItem(row, 0, new QTableWidgetItem(MSactiveBookingPopulateQuery.value(0).toString()));
        MSActiveBookingTable->setItem(row, 1, new QTableWidgetItem(MSactiveBookingPopulateQuery.value(1).toString()));
        row++;
    }


}

//BookstallButton
void MainWindow::on_bookButton_clicked()
{
    int row = ui->marketTable->currentRow();

    if(row < 0)
    {
        QMessageBox::warning(this,"Booking","Select a market date");
        return;
    }

    QMessageBox::information(this,"Booking","Stall booked successfully");

    ui->vendorDashboardSW->setCurrentIndex(2);
}

//Join waitlistbutton
void MainWindow::on_waitlistButton_clicked()
{
    int row = ui->marketTable->currentRow();

    if(row < 0)
    {
        QMessageBox::warning(this,"Waitlist","Select market date");
        return;
    }

    QMessageBox::information(this,"Waitlist","Added to waitlist");
}

//Cancel bookingbutton
void MainWindow::on_cancelBookingButton_clicked()
{
    QMessageBox::information(this,"Cancel","Booking cancelled");
}

//Cancel waitlistbutton
void MainWindow::on_cancelWaitlistButton_clicked()
{
    QMessageBox::information(this,"Waitlist","Removed from waitlist");
}


// Menubar functions
void MainWindow::on_actionDashboard_triggered()
{
    ui->vendorDashboardSW->setCurrentWidget(ui->dashboardPage);
}
void MainWindow::on_actionMarket_Schedule_triggered()
{
    ui->vendorDashboardSW->setCurrentWidget(ui->schedulePage);
}
void MainWindow::on_actionVendorSelect_triggered()
{
    ui->vendorDashboardSW->setCurrentWidget(ui->operatorHomePage);
}

// logout
void MainWindow::on_actionLogout_triggered()
{
    // clear active user reset menu bar to invisivle
    ActiveUser=nullptr;
    onBehalfVendor=nullptr;
    ui->menubar->setVisible(false);
    ui->vendorDashboardSW->setCurrentWidget(ui->loginPage);
}

void MainWindow::on_actionLogout_2_triggered()
{
    ActiveUser=nullptr;
    onBehalfVendor=nullptr;
    ui->menubar->setVisible(false);
    ui->vendorDashboardSW->setCurrentWidget(ui->loginPage);
}
void MainWindow::on_actionLogout_3_triggered()
{
    ActiveUser=nullptr;
    onBehalfVendor=nullptr;
    ui->menubar->setVisible(false);
    ui->vendorDashboardSW->setCurrentWidget(ui->loginPage);
}
