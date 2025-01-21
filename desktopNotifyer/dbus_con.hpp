
#ifndef ___DBUS_CON___
#define ___DBUS_CON___

#include "org_freedesktop_NotificationsSimple.h"

namespace DbusBase
{

    class Controller
    {

    public:
        static Controller *getInstance();
        
        void operator=(const Controller &) = delete;
        Controller(Controller &other) = delete;

    protected:
        Controller();
        ~Controller();

    private:
        static Controller *m_instance;
        std::unique_ptr<DBus::BusDispatcher> m_busDisp;
        
    };

    class DbusProxyObj : public ::DBus::InterfaceProxy, /*public ::DBus::InterfaceProxy,*/
                         public ::DBus::ObjectProxy
    {
    public:
        DbusProxyObj(DBus::Connection &conn, const char *path, const char *service, const char* iface) : 
        ::DBus::InterfaceProxy(iface),
        DBus::ObjectProxy(conn, path, service){


        //m_inerface = new :DBus::InterfaceProxy(service);
        ::DBus::CallMessage call;
        call.member("ListNames");
        invoke_method(call);

        }
        ~DbusProxyObj();
    private:
        ::DBus::InterfaceProxy* m_inerface;
    };



    class DbusProxyObjNotificator : public org::freedesktop::Notifications_proxy,
                              public DBus::IntrospectableProxy,
                              public DBus::ObjectProxy
    {
    public:
        DbusProxyObjNotificator(DBus::Connection &conn, const char *path, const char *service) : DBus::ObjectProxy(conn, path, service) {}
        ~DbusProxyObjNotificator();
    };

    class DbusDeskNotificator
    {
        DBus::Connection connecton;
        std::unique_ptr<DbusProxyObjNotificator> pProxyObj;

    public:

        DbusDeskNotificator();

        enum NotifyLevel
        {
            Info = 0,
            Warning = 1,
            Error = 2
        };

        bool sendNotify(const std::string &header, const std::string &message, const NotifyLevel &) const;
    };

}

#endif