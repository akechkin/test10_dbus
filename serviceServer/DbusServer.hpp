
#ifndef __DBUS_SERVER_HPP
#define __DBUS_SERVER_HPP

#include <dbus-c++/dbus.h>
#include "echo-introspect.h"


class DbusServer: 
  public test::iface_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{

public:
  DbusServer(DBus::Connection &connection);

  int32_t Random();

  std::string Hello(const std::string &name);

  DBus::Variant Echo(const DBus::Variant &value);

  std::vector<uint8_t> Cat(const std::string &file);

  int32_t Sum(const std::vector<int32_t> &ints);

  std::map<std::string, std::string> Info();

private:
    /* data */
};

#endif

