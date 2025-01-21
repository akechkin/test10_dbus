#ifndef _PROCSTARTER_HPP
#define _PROCSTARTER_HPP

#include "unistd.h"

class ProcStarter
{
public:

    static pid_t startProcess(const char *path, char *const argv[]);

private:
    /* data */

};




#endif
