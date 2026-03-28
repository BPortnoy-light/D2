#include "ComplianceDocumentation.h"
#include "LiabilityInsurance.h"
#include <string>

// derived class of compliance doc
// constructor
LiabilityInsurance::LiabilityInsurance(int ID, std::string providerName, int expDate)
{
    this->type="Proof of Liability Insurance";
    this->status=true;
    this->ID=ID;
    this->providerName=providerName;
    this->expDat=expDate;
};

bool LiabilityInsurance::getStatus()
{
    return status;
}
int LiabilityInsurance::getID()
{
    return ID;
}

std::string LiabilityInsurance::getType()
{
    return type;
}

std::string LiabilityInsurance::getProviderName()
{
    return providerName;
}
