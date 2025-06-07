#ifndef LGSCMD_H
#define LGSCMD_H
#include <iostream>
#include <string>

class LgsCmd {
public:
    int argc;
    char** argv;

    LgsCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    virtual void runCmd() = 0;
    virtual void validate() = 0;
    virtual void printHelp() = 0;
    void printInfoAndExit();
    void printInfoAndExit(const std::string& msg);
    virtual ~LgsCmd() = default;
};

inline void LgsCmd::printInfoAndExit() {
    printHelp();
    exit(1);
}

inline void LgsCmd::printInfoAndExit(const std::string& msg) {
    std::cout << msg << '\n';
    printInfoAndExit();
}

#endif //LGSCMD_H
