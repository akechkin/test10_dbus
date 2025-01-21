
#include "serviceClient.hpp"


#include "DbusClient.hpp"

#include "../utils.hpp"

#include <iostream>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <cstring>

#include <thread>


// #include <chrono>
// using namespace std::chrono_literals;
using namespace std;

static const size_t THREADS = 3;

static bool spin = true;




DbusClient *g_client = NULL;

DBus::Pipe *thread_pipe_list[THREADS];

DBus::BusDispatcher dispatcher;
DBus::DefaultTimeout *timeout;

const char* app_name = "Service Client";

#define THREAD_CYCLES (1)


typedef struct type_pipe_struct
{
  enum mType{
    mHello = 0,
    mEcho
  }msg;
  size_t pipeId;
  std::string data;
}type_pipe_handler;


void *greeter_thread(void *arg)
{
  char idstr[16];
  size_t i = (size_t) arg;


  type_pipe_handler pipeStruct{
    .msg = type_pipe_struct::mEcho,
    .pipeId = i,
    .data="Hello data"
  };

  snprintf(idstr, sizeof(idstr), "%lu", pthread_self());

  if (i == 0)
  {
    thread_pipe_list[i]->write(&pipeStruct, sizeof(type_pipe_handler));
  }
  else
  {
    thread_pipe_list[i]->write(idstr, strlen(idstr) + 1);
  }

  cout << "* thread id:"<< idstr << ", done (" << i << ")" << endl;


    //LOG_MSG(app_name,"loop");
    cout << "* thread id:"<< idstr << ", enter loop (" << i << ")" << endl;

      // dispatcher.del_pipe(thread_pipe_list[0]);
      // dispatcher.del_pipe(thread_pipe_list[1]);
      // dispatcher.del_pipe(thread_pipe_list[2]);

  int loopCounter = 0;

    while (spin)
    {
          cout << "* thread id:"<< idstr << ", done (" << i << "), counter:"<< loopCounter << endl;
          if(++loopCounter==THREAD_CYCLES){
            loopCounter = 0;
            sleep(2);
            std::this_thread::sleep_for( 150ms );
          }
    }
    
  return NULL;
}

void niam(int sig)
{
  spin = false;

  dispatcher.leave();
}


static DBus::Variant variant_string(std::string s)
{
  DBus::Variant variant;
  DBus::MessageIter iter=variant.writer();
  iter << s;
  return variant;
}

template <class T>
T from_variant(const DBus::Variant &v)
	{
		T value;
		DBus::MessageIter iter = v.reader();
		iter >> value;
		return value;
	}

#define MAX_CALL_HELLO (3)

void handler1(const void *data, void *buffer, unsigned int nbyte)
{
  //char *str = (char *) buffer;


  type_pipe_handler* pipeStruct = (type_pipe_handler*)buffer;

  cout << "-buffer1: " << pipeStruct << ", size: " << nbyte << endl;

  cout << "-message type: "<<pipeStruct->msg<< endl;
  cout << "-message data: "<<pipeStruct->data<< endl;

  DBus::MessageIter wi;
  DBus::Variant input = variant_string("Test Variant");

  DBus::Variant output;
  string strOut;
  for (int i = 0; i < MAX_CALL_HELLO && spin; ++i)
  {
    switch (pipeStruct->msg)
    {
    case type_pipe_struct::mEcho:
      cout << "-message mEcho: " << endl;

      // std::string argout = {"asd"};

      output = g_client->Echo(input);
      strOut = from_variant<string>(output);
      cout << "-call1 answer: "<< strOut << endl;
      break;
    case type_pipe_struct::mHello:
      cout << "-message mHello: " << endl;
      cout << "-call1: " << g_client->Hello(pipeStruct->data) << endl;
      break;
    default:
      break;
    }
  }
}

void handler2(const void *data, void *buffer, unsigned int nbyte)
{
  char *str = (char *) buffer;
  cout << "buffer2: " << str << ", size: " << nbyte << endl;
  for (int i = 0; i < MAX_CALL_HELLO && spin; ++i)
  {
    cout << "call2: " << g_client->Hello(str) << endl;
  }
}

void handler3(const void *data, void *buffer, unsigned int nbyte)
{
  char *str = (char *) buffer;
  //char *strData = (char *) data;
  //cout << "buffer3 data: " << strData << endl;
  cout << "buffer3: " << str << ", size: " << nbyte << endl;
  for (int i = 0; i < MAX_CALL_HELLO && spin; ++i)
  {
    cout << "call3: " << g_client->Hello(str) << endl;
  }
}

static const char *ECHO_SERVER_SERVICE= "test.service";
static const char *ECHO_SERVER_PATH = "/test";


int main(int argc, char **argv)
{
    size_t i;

    std::cout << "-------------"<<app_name<<"-------------" << std::endl;
    pid_t pid = getpid();
    std::cout<<app_name<< ", PID: " << pid << std::endl;

    signal(SIGTERM, niam);
    signal(SIGINT, niam);

    DBus::_init_threading();

    DBus::default_dispatcher = &dispatcher;

    // increase DBus-C++ frequency
    new DBus::DefaultTimeout(100, false, &dispatcher);

    DBus::Connection conn = DBus::Connection::SystemBus();

    DbusClient client(conn, ECHO_SERVER_PATH, ECHO_SERVER_SERVICE);
    g_client = &client;

    pthread_t threads[THREADS];

    thread_pipe_list[0] = dispatcher.add_pipe(handler1, NULL);
    thread_pipe_list[1] = dispatcher.add_pipe(handler2, NULL);
    thread_pipe_list[2] = dispatcher.add_pipe(handler3, NULL);

    cout << "main pthread, id: " << pthread_self() << endl;

    for (i = 0; i < THREADS; ++i)
    {
        pthread_create(threads + i, NULL, greeter_thread, (void *)i);
        cout << "main thread create, id: "<<threads[i]<< endl;
        //sleep(1);
    }

    cout << "dispatcher.enter()" << endl;
    dispatcher.enter();

      cout << "terminating" << endl;

      for (i = 0; i < THREADS; ++i)
      {
          pthread_join(threads[i], NULL);
      }

      dispatcher.del_pipe(thread_pipe_list[0]);
      dispatcher.del_pipe(thread_pipe_list[1]);
      dispatcher.del_pipe(thread_pipe_list[2]);

      std::cout << "-------------" << app_name << " exit " << "-------------" << std::endl;
      return 0;
}
