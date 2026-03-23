#ifndef MARKETSCHEDULE_H
#define MARKETSCHEDULE_H

#include <vector>
#include "MarketWeek.h"

class MarketSchedule
{
private:
    std::vector<MarketWeek> weeks;

public:
    MarketSchedule();

    void addWeek(const MarketWeek &week);
    std::vector<MarketWeek>& getWeeks();
};

#endif