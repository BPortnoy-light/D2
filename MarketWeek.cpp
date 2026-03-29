#include "MarketWeek.h"

MarketWeek::MarketWeek()
{
    date = "";
}

MarketWeek::MarketWeek(std::string date)
{
    this->date = date;
}

std::string MarketWeek::getDate()
{
    return date;
}

void MarketWeek::addStall(const MarketStall* stall)
{
    //stalls.push_back(stall);
}

std::vector<MarketStall*> MarketWeek::getStalls()
{
    return stalls;
}

Waitlist* MarketWeek::getWaitlist()
{
    return waitlist;
}
