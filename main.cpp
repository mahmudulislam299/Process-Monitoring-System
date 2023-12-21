#include <iostream>
#include <vector>
#include "file.h"
#include "process.h"
#include "log.h"

int main() {
    // Logger logger("output.log");
    Logger::getInstance("output.log").printAndLog("Program Started");
    std::string configFile = "config.txt";
    std::vector<std::string> targetProcessNames = File::ReadTargetProcessNames(configFile);

    Process::MonitorProcesses(targetProcessNames, configFile);

    return 0;
}
