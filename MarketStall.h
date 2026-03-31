#ifndef MARKETSTALL_H
#define MARKETSTALL_H
#include "MarketWeek.h"
#include <string>
//PLACEHOLDER


class MarketStall
{

    private:
        int ID;
        MarketWeek week;
        std::string category;
        int price;
        bool booked;

    public:

        // Constructor
        MarketStall();
        MarketStall(int ID,std::string category, int price, bool booked);
        // Check booking status
        bool isBooked();
        // Set booking status
        void setBooked(bool status);

        // Get stall category
        std::string getCategory();
        int getID();


};


#endif
