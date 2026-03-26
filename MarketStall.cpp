#include "MarketStall.h"
//PLACEHOLDER
MarketStall::MarketStall()
{
}


MarketStall::MarketStall(int ID,std::string category, int price, bool booked)
{
    this->ID=ID;
    this->category=category;
    this->price=price;
    this->booked=booked;
}
// Check booking status
bool MarketStall::isBooked()
{
    return booked;
}
// Set booking status
void MarketStall::setBooked(bool status)
{
    this->booked=status;
}
