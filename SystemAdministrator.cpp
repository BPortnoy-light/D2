#include "User.h"
#include "SystemAdministrator.h"
#include "ComplianceDocumentation.h"
#include "Waitlist.h"
//#include "Notification.h"
#include <string>
#include <vector>


SystemAdministrator::SystemAdministrator(std::string username)
{
    this->setPermission(2);
    this->setUsername(username);
}

std::string SystemAdministrator::displayPermission()
{
    return "System Administrator";
}

std::string SystemAdministrator::getUsername()
{
    return getUsername();
}
