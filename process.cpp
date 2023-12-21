// process.cpp
#include "process.h"
#include "file.h"
#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include "log.h"

#pragma comment(lib, "Psapi.lib")

// Initialize the static member variable with the desired interval (milliseconds)
int Process::monitorProcessInterval = 500;

void Process::StartNewProcess(const std::string& processName) {
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    // Attempt to create a new process
    if (CreateProcess(NULL, const_cast<char*>(processName.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        // std::cout << "Started new process: " << processName << std::endl;
        Logger::getInstance("output.log").printAndLog("Started new process: "+ processName );

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        // Display an error message if process creation fails
        // std::cerr << "Failed to start new process: " << processName << std::endl;
        Logger::getInstance("output.log").printAndLog("Failed to start new process: ");
    }
}

bool Process::IsProcessRunning(const std::string& processName) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) {
        // Display an error message and exit if snapshot creation fails
        // std::cerr << "Failed to create process snapshot. Error code: " << GetLastError() << std::endl;
        Logger::getInstance("output.log").printAndLog("Failed to create process snapshot. Error code: " + GetLastError());
        
        exit(1);
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(snapshot, &processEntry)) {
        do {
            // Check if the process is running by comparing names
            if (_stricmp(processEntry.szExeFile, processName.c_str()) == 0) {
                CloseHandle(snapshot);
                return true;  // Process is running
            }
        } while (Process32Next(snapshot, &processEntry));
    }

    CloseHandle(snapshot);
    return false;  // Process is not running
}

void Process::MonitorProcesses(std::vector<std::string>& targetProcessNames, const std::string& configFile) {
    time_t lastModifiedTime = 0;

    while (true) {
        // Check for changes in the config.txt file
        time_t currentModifiedTime = File::GetFileLastModifiedTime(configFile);
        if (currentModifiedTime != lastModifiedTime) {
            // File has been modified; update the target process names
            lastModifiedTime = currentModifiedTime;
            // std::cout << "Config file has been modified. Updating target processes." << std::endl;
              Logger::getInstance("output.log").printAndLog("Config file has been modified. Updating target processes." );
            targetProcessNames = File::ReadTargetProcessNames(configFile);
        }

        for (const auto& targetProcessName : targetProcessNames) {
            if (!Process::IsProcessRunning(targetProcessName)) {
                // Target process not running; start a new process
                Process::StartNewProcess(targetProcessName);
            }
        }

        Sleep(monitorProcessInterval);
    }
}


void Process::SetMonitorInterval(int interval) {
    // Set the new monitoring interval
    monitorProcessInterval = interval;
}
