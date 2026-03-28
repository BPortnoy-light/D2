#include "User.h"
#include "ComplianceDocumentation.h"

#include <string>


    std::string User::getUsername()
    {
        return username;
    }

    int User::getPermission()
    {
        return permission;
    }

    // 0:vendor 1:Market Operator 2:System Administrator
    //setter
    void User::setPermission(int x)
    {
        this->permission=x;
    };

    void User::setUsername(std::string username)
    {
        this->username=username;
    };

    std::string User::displayPermission(){}
