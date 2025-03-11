#ifndef LOGOSCMDRUN_H
#define LOGOSCMDRUN_H
#include "LogosCliCmd.h"

class LogosRunCmd final : public LogosCliCmd {
public:
    string rootPath;

    void init(int argc, char** argv) override;
    void runCmd() override;
    static void printHelp();
    static void exitWithHelp(const string& errMsg);
    ~LogosRunCmd() override = default;
};

#endif //LOGOSCMDRUN_H
