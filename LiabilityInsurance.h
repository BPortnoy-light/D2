#ifndef LIABILITYINSURANCE_H
#define LIABILITYINSURANCE_H

#include "ComplianceDocumentation.h"
#include <string>
class LiabilityInsurance : public ComplianceDocumentation
{

    private:
        std::string type;
        bool status;
        int ID;
        int expDat;
        std::string providerName;
public:


    public:
        LiabilityInsurance(int ID, std::string providerName, int expDate);
        std::string getType();
        bool getStatus();
        int getID();
        std::string getProviderName();

};



#endif
