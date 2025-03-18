#ifndef UTILS_H
#define UTILS_H

#include "Logos.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

inline string executeAndGetOutput(const string& command) {
    ostringstream outputBuffer;
    array<char, 128> buffer;
    const auto sFile = popen(command.c_str(), "r");
    const unique_ptr<FILE, decltype(&pclose)> pipe(sFile, pclose);
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        outputBuffer << buffer.data();
    }
    return outputBuffer.str();
}

#endif //UTILS_H
