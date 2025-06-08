#pragma once
#include "LgsFunc.h"

#include "types/primitives/LgsInt.h"


class LgsMainFunc final : public LgsFunc {
public:
    Function* IRFunc = nullptr;
    Value* argc = nullptr;
    Value* argv = nullptr;
    LgsArrayExpr* args = nullptr;

    explicit LgsMainFunc() : LgsFunc(LOGOS_MAIN_FUNC, &LGS_INT) {}
    void initArgs(LgsRuntime* runtime);
    void generateIR(LgsRuntime* runtime) override;
    Function* getIRFunc(LgsRuntime* runtime) override;
    ~LgsMainFunc() override = default;
};


