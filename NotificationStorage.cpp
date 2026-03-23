#include "NotificationStorage.h"

void NotificationStorage::addNotification(const Notification &n)
{
    notifications.push_back(n);
}

std::vector<Notification>& NotificationStorage::getNotifications()
{
    return notifications;
}