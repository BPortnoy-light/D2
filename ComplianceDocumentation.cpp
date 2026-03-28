#include "ComplianceDocumentation.h"
#include <string>


    // extract date ddmmyyyy
    int ComplianceDocumentation::getDay(int date)
    {
        return date/10000;
    }

    int ComplianceDocumentation::getMonth(int date)
    {
        return (date/10000) % 100;
    }

    int ComplianceDocumentation::getYear(int date)
    {
        return date% 10000;
    }
