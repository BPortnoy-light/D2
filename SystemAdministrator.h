#ifndef SYSTEMADMINISTRATOR_H
#define SYSTEMADMINISTRATOR_H
#include "User.h"
#include "ComplianceDocumentation.h"
#include "Waitlist.h"
#include "Notification.h"
#include <string>
#include <vector>


class SystemAdministrator : public User
{
    public:

        SystemAdministrator(std::string username);

        std::string displayPermission();
        std::string getUsername();
        int getPermission()
        {
            return 2;
        }

};
#endif // SYSTEMADMINISTRATOR_H
