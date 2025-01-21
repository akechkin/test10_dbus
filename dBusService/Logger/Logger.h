
#ifndef __CAPTURE_LOGGER_H__
#define __CAPTURE_LOGGER_H__

#include <systemd/sd-journal.h>


#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
    PriorityHIGH = LOG_ERR,
    PriorityLOW = LOG_DEBUG
}Priority;

void logData(Priority prio, const char* data);


#ifdef __cplusplus
}
#endif




#endif