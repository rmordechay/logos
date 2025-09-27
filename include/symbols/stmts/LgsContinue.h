#pragma once
#include "LgsStmt.h"

class LgsContinue final : public LgsStmt {
public:
    json::value asJsonStr() override;
};



