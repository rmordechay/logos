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

    explicit LgsMainFunc() : LgsFunc(LGS_MAIN_FUNC_NAME, &LGS_VOID) {}
    void setMainArgs();
    void initMainArgs(LgsCodeGen* codeGen);
    void generateIR(LgsCodeGen* codeGen) override;
    Function* getIRFunc(LgsCodeGen* codeGen) override;
    ~LgsMainFunc() override;
};
