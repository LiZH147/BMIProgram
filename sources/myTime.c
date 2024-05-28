#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../include/myTime.h"

char* getCurrentTime(){
    time_t rawtime;
    struct tm * timeinfo;
    char *timeStr = (char*) malloc(sizeof(char) * 20);
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(timeStr, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
    return timeStr;
}
