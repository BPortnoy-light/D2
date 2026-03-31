#include "BookingRequest.h"
#include "MarketWeek.h"
#include "Vendor.h"

BookingRequest::BookingRequest(Vendor* v, MarketStall s, MarketWeek w)
{
    vendor = v;
    stall = s;
    week = w;
}

Vendor* BookingRequest::getVendor()
{
    return vendor;
}

MarketStall BookingRequest::getStall()
{
    return stall;
}

MarketWeek BookingRequest::getWeek()
{
    return week;
}
