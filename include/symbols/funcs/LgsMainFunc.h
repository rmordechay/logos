#ifndef LGSMAINFUNC_H
#define LGSMAINFUNC_H
#include "LgsFuncImpl.h"
#include "stmts/LgsStmtBlock.h"
#include "types/primitives/LgsInt.h"
#include "logos/LgsGlobals.h"

class LgsMainFunc final : public LgsFuncImpl {
public:
    Function* IRFunc = nullptr;

    explicit LgsMainFunc() : LgsFuncImpl(LOGOS_MAIN_FUNC, &LGS_INT) {}
    void generateIRCode(Module* module) override;
    Function* getIRFunc(Module* module) override;
    ~LgsMainFunc() override = default;
};

#endif //LGSMAINFUNC_H
