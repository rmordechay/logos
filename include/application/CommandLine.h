#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <iostream>
#include <map>
#include "application/Application.h"
using namespace std;

#if defined(_WIN32)
    #define OS_NAME "Windows"
#elif defined(__linux__)
    #define OS_NAME "Linux"
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "MacOS"
#elif defined(__unix__)
    #define OS_NAME "Unix"
#else
    #define OS_NAME "Unknown OS"
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH_NAME "x86_64 (64-bit)"
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCH_NAME "x86 (32-bit)"
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define ARCH_NAME "ARM64"
#elif defined(__arm__) || defined(_M_ARM)
    #define ARCH_NAME "ARM (32-bit)"
#else
    #define ARCH_NAME "Unknown Architecture"
#endif

class CommandLine {
public:
    string command;
    path rootPath;
    vector<string> commands;
    vector<string> flags;
    map<string, string> kvFlags;

    void parse(int argc, char* argv[]);
    void printVersion() const;
    void execute() const;
    void parseLongFlag(const string& arg);
    void runCommand() const;
    void buildCommand() const;
    static void helpCommand();
};

#endif //COMMANDLINE_H
