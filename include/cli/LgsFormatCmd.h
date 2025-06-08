#pragma once
#include "LgsCmd.h"
#include <filesystem>

class LgsFormatCmd final : public LgsCmd {
public:
    std::filesystem::path filePath;

    LgsFormatCmd(const int argc, char** argv) : LgsCmd(argc, argv) {}
    void runCmd() override;
    void validate() override;
    void printHelp() override;
    ~LgsFormatCmd() override = default;
};



