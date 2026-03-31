#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DashboardControl.h"
#include "AccountStorage.h"
#include "Waitlist.h"

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

    // operator vendor select button press
    connect(ui->operatorSelectVendorButton, &QPushButton::clicked,this, &MainWindow::on_operatorSelectVendorButton_clicked);

}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
    //delete ActiveUser;
    //delete onBehalfVendor;
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

    QString username = ui->usernameInput->text();

    // TODO: REPLACE THIS WITH DATABASE QUERY FOR USERNAME
    // check if text is in accounts
    if(!(this->accounts.findUsername(username.toStdString())))
    {
        QMessageBox::warning(this,"Login","Invalid username");
        return;
    }
    // TODO: CHANGE THIS TO BUILD FROM SQL
    // build and set current user
    ActiveUser=this->accounts.getUser(username.toStdString());
    //std::cout << ActiveUser->displayPermission()<< std::endl;

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
    // clear all tables
    ui->WLtableWidget->clear();
    ui->dashboardComplianceTableView->clear();
    ui->dashboardNotificationTableView->clear();
    ui->activeStallBookingTableView->clear();


    //Dashboard object: delete this when connect database
    DashboardControl dc;

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

    while (userComplianceDocumentsQuery.next())
    {
        complianceDocumentsTable->insertRow(row);

        complianceDocumentsTable->setItem(row, 0, new QTableWidgetItem(userComplianceDocumentsQuery.value(0).toString()));
        complianceDocumentsTable->setItem(row, 1, new QTableWidgetItem(userComplianceDocumentsQuery.value(1).toString()));
        complianceDocumentsTable->setItem(row, 2, new QTableWidgetItem(userComplianceDocumentsQuery.value(2).toString()));
        row++;
    }

    // Setup Waitlist table view
    QTableWidget *waitlistTable = ui->WLtableWidget;dynamic_cast<Vendor*>(ActiveUser)->getCategory();
    waitlistTable->setColumnCount(3);
    waitlistTable->setHorizontalHeaderLabels({"Week Number","Type","Queue Position"});

    // Populate Waitlist table view
    // PLACEHOLDER -- INSERT SQL CALL HERE
    QSqlQuery waitlistPopulateQuery;
    waitlistPopulateQuery.prepare("SELECT WEEK_ID, CATEGORY, POSITION FROM WAITLIST JOIN WAITLIST_ENTRY ON WAITLIST_ENTRY.WAITLIST_ID=WAITLIST.WAITLIST_ID JOIN VENDOR ON VENDOR.VENDOR_ID=WAITLIST_ENTRY.VENDOR_ID WHERE USERNAME=:username" );
    waitlistPopulateQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));

    row = 0;

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
    //std::cout<<"this is running"<<std::endl;
    ui->operatorBrowseVendorsTable->clear();
    ui->operatorActiveWaitlistTable->clear();

    // update operatorNameLabel with operator username from active user
    ui->operatorNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));

    // update operatorVendorSelect list with usernames of all vendors in vendors table
    // tabble setup

    QTableWidget *browseVendorTable=ui->operatorBrowseVendorsTable;
    browseVendorTable->setColumnCount(3);
    browseVendorTable->setHorizontalHeaderLabels({"Vendor ID","Username","Category"});
    // build query -- replace with sql

    int row = 0;
    QSqlQuery vendorUsernameQuery("SELECT VENDOR_ID, USERNAME, CATEGORY FROM VENDOR");
    while(vendorUsernameQuery.next())
    {
        browseVendorTable->insertRow(row);

        browseVendorTable->setItem(row, 0, new QTableWidgetItem(vendorUsernameQuery.value(0).toString()));
        browseVendorTable->setItem(row, 1, new QTableWidgetItem(vendorUsernameQuery.value(1).toString()));
        browseVendorTable->setItem(row, 2, new QTableWidgetItem(vendorUsernameQuery.value(2).toString()));
        row++;
    }

    // tabble setup for active waitlists for vendor
    QTableWidget *operatorActiveWaitlitTable=ui->operatorActiveWaitlistTable;
    operatorActiveWaitlitTable->setColumnCount(3);
    operatorActiveWaitlitTable->setHorizontalHeaderLabels({"Week ID","Category","Position"});
    // this goes on operatorSelectButton press
    /*
    int row = 0;
    QSqlQuery operatorActiveWaitlistQuery;
    operatorActiveWaitlistQuery.prepare("SELECT WEEK_ID, CATEGORY, POSITION FROM WAITLIST JOIN WAITLIST_ENTRY ON WAITLIST_ENTRY.WAITLIST_ID=WAITLIST.WAITLIST_ID JOIN VENDOR ON VENDOR.VENDOR_ID=WAITLIST_ENTRY.VENDOR_ID WHERE USERNAME=:username" );
    operatorActiveWaitlistQuery.bindValue(":username",QString::fromStdString(onBehalfVendor->getUsername()));
    while(operatorActiveWaitlistQuery.next())
    {
        operatorActiveWaitlitTable->insertRow(row);

        operatorActiveWaitlitTable->setItem(row, 0, new QTableWidgetItem(operatorActiveWaitlistQuery.value(0).toString()));
        operatorActiveWaitlitTable->setItem(row, 1, new QTableWidgetItem(operatorActiveWaitlistQuery.value(1).toString()));
        operatorActiveWaitlitTable->setItem(row, 2, new QTableWidgetItem(operatorActiveWaitlistQuery.value(2).toString()));
        row++;
    }
    */
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
    // clear tables
    ui->ScheduleactiveBookingTable->clear();
    ui->marketTable->clear();

    // table setup
    QTableWidget *marketScheduleTable=ui->marketTable;
    marketScheduleTable->setColumnCount(3);
    marketScheduleTable->setHorizontalHeaderLabels({"Week Number","Stall ID","Category"});

    QTableWidget *MSActiveBookingTable=ui->ScheduleactiveBookingTable;
    MSActiveBookingTable->setColumnCount(2);
    MSActiveBookingTable->setHorizontalHeaderLabels({"Week Number","Category"});

    // if user permission is operator show different buttons and load differently
    // WILL CRASH AS ON BEHALF USER NOT YET SET TO LOAD
    if(ActiveUser->getPermission()==1)
    {
        // hide vendor book and cancel button and show label
        ui->scheduleBehalfActionLabel->setVisible(true);
        ui->scheduleBehalfActionVendorUsernameLabel->setVisible(true);
        ui->bookButton->setVisible(false);
        ui->cancelStallButton->setVisible(false);
        ui->bookOnBehalfButton->setVisible(true);
        ui->cancelOnBehalfButton->setVisible(true);

        // Populate Market Schedule -- replace with sql function
        QSqlQuery marketSchedulePopulateQuery;
        marketSchedulePopulateQuery.prepare("SELECT WEEK_ID, STALL_ID, CATEGORY FROM MARKETSTALL JOIN MARKETWEEK ON MARKETWEEK.WEEK_ID=MARKETSTALL.WEEK_ID WHERE MARKETSTALL.BOOKED=FALSE AND MARKETSTALL.CATEGORY=:myCategory" );
        marketSchedulePopulateQuery.bindValue(":myCategory",QString::fromStdString(onBehalfVendor->getCategory()));

        int row = 0;

        while (marketSchedulePopulateQuery.next())
        {
            marketScheduleTable->insertRow(row);

            marketScheduleTable->setItem(row, 0, new QTableWidgetItem(marketSchedulePopulateQuery.value(0).toString()));
            marketScheduleTable->setItem(row, 1, new QTableWidgetItem(marketSchedulePopulateQuery.value(1).toString()));
            marketScheduleTable->setItem(row, 2, new QTableWidgetItem(marketSchedulePopulateQuery.value(2).toString()));
            row++;
        }


        // Populate Active Bookings -- replace with sql function
        QSqlQuery MSactiveBookingPopulateQuery;
        MSactiveBookingPopulateQuery.prepare("SELECT WEEK_ID, CATEGORY FROM BOOKINGREQUEST JOIN VENDOR ON VENDOR.VENDOR_ID=BOOKINGREQUEST.VENDOR_ID WHERE USERNAME=:username" );
        MSactiveBookingPopulateQuery.bindValue(":username",QString::fromStdString(onBehalfVendor->getUsername()));


        row = 0;

        while (MSactiveBookingPopulateQuery.next())
        {
            MSActiveBookingTable->insertRow(row);

            MSActiveBookingTable->setItem(row, 0, new QTableWidgetItem(MSactiveBookingPopulateQuery.value(0).toString()));
            MSActiveBookingTable->setItem(row, 1, new QTableWidgetItem(MSactiveBookingPopulateQuery.value(1).toString()));
            row++;
        }



    }
    else
    {
        // this happens if user is vendor
        ui->scheduleBehalfActionLabel->setVisible(false);
        ui->scheduleBehalfActionVendorUsernameLabel->setVisible(false);
        ui->bookButton->setVisible(true);
        ui->cancelStallButton->setVisible(true);
        ui->bookOnBehalfButton->setVisible(false);
        ui->cancelOnBehalfButton->setVisible(false);

        // Populate Market Schedule -- replace with sql function
        QSqlQuery marketSchedulePopulateQuery;
        marketSchedulePopulateQuery.prepare("SELECT WEEK_ID, STALL_ID, CATEGORY FROM MARKETSTALL JOIN MARKETWEEK ON MARKETWEEK.WEEK_ID=MARKETSTALL.WEEK_ID WHERE MARKETSTALL.BOOKED=FALSE AND MARKETSTALL.CATEGORY=:myCategory" );
        marketSchedulePopulateQuery.bindValue(":myCategory",QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getCategory()));

        int row = 0;

        while (marketSchedulePopulateQuery.next())
        {
            marketScheduleTable->insertRow(row);

            marketScheduleTable->setItem(row, 0, new QTableWidgetItem(marketSchedulePopulateQuery.value(0).toString()));
            marketScheduleTable->setItem(row, 1, new QTableWidgetItem(marketSchedulePopulateQuery.value(1).toString()));
            marketScheduleTable->setItem(row, 2, new QTableWidgetItem(marketSchedulePopulateQuery.value(2).toString()));
            row++;
        }


        // Populate Active Bookings -- replace with sql function
        QSqlQuery MSactiveBookingPopulateQuery;
        MSactiveBookingPopulateQuery.prepare("SELECT WEEK_ID, CATEGORY FROM BOOKINGREQUEST JOIN VENDOR ON VENDOR.VENDOR_ID=BOOKINGREQUEST.VENDOR_ID WHERE USERNAME=:username" );
        MSactiveBookingPopulateQuery.bindValue(":username",QString::fromStdString(ActiveUser->getUsername()));


        row = 0;

        while (MSactiveBookingPopulateQuery.next())
        {
            MSActiveBookingTable->insertRow(row);

            MSActiveBookingTable->setItem(row, 0, new QTableWidgetItem(MSactiveBookingPopulateQuery.value(0).toString()));
            MSActiveBookingTable->setItem(row, 1, new QTableWidgetItem(MSactiveBookingPopulateQuery.value(1).toString()));
            row++;
        }
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
    //delete ActiveUser;
    //delete onBehalfVendor;
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

