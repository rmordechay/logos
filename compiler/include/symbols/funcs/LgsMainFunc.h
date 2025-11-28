#pragma once
#include "LgsFunc.h"
#include "types/primitives/LgsVoid.h"
#include "LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    explicit LgsMainFunc() : LgsFunc(LGS_MAIN_FUNC, &LGS_VOID, PUBLIC) {}
    Function* getIRFunc(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
};
