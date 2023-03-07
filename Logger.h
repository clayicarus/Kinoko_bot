//
// Created by clay on 3/6/23.
//

#ifndef ATRI_LOGGER_H
#define ATRI_LOGGER_H


#include <string>

class Logger {
public:
    static constexpr char DEBUG[] = "[DEBUG]";
    static constexpr char INFO[] = "[INFO]";
    static constexpr char WARN[] = "[WARN]";
    static constexpr char ERROR[] = "[ERROR]";
    static constexpr char FATAL[] = "[FATAL]";
    Logger(const char *level, const char *file, int line, const std::string &info) {
        if(level == DEBUG)
            return;
        printf("%s [%s:%d]  %s\n", level, file, line, info.c_str());
        if(level == FATAL)
            abort();
    }
};
#define LOG_DEBUG(debug) Logger(Logger::DEBUG, __FILE__, __LINE__, debug)
#define LOG_INFO(info) Logger(Logger::INFO, __FILE__, __LINE__, info)
#define LOG_WARN(warn) Logger(Logger::WARN, __FILE__, __LINE__, warn)
#define LOG_ERROR(error) Logger(Logger::ERROR, __FILE__, __LINE__, error)
#define LOG_FATAL(fatal) Logger(Logger::FATAL, __FILE__, __LINE__, fatal)

#endif //ATRI_LOGGER_H
