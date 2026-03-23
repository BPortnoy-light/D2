#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification
{
private:
    std::string message;

public:
    Notification(std::string message);

    std::string getMessage();
};

#endif