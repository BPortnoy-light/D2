#ifndef VIEWREQUEST_H
#define VIEWREQUEST_H

#include <string>

// view requests handle data transfer to and from the market schedule
class ViewRequest
{
private:
    std::string requestType;

public:
    ViewRequest(std::string type);

    std::string getType();
};

#endif
