#pragma once
#include "LgsFunc.h"
#include "types/LgsVoid.h"
#include "data/LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    LgsArrayExpr* args = nullptr;

    explicit LgsMainFunc() : LgsFunc(LGS_MAIN_FUNC_NAME, &LGS_VOID, PUBLIC) {}
    Function* getIRFunc(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    ~LgsMainFunc() override;
};
