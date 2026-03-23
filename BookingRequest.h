#ifndef BOOKINGREQUEST_H
#define BOOKINGREQUEST_H

#include "Vendor.h"
#include "MarketStall.h"
#include "MarketDay.h"

class BookingRequest
{
private:
    Vendor vendor;
    MarketStall stall;
    MarketDay day;

public:
    BookingRequest(Vendor v, MarketStall s, MarketDay d);

    Vendor getVendor();
    MarketStall getStall();
    MarketDay getDay();
};

#endif