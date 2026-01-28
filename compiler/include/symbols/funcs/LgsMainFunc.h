#pragma once
#include "LgsFunc.h"
#include "types/primitives/LgsVoid.h"
#include "LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    explicit LgsMainFunc() : LgsFunc(LGS_MAIN_FUNC, &LGS_VOID, PUBLIC) {}
    Function* getIRFunc(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
};
