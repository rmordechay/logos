#pragma once
#include "LgsCmd.h"
#include "logos/LgsApp.h"

class LgsRunCmd final : public LgsCmd {
public:
    LgsRunCmd(const int argc, char** argv) : LgsCmd(argc, argv) {}
    void setArgs(LgsApp* app) const;
    void runCmd() override;
    void validate() override;
    void printHelp() override;
    ~LgsRunCmd() override = default;
};


