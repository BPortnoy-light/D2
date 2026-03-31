#ifndef VENDOR_H
#define VENDOR_H
#include "User.h"
#include "ComplianceDocumentation.h"
#include "Waitlist.h"
#include "Notification.h"
#include <string>
#include <vector>


class Vendor : public User
{
    private:
        // Personal data:
        std::string businessName;
        std::string ownerName;
        std::string email;
        std::string phone;
        std::string mailing;
        std::string category;

        // Compliance Documentation:
        // Vector of all compliance documents
        std::vector<ComplianceDocumentation*> complianceVector;

        // True if all compliance documents are entered correctly
        bool complianceOK;

        // Booking Data:
        // vector of waitlists vendor has joined
        std::vector<Waitlist*> joinedWaitlists;

        // vector of notifications
        std::vector<Notification*> vendorNotifications;

    public:
        // default if nothing
        Vendor();

        // remember to set user permissions
        // testing constructor
        Vendor(std::string businessName,std::string ownerName,std::string email,std::string phone, std::string mailing,std::string category,std::string username);

        // Full constructor with all fields
        //Vendor(std::string businessName,std::string ownerName,std::string email,std::string phone,
        //    std::string mailing,std::string category,std::vector<ComplianceDocumentation*> complianceVector,
        //    bool complianceOK,std::vector<Waitlist*> joinedWaitlists, std::vector<Notification*> vendorNotifications,std::string username);

        std::string displayPermission();
        std::string getUsername();
        int getPermission()
        {
            return 0;
        }


        // Checks if all compliance docs are true
        bool checkComplianceDocs();

        // get/generate vendor specific view of Market Schedule (4 weeks based on vendor category)
        void browseMarketSchedule();

        // initiate book request for vendor
        void vendorBookStall();

        // get/generate data for vendor Dashboard
        // Personal Data, Compliance, Active Bookings, Waitlist, Notifications
        void viewVendorDashboard();

        // getters
        std::string getBusinessName();
        std::string getOwnerName();
        std::string getEmail();
        std::string getPhone();
        std::string getMailing();
        std::string getCategory();
        bool getComplianceOK();
        std::vector<ComplianceDocumentation*> getComplianceVector();
        std::vector<Waitlist*> getJoinedWaitlists();
        std::vector<Notification*> getVendorNotifications();

        Waitlist* findWaitlist(int week, std::string category);

};
#endif // VENDOR_H
