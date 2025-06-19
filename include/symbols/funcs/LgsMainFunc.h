#pragma once
#include "LgsFunc.h"
#include "types/primitives/LgsVoid.h"
#include "data/LgsDefinitions.h"

class LgsMainFunc final : public LgsFunc {
public:
    Function* IRFunc = nullptr;
    Value* argc = nullptr;
    Value* argv = nullptr;
    LgsArrayExpr* args = nullptr;
    LgsFunc* initArgsFunc = nullptr;

    explicit LgsMainFunc() : LgsFunc(LOGOS_MAIN_FUNC, &LGS_VOID) {}
    void setArgs();
    void initArgs(LgsRuntime* runtime);
    void generateIR(LgsRuntime* runtime) override;
    Function* getIRFunc(LgsRuntime* runtime) override;
    ~LgsMainFunc() override;
};


