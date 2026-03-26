#ifndef COMPLIANCEDOCUMENTATION_H
#define COMPLIANCEDOCUMENTATION_H
#include <string>

class ComplianceDocumentation
{
    public:
        // extract date - date stored as int   ddmmyyyy   01082026
        int getDay(int date);
        int getMonth(int date);
        int getYear(int date);
        virtual bool getStatus() = 0;

};



#endif
