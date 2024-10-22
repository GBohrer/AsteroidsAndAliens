#pragma once
#include "../master_header.h"


class Mission {

    public:
        Mission();

        void SetTotalTime(float value);
        float GetTotalTime();
        void SetCurrentTime(float value);
        float GetCurrentTime();
        int GetTotalAliensKill();
        void SetTotalAliensKill(int value);
        int GetCurrentAliensKill();
        void SetCurrentAliensKill(int value);

    private:
        float totalTimeSec;
        float currentTimeSec;
        int totalAliensKill;
        int currentAliensKill;

};
