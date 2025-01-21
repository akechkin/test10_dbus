

#include "ObjEcho.hpp"

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>

#include "Logger.h"

static const char* obj_name = "ObjEcho";
ObjEcho::ObjEcho(DBus::Connection &connection, const char* path)
  : DBus::ObjectAdaptor(connection, path)
{
        std::cout << "-------------"<<obj_name<<"-------------" << std::endl;

}

std::string ObjEcho::Hello(const std::string &name)
{
  std::cout<<"[ObjEcho::Hello] "<<std::endl;
  logData(PriorityLOW,"[ObjEcho::Hello]");

  return "Hello " + name + "!";
}

DBus::Variant ObjEcho::Echo(const DBus::Variant &value)
{

  std::cout<<"[ObjEcho::Echo] "<<std::endl;
  logData(PriorityLOW,"[ObjEcho::Echo]");

  return value;
}

std::string ObjEcho::Hello2(const std::string &name)
{
  std::cout<<"[ObjEcho::Hello2] "<<std::endl;
  logData(PriorityHIGH,"[ObjEcho::Hello2]");

  return "Hello2 " + name + "!";
}

DBus::Variant ObjEcho::Echo2(const DBus::Variant &value)
{

  std::cout<<"[ObjEcho::Echo2] "<<std::endl;
  logData(PriorityHIGH,"[ObjEcho::Echo2]");
  return value;
}
