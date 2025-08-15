#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsDeferStmt final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    Function* createThunkFunc(LgsCodeGen* codeGen, Type* ctxTy) const;
    Type* getCtxType(LgsCodeGen* codeGen) const;
    void generateIR(LgsCodeGen* codeGen) const;
    ~LgsDeferStmt() override;
};
