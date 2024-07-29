#pragma once
#include "../master_header.h"


class Mission {

    public:
        Mission();

        void SetTotalTime(float value);
        float GetTotalTime();
        void SetCurrentTime(float value);
        float GetCurrentTime();

    private:
        float totalTimeSec;
        float currentTimeSec;

};
