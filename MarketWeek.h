#ifndef MARKETWEEK_H
#define MARKETWEEK_H

#include <vector>
#include <string>
class MarketStall;
class Waitlist;

class MarketWeek
{
private:
    std::string date;
    std::vector<MarketStall*> stalls;
    Waitlist* waitlist;

public:
    MarketWeek();
    MarketWeek(std::string date);

    std::string getDate();

    void addStall(const MarketStall* stall);
    std::vector<MarketStall*> getStalls();

    Waitlist* getWaitlist();
};

#endif
