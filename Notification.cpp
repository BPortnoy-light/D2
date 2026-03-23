#include "Notification.h"

Notification::Notification(std::string message)
{
    this->message = message;
}

std::string Notification::getMessage()
{
    return message;
}