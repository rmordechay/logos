#ifndef LOGOSCMDRUN_H
#define LOGOSCMDRUN_H
#include "LgsCmd.h"

#include <string>

class Logos;

class LgsRunCmd final : public LgsCmd {
public:
    std::string rootPath;

    LgsRunCmd(const int argc, char** argv) : LgsCmd(argc, argv) {}
    void setArgs(Logos* logos) const;
    void runCmd() override;
    void validate() override;
    void printHelp() override;
    ~LgsRunCmd() override = default;
};

#endif //LOGOSCMDRUN_H
