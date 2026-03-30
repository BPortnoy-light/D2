#ifndef MARKETOPERATOR_H
#define MARKETOPERATOR_H
#include "User.h"
#include "ComplianceDocumentation.h"
#include "Waitlist.h"
#include "Vendor.h"
#include "Notification.h"
#include "MarketWeek.h"
#include <string>
#include <vector>


class MarketOperator : public User
{
    public:

        MarketOperator(std::string username);

        // might be needed for them to pick day to cancel/book for client
        // add extra button for them?
        // maybe browse market Scheudle for a specific vendor?
        void browseMarketSchedule();

        // MarketOperator
        //edit
        void onBehalfBookStall(Vendor *vendor);
        void onBehalfCancelStall(Vendor *vendor, MarketStall stall);
        void removeFromWaitlsit(Vendor *vendor,Waitlist &waitlist);

        std::string displayPermission();
        std::string getUsername();
        int getPermission()
        {
            return 1;
        }

};
#endif // MARKETOPERATOR_H
