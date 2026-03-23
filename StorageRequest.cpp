#include "StorageRequest.h"

StorageRequest::StorageRequest(std::string action)
{
    this->action = action;
}

std::string StorageRequest::getAction()
{
    return action;
}