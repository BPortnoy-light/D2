#ifndef ACCOUNTSTORAGE_H
#define ACCOUNTSTORAGE_H
#include "../User.h"
#include "../Vendor.h"
#include <string>
#include <vector>
#include <memory>
class AccountStorage
{

    private:
        std::vector<std::unique_ptr<User>> validUsernames;

    public:
        AccountStorage();
        bool findUsername(std::string input);
        User* getUser(std::string input);


};

#endif

