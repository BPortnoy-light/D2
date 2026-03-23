#ifndef VIEWREQUEST_H
#define VIEWREQUEST_H

#include <string>

class ViewRequest
{
private:
    std::string requestType;

public:
    ViewRequest(std::string type);

    std::string getType();
};

#endif