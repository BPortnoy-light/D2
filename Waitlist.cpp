#include <string>
#include <vector>
#include "MarketStall.h"
#include "Vendor.h"
//#include "MarketDay.h"
//#include "BookRequest.h"
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
//void Waitlist::removeBookRequest(BookRequest &booking)
//{
 //   for (size_t i=0; i<bookingQueue.size();i++)
  //  {
        // if ids match remove element - vector fixes space itself
     //   if (bookingQueue[i].getBookingID()==booking.getBookingID())
       // {
            // must use iterator to use erase
     //       bookingQueue.erase(bookingQueue.begin()+i);
       //     break;
    //    }
   // }
//}

std::string Waitlist::getCategory()
{
    return this->category;
}

int Waitlist::getWeekID()
{
    return this->weekID;
}
