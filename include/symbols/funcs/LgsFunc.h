#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsFuncSignature.h"
#include "types/LgsType.h"
#include "LgsValue.h"
#include "stmts/LgsStmtBlock.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;
class LgsFunc : public LgsValue {
public:
    LgsFuncSignature signature;
    vector<Type*> IRParamsTypes;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) {
        signature.name = name;
        signature.rt = funcType;
        signature.params = params;
    }

    virtual void setIRFuncType() = 0;
    virtual void createIRValue(CodeGenMetadata* metadata);
    virtual Function* getIRFunc(const CodeGenMetadata* metadata);
    json asJson() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
