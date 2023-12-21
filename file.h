#pragma once
// file.h
#pragma once

#include <vector>
#include <string>
#include <windows.h>


class File {
public:
    // Function to read and print target process names from config.txt
    static std::vector<std::string> ReadTargetProcessNames(const std::string& configFile);

    // Function to get the last modification time of a file
    static time_t GetFileLastModifiedTime(const std::string& filePath);
};