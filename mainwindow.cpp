#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../DashboardControl.h"
#include "AccountStorage.h"

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

    // connecting stacked widget with main window
    connect(ui->vendorDashboardSW, &QStackedWidget::currentChanged,this, &MainWindow::onDashboard);


}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}


// page change handler
void MainWindow::onPageChange(int index)
{
/*
    QWidget* current = ui->vendorDashboardSW->widget(index);

    if (current == ui->dashboardPage)
    {
        onDashboard(index);
    }
    else if (current == ui->schedulePage)
    {
        onMarketSchedule(index);
    }
    else if (current == ui->operatorHomePage)
    {
        onOperatorHomePage(index);
    }
    else if (current == ui->sysAdminHomePage)
    {
        onSysAdminHomePage(index);
    }
*/

}




// Login Fuctions

// Loginbutton
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


// decides what to show when on dashboard
void MainWindow::onDashboard(int index)
{
    if (index == 2)
    {
        //Dashboard Initial:
        DashboardControl dc;

        //Waitlist Table View
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
        // on navigation to page update this
        // on refresh update this

        // Bus info
        //ui->BIBusNameLabel->setText(QString::fromStdString(dc.getBIName()));
        ui->BICategoryLabel->setText(QString::fromStdString(dc.getBICategory()));
        ui->BIOwnerNameLabel->setText(QString::fromStdString(dc.getBIOwnerName()));
        ui->BIEmailLabel->setText(QString::fromStdString(dc.getBIEmail()));
        ui->BIPhoneLabel->setText(QString::fromStdString(dc.getBIPhone()));
        ui->BIMailingLabel->setText(QString::fromStdString(dc.getBIMailing()));

        // new fetch from active user object
        ui->vendorNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));
        ui->BICategoryLabel->setText(QString::fromStdString(ActiveUser->displayPermission()));
        ui->BIOwnerNameLabel->setText(QString::fromStdString(ActiveUser->getUsername()));
        ui->BIEmailLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getEmail()));
        ui->BIPhoneLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getPhone()));
        ui->BIMailingLabel->setText(QString::fromStdString(dynamic_cast<Vendor*>(ActiveUser)->getMailing()));


    }
    // Compliance Docs
    // if a food vendor
    if (index==2 )//&& vendor.category=="food")
    {
        // sets labels to empty initially
        //ui->CDBLStatusLabel->setText("Valid");
        //ui->CDBLExpDateLabel->setText("2026-10-01");
        //ui->CDLIStatusLabel->setText("Valid");
        //ui->CDLIExpDateLabel->setText("2026-10-01");
        //ui->CDFCStatusLabel->setText("Valid");
        //ui->CDFCExpDateLabel->setText("2026-10-01");
    }
    else //not food vendor hide elements they wont need
    {
        //ui->CDFCLabel->hide();
        //ui->CDFCStatusLabel->hide();
        //ui->CDFCExpDateLabel->hide();
    }

    // continue with dashboard display
    // call refresh function at the end to get real values from storage -- not implemented yet
}

//Refresh Dashboardbutton
void MainWindow::on_refreshDashboardButton_clicked()
{
    DashboardControl dc;

   //ui->BIBusNameLabel->setText(QString::fromStdString(dc.getBIName()));
    ui->BICategoryLabel->setText(QString::fromStdString(dc.getBICategory()));
    ui->BIOwnerNameLabel->setText(QString::fromStdString(dc.getBIOwnerName()));
}


//loadMarketschedule
void MainWindow::loadMarketSchedule()
{
    ui->marketTable->setColumnCount(3);
    ui->marketTable->setHorizontalHeaderLabels({"Date","Food Stalls","Artisan Stalls"});

    ui->marketTable->setRowCount(4);

    ui->marketTable->setItem(0,0,new QTableWidgetItem("2026-05-04"));
    ui->marketTable->setItem(0,1,new QTableWidgetItem("2"));
    ui->marketTable->setItem(0,2,new QTableWidgetItem("2"));

    ui->marketTable->setItem(1,0,new QTableWidgetItem("2026-05-11"));
    ui->marketTable->setItem(1,1,new QTableWidgetItem("2"));
    ui->marketTable->setItem(1,2,new QTableWidgetItem("2"));

    ui->marketTable->setItem(2,0,new QTableWidgetItem("2026-05-18"));
    ui->marketTable->setItem(2,1,new QTableWidgetItem("2"));
    ui->marketTable->setItem(2,2,new QTableWidgetItem("2"));

    ui->marketTable->setItem(3,0,new QTableWidgetItem("2026-05-25"));
    ui->marketTable->setItem(3,1,new QTableWidgetItem("2"));
    ui->marketTable->setItem(3,2,new QTableWidgetItem("2"));
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


// Menu functions
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
