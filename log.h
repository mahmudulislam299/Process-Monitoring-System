#ifndef LOG_H
#define LOG_H

#include <string>

class Logger {
public:
    static Logger& getInstance(const std::string& filename);
    void printAndLog(const std::string& message);

private:
    Logger(const std::string& filename);
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string getTimestamp();
    std::string filename;
};

#endif // LOG_H
