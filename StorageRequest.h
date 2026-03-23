#ifndef STORAGEREQUEST_H
#define STORAGEREQUEST_H

#include <string>

class StorageRequest
{
private:
    std::string action;

public:
    StorageRequest(std::string action);

    std::string getAction();
};

#endif