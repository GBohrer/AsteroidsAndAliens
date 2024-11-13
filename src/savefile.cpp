#include "../include/master.hpp"


bool CheckCurrentDir() {
    std::cout << "Diretório atual: " << std::filesystem::current_path() << std::endl;
    return 0;
}

bool CheckSaveFile() {
    std::string path = DEFAULT_SAVEFILE_PATH;

    if (!std::filesystem::exists(path)) {
        std::cerr << "O diretório não existe: " << path << std::endl;
        return false;
    }

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() == ".bin")
            return true;
    }
    return false;
}

SaveFile LoadSaveFile() {
    if (!CheckSaveFile()){
        //CreateSaveFile();
    }
    SaveFile sf;
    return sf;
}
