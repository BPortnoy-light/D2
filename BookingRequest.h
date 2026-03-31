#ifndef BOOKINGREQUEST_H
#define BOOKINGREQUEST_H

#include "MarketStall.h"
#include "MarketWeek.h"

class Vendor;

// booking requests handle i
class BookingRequest
{
private:
    Vendor* vendor;
    MarketStall stall;
    MarketWeek week;

public:
    BookingRequest(Vendor* v, MarketStall s, MarketWeek d);

    Vendor* getVendor();
    MarketStall getStall();
    MarketWeek getWeek();
};

#endif
