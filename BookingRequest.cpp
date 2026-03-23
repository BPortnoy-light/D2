#include "BookingRequest.h"

BookingRequest::BookingRequest(Vendor v, MarketStall s, MarketDay d)
{
    vendor = v;
    stall = s;
    day = d;
}

Vendor BookingRequest::getVendor()
{
    return vendor;
}

MarketStall BookingRequest::getStall()
{
    return stall;
}

MarketDay BookingRequest::getDay()
{
    return day;
}