#ifndef MARKETSTALL_H
#define MARKETSTALL_H
#include <string>
//PLACEHOLDER


class MarketStall
{

    private:
        int ID;
        // MarketDate date;??
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



};


#endif
