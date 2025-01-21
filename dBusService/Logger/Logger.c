

#include "Logger.h"


void logData(Priority prio, const char* data){
    sd_journal_print(prio, data);
}
