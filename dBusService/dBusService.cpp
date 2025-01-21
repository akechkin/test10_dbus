
#include "dBusService.hpp"

#include "ObjEcho/ObjEcho.hpp"
#include "ObjKeyboard/ObjKeyboard.hpp"

#include "../utils.hpp"

#include "procStarter.hpp"

DBus::BusDispatcher dispatcher;

const char *app_name = "dBusService";

void terminate(int sig);

int main(int argc, char **argv)
{
  size_t i;

  std::cout << "-------------" << app_name << "-------------" << std::endl;
  pid_t pid = getpid();
  std::cout << app_name << ", PID: " << pid << std::endl;

  signal(SIGTERM, terminate);
  signal(SIGINT, terminate);

  DBus::default_dispatcher = &dispatcher;

  DBus::Connection conn = DBus::Connection::SessionBus();

  const char *dbusService = "test.dBusService";

  try
  {
    conn.request_name(dbusService);
  }
  catch (const DBus::Error &e)
  {
    std::cerr << e.what() << '\n';
  }

  //system("./script.sh");

  ObjEcho objEcho(conn, "/objEcho");
  ObjKeyboard objKeyboard(conn, "/objKeyboard");

  dispatcher.enter();

  std::cout << "-------------" << app_name << " exit " << "-------------" << std::endl;
  return 0;
}

void terminate(int sig)
{

  std::stringstream s;
  s << "-------------" << app_name << " niam " << "-------------" << std::endl;
  // cout гарантирует фуферизацию только части << "-------------" <<
  std::cout << s.str();
  dispatcher.leave();
}

// char param1[] = "./~/KechkinDoc/pro/examples/tests/test10_dbus/dBusService/script.sh";

// char *fly_term_param[] = {
//   param1,
//    NULL
//    };

// if((pid = ProcStarter::startProcess("fly-term",fly_term_param))==-1){
//   std::cout << "-------------" << app_name << " startProcess fail " << "-------------" << std::endl;
// }else{
//   std::cout << "-------------" << app_name << " startProcess fly-term pid: "<<pid<< "-------------" << std::endl;

// }