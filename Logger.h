//
// Created by clay on 3/6/23.
//

#ifndef ATRI_LOGGER_H
#define ATRI_LOGGER_H

#include <string>
// #include <vector>

class Logger {
public:
    static constexpr char DEBUG[] = "[DEBUG]";
    static constexpr char INFO[] = "[INFO]";
    static constexpr char WARN[] = "[WARN]";
    static constexpr char ERROR[] = "[ERROR]";
    static constexpr char FATAL[] = "[FATAL]";
    Logger(const char *level, const char *file, int line, const std::string &info) {
        std::string s;
        for(auto i : info) {
            switch (i) {
                case '\n':
                    s.append("\\n");
                    break;
                case '\t':
                    s.append("\\t");
                    break;
                case '\r':
                    s.append("\\r");
                    break;
                case '\0':
                    s.append("\\0");
                    break;
                default:
                    s.push_back(i);
            }
        }
        printf("%s [%s:%d]  %s\n", level, file, line, s.c_str());
        if(level == FATAL)
            abort();
    }
};
#define DEBUG_LOG(debug) Logger(Logger::DEBUG, __FILE__, __LINE__, debug)
#define INFO_LOG(info) Logger(Logger::INFO, __FILE__, __LINE__, info)
#define WARN_LOG(warn) Logger(Logger::WARN, __FILE__, __LINE__, warn)
#define ERROR_LOG(error) Logger(Logger::ERROR, __FILE__, __LINE__, error)
#define FATAL_LOG(fatal) Logger(Logger::FATAL, __FILE__, __LINE__, fatal)

#endif //ATRI_LOGGER_H
