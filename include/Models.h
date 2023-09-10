#ifndef models_h
#define models_h

#include <Arduino.h>

const char *ssid = "faizareborn";
const char *password = "herbowo221977";

struct TimerVar {
    const uint16_t interval;
    uint64_t prevTime;
    uint64_t currentTime;
    
    TimerVar(uint16_t initialInterval) : interval(initialInterval), prevTime(0), currentTime(0) {};
};



#endif