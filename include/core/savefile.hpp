#pragma once
#include "../master.hpp"


#define DEFAULT_SAVEFILE_PATH       "data/savefiles"
const int MAX_FILENAME_CHARS        = 3;


typedef struct MissionData {
    char fileName[MAX_FILENAME_CHARS];
    int score;

} MissionData;

typedef struct SaveFile {
    std::string filePath;

    std::vector<MissionData> missions;

} SaveFile;

bool CheckCurrentDir();
bool CheckSaveFile();

SaveFile LoadSaveFile();