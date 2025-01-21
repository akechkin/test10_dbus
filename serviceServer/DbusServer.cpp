

#include "DbusServer.hpp"

#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>


static const char *ECHO_SERVER_PATH = "/test";


static const char* obj_name = "DbusServer";
DbusServer::DbusServer(DBus::Connection &connection)
  : DBus::ObjectAdaptor(connection, ECHO_SERVER_PATH)
{
        std::cout << "-------------"<<obj_name<<"-------------" << std::endl;

}

int32_t DbusServer::Random()
{
  return rand();
}

std::string DbusServer::Hello(const std::string &name)
{
  return "Hello " + name + "!";
}

DBus::Variant DbusServer::Echo(const DBus::Variant &value)
{
  this->Echoed(value);

  std::cout<<"[DbusServer::Echo] "<<std::endl;

  return value;
}

std::vector< uint8_t > DbusServer::Cat(const std::string &file)
{
  FILE *handle = fopen(file.c_str(), "rb");

  if (!handle) throw DBus::Error("test.service.Cat ErrorFileNotFound", "file not found");

  uint8_t buff[1024];

  size_t nread = fread(buff, 1, sizeof(buff), handle);

  fclose(handle);

  return std::vector< uint8_t > (buff, buff + nread);
}

int32_t DbusServer::Sum(const std::vector<int32_t>& ints)
{
  int32_t sum = 0;

  for (size_t i = 0; i < ints.size(); ++i) sum += ints[i];

  return sum;
}

std::map< std::string, std::string > DbusServer::Info()
{
  std::map< std::string, std::string > info;
  char hostname[HOST_NAME_MAX];

  gethostname(hostname, sizeof(hostname));
  info["hostname"] = hostname;
  info["username"] = getlogin();

  return info;
}
