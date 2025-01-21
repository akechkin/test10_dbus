
#ifndef __DBUS_CLIENT_HPP
#define __DBUS_CLIENT_HPP

#include <dbus-c++/dbus.h>
#include "echo-introspect.h"

    // { 'y', "uint8_t" },
    // { 'b', "bool" },
    // { 'n', "int16_t" },
    // { 'q', "uint16_t" },
    // { 'i', "int32_t" },
    // { 'u', "uint32_t" },
    // { 'x', "int64_t" },
    // { 't', "uint64_t" },
    // { 'd', "double" },
    // { 's', "std::string" },
    // { 'o', "::DBus::Path" },
    // { 'g', "::DBus::Signature" },
    // { 'v', "::DBus::Variant" },
    // { '\0', "" }


class DbusClient: 
  public test::iface_proxy,
  public DBus::IntrospectableProxy,
  public DBus::ObjectProxy
{

public:
    DbusClient(DBus::Connection &connection, const char *path, const char *service);
    void Echoed(const DBus::Variant &value);
private:
    /* data */
};

#endif

