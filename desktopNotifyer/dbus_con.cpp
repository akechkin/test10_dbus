

#include "dbus_con.hpp"
#include <dbus-c++/dbus.h>

#include "stdio.h"

#include "../utils.hpp"

//#include <xml.h>




namespace DbusBase
{

    Controller *Controller::m_instance = nullptr;

    Controller *Controller::getInstance()
    {
        if (Controller::m_instance == nullptr)
        {
            Controller::m_instance = new Controller();
        }
        return Controller::m_instance;
    }

    // static const char *DBUS_SERVER_NAME = "org.freedesktop.DBus";
    // static const char *DBUS_SERVER_PATH = "/org/freedesktop/DBus";
    static const char *DBUS_SERVER_NAME = "org.freedesktop.DBus";
    static const char *DBUS_SERVER_PATH =     "/";

    Controller::Controller()
    {
        LOG_MSG("", "");
        m_busDisp = std::make_unique<DBus::BusDispatcher>();
        ::DBus::default_dispatcher = m_busDisp.get();

        DBus::Connection conn  = DBus::Connection::SessionBus();
        DbusProxyObjNotificator inspector(conn, DBUS_SERVER_PATH, DBUS_SERVER_NAME);
        std::string strData =  inspector.Introspect(); 

                std::cout<<strData;

        //DBus::Interface iface();



        DbusProxyObj pobj(conn, DBUS_SERVER_PATH, DBUS_SERVER_NAME,DBUS_SERVER_NAME);


        ::DBus::CallMessage call;
        ::DBus::MessageIter wi = call.writer();

        // // wi << app_name;
        // // wi << replace_id;
        // // wi << app_icon;
        // // wi << summary;
        // // wi << body;
        // // wi << actions;
        // // wi << hints;
        // // wi << expire_timeout;

        call.member("ListNames");
        // // ::DBus::Message ret = invoke_method (call);
        std::cout<< "-----------GGG-------"<<std::endl;

        DBus::Message ret = pobj.invoke_method(call);
        
        // DBus::MessageIter ri = ret.reader();

        // std::vector< std::string > strvOut;         
        // ri>>strvOut;

        // for (size_t i = 0; i < strvOut.size(); i++)
        // {
        //     std::cout << strvOut.at(i) << std::endl;
        // }

        getchar();
    }

    Controller::~Controller()
    {
        LOG_MSG("", "");
    }

     DbusProxyObjNotificator::~DbusProxyObjNotificator()
    {
        LOG_MSG("","");
    }


    ::DBus::BusDispatcher notifyDispatcher;


    DbusDeskNotificator::DbusDeskNotificator():
    connecton(DBus::Connection::SessionBus())
    {
        LOG_MSG("","");
        pProxyObj = std::make_unique<DbusProxyObjNotificator>( connecton ,"/org/freedesktop/Notifications", "org.freedesktop.Notifications");
    }

    bool DbusDeskNotificator::sendNotify( const std::string & header, const std::string & message, const NotifyLevel & level ) const
    {
        const std::string applicationName( "desktopNotifyer" );
        uint32_t replacesID = 0;
        std::string notificationIcon;

        switch( level ) {
            case NotifyLevel::Info:
                notificationIcon = "dialog-information";
                break;

            case NotifyLevel::Warning:
                notificationIcon  = "dialog-warning";
                break;

            case NotifyLevel::Error:
                notificationIcon = "dialog-error";
                break;
        }

        int32_t expirationTimeout = 10; //-1 default


        try {
            pProxyObj->Notify( applicationName, replacesID, notificationIcon, header, message, {}, {}, expirationTimeout );
            return true;

        } catch( const DBus::Error & err ) {
            std::cerr << "dbus error: " << err.what() << std::endl;
        } catch( const std::exception & err ) {
            std::cerr << "exception: " << err.what() << std::endl;
        }

        return false;
    }

    DbusProxyObj::~DbusProxyObj()
    {
    }

}
