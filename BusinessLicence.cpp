#include "ComplianceDocumentation.h"
#include "BusinessLicence.h"
#include <string>

// derived class of compliance doc
// constructor
BusinessLicence::BusinessLicence(int ID, int expDate)
{
    this->type="City of Hintonville Business Licence";
    this->status=true;
    this->ID=ID;
    this->expDat=expDate;
};

bool BusinessLicence::getStatus()
{
    return status;
}
int BusinessLicence::getID()
{
    return ID;
}

std::string BusinessLicence::getType()
{
    return type;
}
