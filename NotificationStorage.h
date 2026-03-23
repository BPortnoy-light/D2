#ifndef NOTIFICATIONSTORAGE_H
#define NOTIFICATIONSTORAGE_H

#include <vector>
#include "Notification.h"

class NotificationStorage
{
private:
    std::vector<Notification> notifications;

public:
    void addNotification(const Notification &n);
    std::vector<Notification>& getNotifications();
};

#endif