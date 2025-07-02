#pragma once
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreakStmt final : public LgsStmt {
public:
    std::string tag;

    explicit LgsBreakStmt(const std::string& tag = "") : tag(tag) {}
    void createIRStmt(LgsModule* module) override;
    ~LgsBreakStmt() override = default;
};



