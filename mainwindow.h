#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "AccountStorage.h"
#include "User.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // refresh functions
    void onPageChange(int index);

    // detect if on dashboard page
    void onDashboard(int index);
    void onOperatorHomePage(int index);
    void onSysAdminHomePage(int index);

    void loadMarketSchedule();

private:
    Ui::MainWindow *ui;
    // Track Active User
    User* ActiveUser;
    Vendor* onBehalfVendor;

    // create accounts storage
    AccountStorage accounts;

    // create database instance
    QSqlDatabase database;

// button actions go here
private slots:

    void on_loginButton_clicked();

    void on_bookButton_clicked();

    void on_waitlistButton_clicked();

    void on_cancelBookingButton_clicked();

    void on_cancelWaitlistButton_clicked();

    void on_refreshDashboardButton_clicked();



//
    void on_actionDashboard_triggered();
    void on_actionMarket_Schedule_triggered();
    void on_actionVendorSelect_triggered();
    void on_actionLogout_triggered();
    void on_actionLogout_2_triggered();
    void on_actionLogout_3_triggered();


};
#endif // MAINWINDOW_H
