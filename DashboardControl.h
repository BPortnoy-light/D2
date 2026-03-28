#ifndef DASHBOARDCONTROL_H
#define DASHBOARDCONTROL_H
#include "MarketStall.h"
#include "Vendor.h"
//#include "MarketDay.h"
#include <string>
#include <vector>
/*
Purpose: 
Control Dashboard.
recieves view requests from dashoboard and handles by requesting from storage

*/

class DashboardControl
{
    public:
        void updateDashboard();
        void createViewRequest();

        // get BI from vendor storage object or vendor proxy
        std::string getBIName();
        std::string getBIOwnerName();
        std::string getBIEmail();
        std::string getBIPhone();
        std::string getBIMailing();
        std::string getBICategory();

        // add other getters
        std::vector<std::string> getBookings();
        std::vector<std::string> getNotifications();
};

#endif
