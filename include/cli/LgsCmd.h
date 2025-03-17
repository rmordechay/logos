#ifndef LGSCMD_H
#define LGSCMD_H
#include <cstdlib>

class LgsCmd {
public:
    int argc;
    char** argv;

    LgsCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    void printInfoAndExit();
    virtual void runCmd() = 0;
    virtual void validate() = 0;
    virtual void printHelp() = 0;
    virtual ~LgsCmd() = default;
};

inline void LgsCmd::printInfoAndExit() {
    printHelp();
    exit(1);
}

#endif //LGSCMD_H
