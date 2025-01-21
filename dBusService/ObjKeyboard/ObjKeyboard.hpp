
#ifndef __OBJ_KEYBOARD_HPP
#define __OBJ_KEYBOARD_HPP

#include <iostream>

#include "ObjKeyboard-adaptor.h"


class ObjKeyboard: 
  public _X11_::keyboard_adaptor,
  public DBus::IntrospectableAdaptor,
  public DBus::ObjectAdaptor
{

public:
  ObjKeyboard(DBus::Connection &connection, const char* path);

  bool SwitchKeyboardLayout();

private:
    /* data */
};

#endif

