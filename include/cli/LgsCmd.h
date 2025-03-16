#ifndef LGSCMD_H
#define LGSCMD_H

class LgsCmd {
public:
    int argc;
    char** argv;

    LgsCmd(const int argc, char** argv) : argc(argc), argv(argv) {};
    virtual void runCmd() = 0;
    virtual void validate() = 0;
    virtual void printHelp() = 0;
    virtual ~LgsCmd() = default;
};

#endif //LGSCMD_H
