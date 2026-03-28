#include "ComplianceDocumentation.h"
#include "OFHC.h"
#include <string>

// derived class of compliance doc
// constructor
OFHC::OFHC(int ID, int expDate)
{
    this->type="Ontario Food Handler Certification";
    this->status=true;
    this->ID=ID;
    this->expDat=expDate;
};

bool OFHC::getStatus()
{
    return status;
}
int OFHC::getID()
{
    return ID;
}

std::string OFHC::getType()
{
    return type;
}
