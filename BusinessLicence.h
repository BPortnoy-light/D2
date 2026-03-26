#ifndef BUSINESSLICENCE_H
#define BUSINESSLICENCE_H
#include <string>
#include "ComplianceDocumentation.h"

class BusinessLicence : public ComplianceDocumentation
{
    private:
        std::string type;

         // true = complete
         // false = fail
         // Default True
         bool status;

         int ID;

         // store as ddmmyyyy
         int expDat;

    public:
        BusinessLicence(int ID, int expDate);
        bool getStatus();
        int getID();
        std::string getType();
};



#endif // BUSINESSLICENCE_H
