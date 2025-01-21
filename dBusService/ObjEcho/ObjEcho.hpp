
#ifndef __OBJ_ECHO__HPP
#define __OBJ_ECHO__HPP

#include "ObjEcho-adaptor.h"

class ObjEcho: 
  public test::iface1_adaptor,
  public test::iface2_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{

public:
  ObjEcho(DBus::Connection &connection, const char* path);

  //iface1
  std::string Hello(const std::string &name);
  DBus::Variant Echo(const DBus::Variant &value);

  //iface2
  std::string Hello2(const std::string &name);
  DBus::Variant Echo2(const DBus::Variant &value);

private:
    /* data */
};

#endif

