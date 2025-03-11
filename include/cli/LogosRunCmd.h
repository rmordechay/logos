#ifndef LOGOSCMDRUN_H
#define LOGOSCMDRUN_H
#include <string>

class LogosRunCmd final {
public:
    std::string rootPath;

    void initRootPath(int argc, char** argv);
    void runCmd(int argc, char** argv);
    static void printHelp();
    ~LogosRunCmd() = default;
};

#endif //LOGOSCMDRUN_H
