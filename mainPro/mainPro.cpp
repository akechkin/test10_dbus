
#include "mainPro.hpp"

#include "procStarter.hpp"

#include "../utils.hpp"

const char *app_name = "mainPro";

#include <list>

std::list<const char*> list = {
    // "./desktopNotifyer"
    "./serviceServer",
    "./serviceClient"
};


int main(int argc, char **argv)
{
    
    //std::cout << "-------------" << app_name << "-------------" << std::endl;
    LOG_MSG(app_name,"start");

    pid_t pid = getpid();
    std::cout << app_name << ", PID: " << pid << std::endl;


    for (auto * el: list)
    {
        std::cout << app_name;
        if (ProcStarter::startProcess(el, argv) == -1)
        {
            std::cout << ", error :" << errno << std::endl << std::endl;
            perror("startProcess");
        }else{
            std::cout << ", play :" << el << std::endl << std::endl;
        }
    }

    getchar();
    LOG_MSG(app_name,"exit");

    return 0;
}
