#ifndef BOOKSTALLCONTROL_H
#define BOOKSTALLCONTROL_H
#include "MarketStall.h"
#include "Vendor.h"
#include "MarketDay.h"
#include <string>

/*
Purpose: 
Controls Booking of a stall

Features:
- Confirmation message displayed upon successful booking.
- Booking appears on the vendor's status dashboard.
- Enforce a maximum of 2 artisan or food vendors per market day.
- Update stall booking status in the market schedule.
- Add to the vendor’s booked stall.

*/

class BookStallControl
{
    private:
    // should it store stall and vendor proxy?
        MarketStall stall;
        Vendor vendor;
        MarketDay day;

    public:
        BookStallControl(MarketStall &stall, Vendor &vendor, MarketDay &day);

        // should book a stall for the passed vendor
        // 1. check compliance docs for vendor category and stall category
        // 2. verfiy that vendor category max has not been reached
        // 3. mark the stall as reserved or add to waitlist
        // 4. update dashboard 
        void bookStall(MarketStall &stall, Vendor &vendor, MarketDay &day);
        
        // cancel booking for passed stall
        // remove from dashboard
        // remove from 
        void cancelStall(MarketStall &stall, Vendor &vendor, MarketDay &day);

        // checks compliance documents of a passed vendor
        bool checkCompliance(Vendor &vendor);

        // verfiy that vendor category max has not been reached for the given day. if max, pass to waitlist
        bool verfiyAvailable (MarketStall &stall, MarketDay &day);

        // signals to waitlist control to handle - this ends booking procedure and passes it off to waitlistControler 
        void notifyWaitlist(MarketStall &stall, Vendor &vendor, MarketDay &day);

        // update the vendor dashboard with new booking
        void updateDashboard(Vendor &vendor, MarketStall &stall, MarketDay &day);

        

        void createBookRequest(Vendor &vendor, MarketStall &stall, MarketDay &day);
};

#endif
