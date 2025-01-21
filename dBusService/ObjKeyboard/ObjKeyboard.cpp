

#include "ObjKeyboard.hpp"

#include "Logger.h"
#include "KeyboardDriver/captureKeyboard.h"

static const char* obj_name = "ObjKeyboard";
ObjKeyboard::ObjKeyboard(DBus::Connection &connection, const char* path)
  : DBus::ObjectAdaptor(connection, path)
{
        std::cout << "-------------"<<obj_name<<"-------------" << std::endl;

}

bool ObjKeyboard::SwitchKeyboardLayout()
{

    std::cout<<"[ObjKeyboard::SwitchKeyboardLayout] "<<std::endl;
    if(xcbCtrlSwitchLayout(NULL)==True){
          logData(PriorityLOW,"Keyboard layout switched !");
    }

    return false;
}
