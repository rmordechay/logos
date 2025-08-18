#pragma once
#include "LgsCmd.h"

class LgsGenerateCmd final : public LgsCmd {
public:

    LgsGenerateCmd(const int argc, char** argv) : LgsCmd(argc, argv) {}
    void runCmd() override;
    void validate() override;
    void printHelp() override;
};




