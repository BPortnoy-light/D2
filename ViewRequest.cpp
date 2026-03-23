#include "ViewRequest.h"

ViewRequest::ViewRequest(std::string type)
{
    requestType = type;
}

std::string ViewRequest::getType()
{
    return requestType;
}