// add sql for building
void MainWindow::on_operatorSelectVendorButton_clicked()
{
    // setup vendor browse table
    // get selected row
    int row = ui->operatorBrowseVendorsTable->currentRow();

    // if no row selected do nothing
    if (row <0 )
    {
        return;
    }
    else
    {
        // get username from selected item
        QTableWidgetItem* extractedItem=ui->operatorBrowseVendorsTable->item(row, 1);
        QString extractedUsername = extractedItem->text();

        // sql query to find vendor with correct user name
        QSqlQuery getBehalfVendorQuery;
        getBehalfVendorQuery.prepare("SELECT BUSINESS_NAME, OWNER_NAME, EMAIL, PHONE, MAILING, CATEGORY, USERNAME FROM VENDOR WHERE USERNAME=:username");
        getBehalfVendorQuery.bindValue(":username", extractedUsername);

        // build partial vendor obj and set onBehalfVendor
        onBehalfVendor= new Vendor(getBehalfVendorQuery.value(0).toString().toStdString(), getBehalfVendorQuery.value(1).toString().toStdString(), getBehalfVendorQuery.value(2).toString().toStdString(),
                               getBehalfVendorQuery.value(3).toString().toStdString(),  getBehalfVendorQuery.value(4).toString().toStdString(), getBehalfVendorQuery.value(5).toString().toStdString(),
                               getBehalfVendorQuery.value(6).toString().toStdString());
        // Build and assign compliance vector from db

        // build and assign waitlist vector from db

        // build and assign notification vector from db



        // setup and populate waillist table
        QTableWidget *operatorWaitlistTable = ui->operatorActiveWaitlistTable;
        operatorWaitlistTable->setColumnCount(3);
        operatorWaitlistTable->setHorizontalHeaderLabels({"Week Number","Type","Queue Position"});

        // Populate Waitlist table
        // PLACEHOLDER -- INSERT SQL CALL HERE
        QSqlQuery operatorWaitlistPopulateQuery;
        operatorWaitlistPopulateQuery.prepare("SELECT WEEK_ID, CATEGORY, POSITION FROM WAITLIST JOIN WAITLIST_ENTRY ON WAITLIST_ENTRY.WAITLIST_ID=WAITLIST.WAITLIST_ID JOIN VENDOR ON VENDOR.VENDOR_ID=WAITLIST_ENTRY.VENDOR_ID WHERE USERNAME=:username" );
        operatorWaitlistPopulateQuery.bindValue(":username",extractedUsername);

        row = 0;

        while (operatorWaitlistPopulateQuery.next())
        {
            operatorWaitlistTable->insertRow(row);

            operatorWaitlistTable->setItem(row, 0, new QTableWidgetItem(operatorWaitlistPopulateQuery.value(0).toString()));
            operatorWaitlistTable->setItem(row, 1, new QTableWidgetItem(operatorWaitlistPopulateQuery.value(1).toString()));
            operatorWaitlistTable->setItem(row, 2, new QTableWidgetItem(operatorWaitlistPopulateQuery.value(2).toString()));
            row++;
        }
    }


}

