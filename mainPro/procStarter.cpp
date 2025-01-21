#include "procStarter.hpp"

#include "stdio.h"


pid_t ProcStarter::startProcess(const char *path, char *const argv[])
{
    pid_t pid = fork();

    if (pid == -1)
    {
        // pid == -1 means error occurred
        printf("can't fork, error occurred\n");
        return -1;
    }
    else if (pid == 0)
    {
        // pid == 0 means child process created
        // unistd
        if (execvp(path, argv) == -1)
        { 
            return -1;
        }
    }

    return pid;
}
