#pragma once
#include "LgsFunc.h"

class LgsCoroutine final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    Type* getCtxType(LgsCodeGen* codeGen) const;
    ~LgsCoroutine() override;
};
