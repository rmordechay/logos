#pragma once

enum LogLevel {
    INFO,
    DEBUG,
    ERROR,
};

void lgsLog(const string& text, LogLevel level = INFO);
