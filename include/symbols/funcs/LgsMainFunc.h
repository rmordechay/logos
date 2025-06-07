#ifndef LGSMAINFUNC_H
#define LGSMAINFUNC_H
#include "LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "types/primitives/LgsInt.h"


class LgsMainFunc final : public LgsFunc {
public:
    Function* IRFunc = nullptr;
    Value* argc = nullptr;
    Value* argv = nullptr;

    explicit LgsMainFunc() : LgsFunc(LOGOS_MAIN_FUNC, &LGS_INT) {}
    void generateIR(LgsRuntime* runtime) override;
    Function* getIRFunc(LgsRuntime* runtime) override;
    ~LgsMainFunc() override = default;
};

#endif //LGSMAINFUNC_H
