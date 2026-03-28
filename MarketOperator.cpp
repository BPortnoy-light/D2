#include "User.h"
#include "MarketOperator.h"
#include "ComplianceDocumentation.h"
#include "Waitlist.h"
//#include "Notification.h"
//#include "MarketDay.h"
#include <string>
#include <vector>



    // set username and permission for
    MarketOperator::MarketOperator(std::string username)
    {
        this->setPermission(1);
        this->setUsername(username);
    }

    // TODO: IMPLEMENT
    // might be needed for them to pick day to cancel/book for client
    // add extra button for them?
    // maybe browse market Scheudle for a specific vendor?
    void MarketOperator::browseMarketSchedule()
    {

    }

    // MarketOperator
    void MarketOperator::onBehalfBookStall(Vendor *vendor)
    {

    }
    void MarketOperator::onBehalfCancelStall(Vendor *vendor, MarketStall stall)
    {

    }
    void MarketOperator::removeFromWaitlsit(Vendor *vendor,Waitlist &waitlist)
    {

    }

    std::string MarketOperator::displayPermission()
    {
        return "Market Operator";
    }
    std::string MarketOperator::getUsername()
    {
        return getUsername();
    }
