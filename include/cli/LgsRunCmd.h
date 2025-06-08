#pragma once
#include "LgsCmd.h"

class Logos;

class LgsRunCmd final : public LgsCmd {
public:
    LgsRunCmd(const int argc, char** argv) : LgsCmd(argc, argv) {}
    void setArgs(Logos* logos) const;
    void runCmd() override;
    void validate() override;
    void printHelp() override;
    ~LgsRunCmd() override = default;
};


