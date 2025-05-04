#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "../types/LgsFuncType.h"
#include "LgsValue.h"
#include "stmts/LgsStmtBlock.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsValue {
public:
    string path;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    void generateIRCode(CodeGenMetadata* metadata);
    string format(string& indentStr) override;
    json asJSON() override;
    virtual bool equals(const LgsFuncCall* funcCall) = 0;
    virtual LgsFuncType* getFuncType() = 0;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
