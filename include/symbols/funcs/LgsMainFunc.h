#pragma once
#include "LgsFunc.h"
#include "types/LgsVoid.h"
#include "data/LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    explicit LgsMainFunc() : LgsFunc(LGS_MAIN_FUNC, &LGS_VOID, PUBLIC) {}
    Function* getIRFunc(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
};
