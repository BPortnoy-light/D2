#include <string>
#include <vector>
#include <memory>
#include "AccountStorage.h"
#include "../User.h"
#include "../Vendor.h"
#include "../MarketOperator.h"
#include "../SystemAdministrator.h"


AccountStorage::AccountStorage()
{
        // vendors
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Abuis","Aowner","Aemail","A613","Aaddress","Vendor","Alfa")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Bbuis","Bowner","Bemail","B613","Baddress","Vendor","Bravo")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Cbuis","Cowner","Cemail","C613","Caddress","Vendor","Charlie")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Dbuis","Downer","Demail","D613","Daddress","Vendor","Delta")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Ebuis","Eowner","Eemail","E613","Eaddress","Artisan","Echo")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Fbuis","Fowner","Femail","F613","Faddress","Artisan","Foxtrot")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Gbuis","Gowner","Gemail","G613","Gaddress","Artisan","Golf")));
        validUsernames.push_back(std::unique_ptr<User>(new Vendor("Hbuis","Howner","Hemail","H613","Haddress","Artisan","Hotel")));
        //oper
        validUsernames.push_back(std::unique_ptr<User>(new MarketOperator("Yankee")));
        //sys
        validUsernames.push_back(std::unique_ptr<User>(new SystemAdministrator("Zulu")));
}

// searches valid usernames for input
bool AccountStorage::findUsername(std::string input)
{

    for (size_t i = 0; i < validUsernames.size(); ++i)
    {
            if (validUsernames[i]->getUsername() == input)
            {
                   return true;
            }
    }

      return false;
}

User* AccountStorage::getUser(std::string input)
{
    for (size_t i = 0; i < validUsernames.size(); ++i)
    {
            if (validUsernames[i]->getUsername() == input)
            {
                   return validUsernames[i].get();
            }
    }

      return nullptr;
}
