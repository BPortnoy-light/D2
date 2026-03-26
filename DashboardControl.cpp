#include "DashboardControl.h"
#include "MarketStall.h"
#include "Vendor.h"
//#include "MarketDay.h"
#include <string>

// get BI from vendor storage object or vendor proxy
std::string DashboardControl:: getBIName()
{
    return "vendor.BIname";
}

std::string DashboardControl:: getBIOwnerName()
{
    return "vendor.ownerName";
}

std::string DashboardControl:: getBIEmail()
{
    return "vendor.email";
}

std::string DashboardControl:: getBIPhone()
{
    return "vendor.phone";
}

std::string DashboardControl:: getBIMailing()
{
    return "vendor.mailing";
}

std::string DashboardControl:: getBICategory()
{
    return "vendor.category";
}

// need functions for bookings, notifications
std::vector<std::string> DashboardControl::getBookings()
{
    std::vector<std::string> bookings;

    bookings.push_back("2026-05-03");
    bookings.push_back("2026-05-17");

    return bookings;
}


std::vector<std::string> DashboardControl::getNotifications()
{
    std::vector<std::string> notifications;

    notifications.push_back("Booking confirmed for May 3");
    notifications.push_back("Waitlist position updated");
    notifications.push_back("Compliance documents verified");

    return notifications;
}
