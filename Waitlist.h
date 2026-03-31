#ifndef WAITLIST_H
#define WAITLIST_H

#include <string>
#include <vector>
#include "MarketStall.h"
#include "MarketWeek.h"

class BookingRequest;

// category for each
class Waitlist 
{
    private:
        // weekID to indicate the week of the season
        int weekID;

        // food or artisan (0/1)
        std::string category;

        // storage structure of booking requests
        std::vector<BookingRequest*> bookingQueue;

    public:
        Waitlist(std::string category,int weekID);
        //void addBookRequest(BookRequest &booking);
        void removeBookRequest(std::string vendor, int stall, std::string week);
        std::string getCategory();
        int getWeekID();

};

#endif
