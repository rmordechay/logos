#pragma once

enum LogLevel {
    INFO,
    DEBUG,
};

inline void lgsLog(const string& text, LogLevel level = INFO) {
    cout << text << std::endl;
}
