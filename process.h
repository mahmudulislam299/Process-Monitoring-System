#pragma once

#include <vector>
#include <string>
#include <windows.h>

class Process {
private:
    // Static member variable to define the interval for monitoring processes
    static int monitorProcessInterval;

public:
    // Function to start a new process
    static void StartNewProcess(const std::string& processName);

    // Function to check if a process is currently running
    static bool IsProcessRunning(const std::string& processName);

    // Function to monitor target processes
    static void MonitorProcesses(std::vector<std::string>& targetProcessNames, const std::string& configFile);

    // Public function to set the monitoring interval
    static void SetMonitorInterval(int interval);
};

