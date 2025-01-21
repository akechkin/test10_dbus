
#ifndef ___DBUS_CON___
#define ___DBUS_CON___

#include "org_freedesktop_NotificationsSimple.h"

// namespace Stal
// {

    class ProxyNotification : public org::freedesktop::Notifications_proxy, public DBus::IntrospectableProxy, public DBus::ObjectProxy
    {
    public:
        ProxyNotification(DBus::Connection &conn) : DBus::ObjectProxy(conn, "/org/freedesktop/Notifications", "org.freedesktop.Notifications") {}
        ~ProxyNotification();
    };

    class SessionNotification
    {
        DBus::Connection conn = DBus::Connection::SessionBus();
        std::unique_ptr<ProxyNotification> ptr;

    public:
        enum NotifyLevel
        {
            Info = 0,
            Warning = 1,
            Error = 2
        };

        SessionNotification();

        bool sendNotify(const std::string &header, const std::string &message, const NotifyLevel &) const;
    };

// }

#endif