#ifndef LGSMAINFUNC_H
#define LGSMAINFUNC_H
#include "LgsFuncImpl.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "types/primitives/LgsInt.h"


class LgsMainFunc final : public LgsFuncImpl {
public:
    Function* IRFunc = nullptr;

    explicit LgsMainFunc() : LgsFuncImpl(LOGOS_MAIN_FUNC, &LGS_INT) {}
    void generateIR(LgsRuntime* runtime) override;
    Function* getIRFunc(LgsRuntime* runtime) override;
    ~LgsMainFunc() override = default;
};

#endif //LGSMAINFUNC_H
