// file.cpp
#include "file.h"
#include <iostream>
#include <fstream>
#include "log.h"

std::vector<std::string> File::ReadTargetProcessNames(const std::string& configFile) {
    std::vector<std::string> targetProcessNames;

    // Open config file
    std::ifstream file(configFile);
    if (!file.is_open()) {
        // Display an error message and exit if file opening fails
        std::cerr << "Failed to open " << configFile << " file." << std::endl;
        Logger::getInstance("output.log").printAndLog("Failed to open "+ configFile + " file.");
        exit(1);
    }

    // Display header for better output readability
    // std::cout << ">>>--------------------" << std::endl;
    Logger::getInstance("output.log").printAndLog(">>>--------------------");
    std::string processName;
    // std::cout << "Target Process Names List:" << std::endl;
    Logger::getInstance("output.log").printAndLog("Target Process Names List:");


    // Read process names from file
    while (file >> processName) {
        targetProcessNames.push_back(processName);
        Logger::getInstance("output.log").printAndLog(processName);
        // std::cout << processName << std::endl;
    }

    // Display footer for better output readability
    // std::cout << "--------------------<<<" << std::endl;
    Logger::getInstance("output.log").printAndLog("--------------------<<<");
    file.close();
    return targetProcessNames;
}

time_t File::GetFileLastModifiedTime(const std::string& filePath) {
    WIN32_FILE_ATTRIBUTE_DATA fileAttr;
    
    // Retrieve file attributes, including last modification time
    if (GetFileAttributesEx(filePath.c_str(), GetFileExInfoStandard, &fileAttr) != 0) {
        ULARGE_INTEGER uli;
        uli.LowPart = fileAttr.ftLastWriteTime.dwLowDateTime;
        uli.HighPart = fileAttr.ftLastWriteTime.dwHighDateTime;
        return uli.QuadPart;
    }
    // Return 0 if file attributes retrieval fails
    return 0;
}