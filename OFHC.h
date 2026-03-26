#ifndef OFHC_H
#define OFHC_H

#include <string>
#include "ComplianceDocumentation.h"

class OFHC : public ComplianceDocumentation
{
    private:
         std::string type;
         bool status;
         int ID;
         // store as ddmmyyyy
         int expDat;

    public:
        OFHC(int ID, int expDate);
        bool getStatus();
        int getID();
        std::string getType();
};

#endif
