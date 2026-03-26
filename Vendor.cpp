#include "User.h"
#include "Vendor.h"
#include "ComplianceDocumentation.h"

#include <string>


Vendor::Vendor(std::string businessName,std::string ownerName,std::string email,std::string phone, std::string mailing,std::string category,std::string username)
{
    this->businessName=businessName;
    this->ownerName=ownerName;
    this->email=email;
    this->phone=phone;
    this->mailing=mailing;
    this->category=category;

    // set permission level as vendor (0) and username
    this->setPermission(this->getPermission());
    this->setUsername(username);

}

//Constructor for when existing data: Object will have populated vectors and fields
/*
 * Vendor::Vendor(std::string businessName,std::string ownerName,std::string email,std::string phone,
   std::string mailing,std::string category,std::vector<ComplianceDocumentation*> complianceVector,
    bool complianceOK,std::vector<Waitlist*> joinedWaitlists, std::vector<Notification*> vendorNotifications,std::string username)
{
    this->businessName=businessName;
    this->ownerName=ownerName;
    this->email=email;
    this->phone=phone;
    this->mailing=mailing;
    this->category=category;

    this->complianceVector=complianceVector;
    this->complianceOK=complianceOK;
    this->joinedWaitlists=joinedWaitlists;
    this->vendorNotifications=vendorNotifications;

    // set permission level as vendor (0) and username
    this->setPermission(this->getPermission());
    this->setUsername(username);

}
*/





// Checks if all compliance docs are true
bool Vendor::checkComplianceDocs()
{

}

// get/generate vendor specific view of Market Schedule (4 weeks based on vendor category)
void Vendor::browseMarketSchedule()
{

}

// initiate book request for vendor
void Vendor::vendorBookStall()
{

}

// get/generate data for vendor Dashboard
// Personal Data, Compliance, Active Bookings, Waitlist, Notifications
void Vendor::viewVendorDashboard()
{

}


// getters
std::string Vendor::getBusinessName()
{
    return this->businessName;
}
std::string Vendor::getOwnerName()
{
    return this->ownerName;
}
std::string Vendor::getEmail()
{
    return this->email;
}
std::string Vendor::getPhone()
{
    return this->phone;
}
std::string Vendor::getMailing()
{
    return this->mailing;
}
std::string Vendor::getCategory()
{
    return this->category;
}
bool Vendor::getComplianceOK()
{
    return this->complianceOK;
}

std::vector<ComplianceDocumentation*> Vendor::getComplianceVector()
{
    return this->complianceVector;
}
std::vector<Waitlist*> Vendor::getJoinedWaitlists()
{
    return this->joinedWaitlists;
}
//std::vector<Notification*> Vendor::getVendorNotifications()
//{
//    return this->vendorNotifications;
//}

// give text represnetation of permission
std::string Vendor::displayPermission()
{
    return "Vendor";
}

// get username form base user class
std::string Vendor::getUsername()
{
    return getUsername();
}


