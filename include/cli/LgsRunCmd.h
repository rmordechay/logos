#ifndef LOGOSCMDRUN_H
#define LOGOSCMDRUN_H
#include <string>

class LgsRunCmd final {
public:
    std::string rootPath;

    void initRootPath(int argc, char** argv);
    void runCmd(int argc, char** argv);
    static void printHelp();
    ~LgsRunCmd() = default;
};

#endif //LOGOSCMDRUN_H