// navigates to market schedule page
void MainWindow::on_operatorManageStallButton_clicked()
{
    ui->vendorDashboardSW->setCurrentWidget(ui->schedulePage);
}


// leave waitlist buttons for dashboard
// user selects row off waitlist to leave then clicks this button
// button should 1. remove user from waitlist(update active user strucutre waitlist) 2. update Waitlist structure in database 3. update Stall in database (set booked as false) 3. notificiation that operation is complete
void MainWindow::on_vendorLeaveWaitlist_clicked()
{
    // check to see if roww has been selected {"Week Number","Type","Queue Position"}
    int selectedRow = ui->WLtableWidget->currentRow();

    // if no row selected do nothing
    if (selectedRow <0 )
    {
        return;
    }
    else
    {
        // extract
        QTableWidgetItem* extractedItem=ui->WLtableWidget->item(selectedRow, 0);
        int extractedWeek = extractedItem->text().toInt();

        extractedItem=ui->WLtableWidget->item(selectedRow, 1);
        QString extractedCategory = extractedItem->text();

        extractedItem=ui->WLtableWidget->item(selectedRow, 2);
        QString extractedPosition = extractedItem->text();

        // remove waitlist from vendors joined waitlist (active user structure)
        // find correct waitlist in joined waitlists
        Waitlist* waitlistToEdit = dynamic_cast<Vendor*>(ActiveUser)->findWaitlist(extractedWeek, extractedCategory.toStdString());

        // remove waitlist from it
        //std::string username, int stall, std::string week
        extractedItem=ui->WLtableWidget->item(selectedRow, 0);
        std::string extractedWeekStr = extractedItem->text().toStdString();

        // **PLACEHOLDER VALUE FOR STALL** -- need to figure out how to extract stall
        waitlistToEdit->removeBookRequest(ActiveUser->getUsername(),2,extractedWeekStr);

        // INSERRT SQL UPDATE FOR CHANGED STRUCTURES


        // geneerate cancelation notification and add to notification struct

    }
}

