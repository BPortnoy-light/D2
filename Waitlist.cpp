#include <string>
#include <vector>
#include "MarketStall.h"
#include "Vendor.h"
#include "MarketWeek.h"
#include "BookingRequest.h"
#include "Waitlist.h"

// creates waitlist
Waitlist::Waitlist(std::string category,int weekID)
{
        this->weekID=weekID;
        this->category=category;
}

// adds bookreqiest to end of waitlist
//void Waitlist::addBookRequest(BookRequest &booking)
//{
//    bookingQueue.push_back(booking);
//}

// removes a book reqwust from waitlist if IDs match
void Waitlist::removeBookRequest(std::string username, int stall, std::string week)
{
    // iterate through and check for
    for(int i=0; i<bookingQueue.size();i++)
    {
        if (username==bookingQueue[i]->getVendor()->getUsername() && stall==bookingQueue[i]->getStall().getID() && week==bookingQueue[i]->getWeek().getDate())
        {
            for (int j=i; j<bookingQueue.size()-1; ++j)
                {
                    bookingQueue[j] = bookingQueue[j + 1];
                }
            bookingQueue.resize(bookingQueue.size() - 1);
        }
    }
}

std::string Waitlist::getCategory()
{
    return this->category;
}

int Waitlist::getWeekID()
{
    return this->weekID;
}
