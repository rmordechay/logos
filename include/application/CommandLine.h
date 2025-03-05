#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <iostream>
#include <map>
#include "application/Application.h"
using namespace std;

class CommandLine {
public:
    string command;
    path rootPath;
    vector<string> commands;
    vector<string> flags;
    map<string, string> kvFlags;

    void parse(int argc, char* argv[]);
    void execute() const;
    void parseLongFlag(const string& arg);
    void runCommand() const;
    void buildCommand() const;
    static void helpCommand();
};

#endif //COMMANDLINE_H
