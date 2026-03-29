#include "BookStallControl.h"
#include "MarketStall.h"
#include "Vendor.h"
#include "MarketDay.h"
#include "BookRequest.h"
#include <string>

#include <iostream>

BookStallControl::BookStallControl(MarketStall &stall, Vendor &vendor, MarketDay &day)
{
    this->stall=stall;
    this->vendor=vendor;
    this->day=day;
}

// should book a stall for the passed vendor
// 1. check compliance docs for vendor category and stall category
// 2. verfiy that vendor category max has not been reached
// 3. mark the stall as reserved or add to waitlist
// 4. update dashboard

// should this take stalls vendor and day or a request copntaining them?
void BookStallControl::bookStall(MarketStall &stall, Vendor &vendor, MarketDay &day)
{
    // check compliance docs
    // compliance false therefore illegal and terminate booking
    // call failure notification display TODO
    if (!checkCompliance(vendor))
    {
        std::cout << "Incomplete Compliance Documents\n";
        return;
    }
    // check if stall available
    // if true space is Available
    if (verfiyAvailable(stall, day))
    {
        // update stall TODO
        stall.setBooked(true);
        // send request to storageManager() to update stall structure
        createBookRequest(vendor,stall,day);

        // update dashboard - not implemented yet
        updateDashboard(vendor, stall, day);

        // display confirmation notice -- TODO
        std::cout << "Stall booking completed successfully\n";
    }
        // compliance true but not available -- waitlist request
    else
    {
        //notifyWaitlist; TODO
        notifyWaitlist(stall,vendor,day);
        std::cout << "No stalls available - vendor added to waitlist\n";
    }

}

// TODO
// checks compliance documents of a passed vendor
bool BookStallControl::checkCompliance(Vendor &vendor)
{

    for(int i=0; i<vendor.getComplianceDocuments().size();i++)
    {
        if(vendor.getComplianceDocuments()[i]->getStatus()==false)
        {
            return false;
        }

    }
    return true;
}

// CHECK IF THIS WORKS WITH VENDOR/STALL STRUCTURE
// verfiy that vendor category max has not been reached for the given day. if max, pass to waitlist
bool BookStallControl::verfiyAvailable (MarketStall &stall, MarketDay &day)
{
    // verifyMax category has not been reach
    // access stalls for the day
    int stallCount = 0;
    int maxStalls = 2;

    // count booked stalls of the same category
    if(stall.isBooked())
    {
        return false;
    }
    // day class has array of stalls which also maintains a size
   // for (size_t i = 0; i < day.stalls.size; i++)
   // {
        // assumes stalls have a category associated with it
        //if (day.stalls[i].category == stall.getCategory())
         //   {
                stallCount++;
         //   }
  //  }

    return stallCount < maxStalls;
}

//TODO
// signals to waitlist control to handle - this ends booking procedure and passes it off to waitlistControler
void BookStallControl::notifyWaitlist(MarketStall &stall, Vendor &vendor, MarketDay &day)
{
    // call waitlist function
    BookRequest request(vendor,stall,day);
    std::cout << "Vendor added to waitlist queue\n";
}

//TODO
// update the vendor dashboard with new booking
void BookStallControl::updateDashboard(Vendor &vendor, MarketStall &stall, MarketDay &day)
{
    // call dashboard controller function
    std::cout << "Dashboard updated with new booking\n"; 
}

//TODO
void BookStallControl::createBookRequest(Vendor &vendor, MarketStall &stall, MarketDay &day)
{
    BookRequest request(vendor,stall,day);
    std:: cout << "Booking request created with ID:" << request.getBookingID() << std:: endl;

}

//TODO
// cancel booking for passed stall
// remove from dashboard
// remove from STORAGE
void BookStallControl::cancelStall(MarketStall &stall, Vendor &vendor, MarketDay &day)
{
    if(!stall.isBooked())
    {
        std:: cout << "No booking exists for this stall\n";
        return;
    }
    // Free the stall
    stall.setBooked(false);

    //update dashboard (placeholder)
    updateDashboard(vendor,stall,day);

    std::cout << "Stall booking cancelled successfully\n";

}
