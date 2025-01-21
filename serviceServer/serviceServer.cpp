
#include "serviceServer.hpp"

#include "DbusServer.hpp"

#include "../utils.hpp"

#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <cstring>

using namespace std;

DBus::BusDispatcher dispatcher;

const char *app_name = "Service Server";

void niam(int sig)
{
  std::cout << "-------------" << app_name << " niam " << "-------------" << std::endl;
  dispatcher.leave();
}

static const char *ECHO_SERVER_NAME = "test.service";

/*
Зарегистрировать шину ru.uveon.stal в системе, для этого нужно создать файл доступа
/etc/dbus-1/system.d/ru.uveon.stal.conf либо /usr/share/dbus-1/system.d/ru.uveon.stal.conf.

Формат файла описан в разделе DBus интерфес.


<!DOCTYPE busconfig PUBLIC "-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN"
        "http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd">
<busconfig>
    <policy context="default">
        <allow own="org.freedesktop.DBus.Examples.Echo"/>
        <allow send_destination="org.freedesktop.DBus.Examples.Echo"/>
        <allow receive_sender="org.freedesktop.DBus.Examples.Echo"/>
    </policy>
</busconfig>


<!DOCTYPE busconfig PUBLIC "-//freedesktop//DTD D-BUS Bus Configuration 1.0//EN"
        "http://www.freedesktop.org/standards/dbus/1.0/busconfig.dtd">
<busconfig>
    <policy user="root">
        <allow own="ru.uveon.stal" />
        <allow send_destination="ru.uveon.stal" />
        <allow send_interface="ru.uveon.stal" />
    </policy>

    <policy user="ivanov">
        <allow send_destination="ru.uveon.stal" />
    </policy>

    <policy group="stal-dbus">
        <allow send_destination="ru.uveon.stal" />
    </policy>
</busconfig>
*/

int main(int argc, char **argv)
{
  size_t i;

  std::cout << "-------------" << app_name << "-------------" << std::endl;
  pid_t pid = getpid();
  std::cout << app_name << ", PID: " << pid << std::endl;

  signal(SIGTERM, niam);
  signal(SIGINT, niam);

  DBus::default_dispatcher = &dispatcher;

  DBus::Connection conn = DBus::Connection::SystemBus();

  try
  {
    conn.request_name(ECHO_SERVER_NAME);
  }
  catch (const DBus::Error &e)
  {
    std::cerr << e.what() << '\n';
  }

  DbusServer server(conn);

  dispatcher.enter();

  std::cout << "-------------" << app_name << " exit " << "-------------" << std::endl;
  return 0;
}
