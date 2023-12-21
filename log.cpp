#include "log.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <windows.h>


Logger& Logger::getInstance(const std::string& filename) {
    static Logger instance(filename);
    return instance;
}

Logger::Logger(const std::string& filename) : filename(filename) {}

Logger::~Logger() {}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now), "%Y-%m-%d %X");
    return ss.str();
}

void Logger::printAndLog(const std::string& message) {
    // Redirect std::cout to a file stream
    std::ofstream file(filename, std::ios_base::app); // Open file in append mode
    std::streambuf* stream_buffer_cout = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    // Log the message with timestamp
    file << "[" << getTimestamp() << "] " << message << std::endl;
    file.close();

    // Restore std::cout
    std::cout.rdbuf(stream_buffer_cout);

    // Print the message
    std::cout << message << std::endl;
}
