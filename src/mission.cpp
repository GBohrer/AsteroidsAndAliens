#include "../include/master_header.h"


Mission::Mission() {};

void Mission::SetTotalTime(float value) {
    this->totalTimeSec = value;
}

float Mission::GetTotalTime() {
    return totalTimeSec;
}

void Mission::SetCurrentTime(float value) {
    this->currentTimeSec = value;
}

float Mission::GetCurrentTime() {
    return currentTimeSec;
}