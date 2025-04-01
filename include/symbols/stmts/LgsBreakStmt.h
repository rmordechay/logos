#ifndef LGSBREAK_H
#define LGSBREAK_H
#include "LgsStmt.h"

class LgsLoop;

class LgsBreakStmt final : public LgsStmt {
public:
    LgsLoop* loop = nullptr;

    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsBreakStmt() override = default;
};


#endif //LGSBREAK_H
