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
    vector<LgsParam*> params;
    vector<Type*> IRParamsTypes;
    Function* IRFunc = nullptr;
    LgsStmtBlock* stmtBlock = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : params(params) {
        signature.name = name;
        signature.type = funcType;
    }
    void setComposedName();
    virtual void createIRValue(CodeGenMetadata* metadata);
    virtual void setIRFunc(CodeGenMetadata* metadata) = 0;
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {});
    json asJson() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
