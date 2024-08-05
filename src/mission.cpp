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

int Mission::GetTotalAliensKill() {
    return totalAliensKill;
}

void Mission::SetTotalAliensKill(int value) {
    this->totalAliensKill = value;
}
int Mission::GetCurrentAliensKill() {
    return currentAliensKill;
}

void Mission::SetCurrentAliensKill(int value) {
    this->currentAliensKill = value;
}