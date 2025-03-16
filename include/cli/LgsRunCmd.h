#ifndef LOGOSCMDRUN_H
#define LOGOSCMDRUN_H
#include "LgsCmd.h"

#include <string>

class LgsRunCmd final : public LgsCmd {
public:
    std::string rootPath;

    LgsRunCmd(const int argc, char** argv) : LgsCmd(argc, argv) {}
    void runCmd() override;
    void validate() override;
    void printHelp() override;
    ~LgsRunCmd() override = default;
};

#endif //LOGOSCMDRUN_H
