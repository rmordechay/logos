#pragma once
#include "LgsFunc.h"
#include "../types/LgsVoid.h"
#include "configs/LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    Function* IRFunc = nullptr;
    Value* argc = nullptr;
    Value* argv = nullptr;
    LgsArrayExpr* mainArgs = nullptr;
    LgsFunc* initArgsFunc = nullptr;

    explicit LgsMainFunc() : LgsFunc(LGS_MAIN_FUNC_NAME, &LGS_VOID, {}, PUBLIC) {}
    void setMainArgs();
    void initMainArgs(LgsLLVM& codeGen);
    Function* getIRFunc(LgsLLVM& codeGen) override;
    ~LgsMainFunc() override;
};
