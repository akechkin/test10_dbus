
#include "desktopNotifyer.hpp"

#include <iostream>
#include <unistd.h> //getpid
#include <time.h>

#include "stdio.h"

#include "../utils.hpp"

const char *app_name = "desktopNotifyer";

// using namespace Stal;

//extern ::DBus::BusDispatcher notifyDispatcher;


int main(int argc, char **argv)
{

    LOG_MSG(app_name,"start");
    pid_t pid = getpid();
    std::cout << app_name << ", PID: " << pid << std::endl;


    DbusBase::Controller* dbusCtrl = DbusBase::Controller::getInstance();


    //Stal::ProxyNotification notifyObj();
    //DBus::default_dispatcher = & notifyDispatcher;


    //std::string header = "Test Notify";
    //std::string message = "Hello World!";
    //DBus::Connection conn = DBus::Connection::SessionBus();

    //DbusBase::DbusDeskNotificator deskNotificator;// = new DbusBase::DbusDeskNotificator();

    //deskNotificator.sendNotify( header, message, DbusBase::DbusDeskNotificator::Warning );


    while (1)
    {
        std::cout << app_name << " time: " << clock() << "-------------" << std::endl;
        //SessionNotification().sendNotify( header, message + std::to_string(clock()), SessionNotification::Info );
        //notif->sendNotify( header, message, SessionNotification::Info );

        sleep(2);
    }

    getchar();
    LOG_MSG(app_name,"exit");
    return 0;
}
