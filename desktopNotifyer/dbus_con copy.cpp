

#include "dbus_con.hpp"
#include <dbus-c++/dbus.h>

#include <iostream>



/*

In order to ensure that multiple notifications 
can easily be displayed at once, and to provide a convenient 
implementation, all notifications are controlled by a single 
session-scoped service which exposes a D-BUS interface. 
https://specifications.freedesktop.org/notification-spec/latest/basic-design.html

*/


// namespace Stal
// {


        ProxyNotification::~ProxyNotification()
    {
        std::cout<<__func__<<std::endl;
    }


    ::DBus::BusDispatcher notifyDispatcher;


    SessionNotification::SessionNotification()
    {
        std::cout<<__func__<<std::endl;
        ptr = std::make_unique<ProxyNotification>( conn );
    }

    bool SessionNotification::sendNotify( const std::string & header, const std::string & message, const NotifyLevel & level ) const
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
            ptr->Notify( applicationName, replacesID, notificationIcon, header, message, {}, {}, expirationTimeout );
            return true;

        } catch( const DBus::Error & err ) {
            std::cerr << "dbus error: " << err.what() << std::endl;
        } catch( const std::exception & err ) {
            std::cerr << "exception: " << err.what() << std::endl;
        }

        return false;
    }

//}


