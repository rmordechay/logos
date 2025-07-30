#pragma once
#include "LgsFunc.h"
#include "../types/LgsVoid.h"
#include "configs/LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    Function* IRFunc = nullptr;
    Value* argc = nullptr;
    Value* argv = nullptr;
    LgsArrayExpr* args = nullptr;
    LgsFunc* initArgsFunc = nullptr;

    explicit LgsMainFunc() : LgsFunc(LOGOS_MAIN_FUNC_NAME, &LGS_VOID) {}
    void setArgs();
    void initArgs(LgsModule* module);
    void generateIR(LgsModule* module) override;
    Function* getIRFunc(LgsModule* module) override;
    ~LgsMainFunc() override;
};


