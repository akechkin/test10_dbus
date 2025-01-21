

#include "DbusClient.hpp"

#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <cstring>

#include <unistd.h>

static const char* obj_name = "DbusClient";
DbusClient::DbusClient(DBus::Connection &connection, const char *path, const char *service)
: DBus::ObjectProxy{connection,path,service}
{
        std::cout << "-------------"<<obj_name<<"-------------" << std::endl;

}

void DbusClient::Echoed(const DBus::Variant &value)
{
      std::cout << "@@@!@@@ DbusClient Echoed"<< "pid: "<< getuid() <<std::endl;
}
