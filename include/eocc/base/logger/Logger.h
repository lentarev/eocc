//
// Created by Egor Lentarev on 02.01.2026.
//

#ifndef EOCC_LOGGER_H
#define EOCC_LOGGER_H

#include <cstdio>

namespace eocc {

class Logger {
public:
    template <typename... Args>
    static void log(const unsigned int logLevel, Args... args) {
        if (logLevel <= mLogLevel) {
            std::printf(args...);
            // forced output for IDE
            std::fflush(stdout);
        }
    }

    static void setLogLevel(const unsigned int inLogLevel) { inLogLevel <= 9 ? mLogLevel = inLogLevel : mLogLevel = 9; }

private:
    static unsigned int mLogLevel;
};

}  // namespace eocc

#endif  // EOCC_LOGGER_H