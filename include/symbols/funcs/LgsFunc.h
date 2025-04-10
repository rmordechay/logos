#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsFuncSignature.h"
#include "LgsValue.h"
#include "stmts/LgsStmtBlock.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsValue {
public:
    string path;
    LgsFuncSignature signature;
    vector<Type*> IRParamsTypes;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam>& params, const string& parentName = "")
        : signature(LgsFuncSignature(name, parentName, funcType, params)) {}

    virtual void setIRFuncType() = 0;
    virtual void createIRValue(CodeGenMetadata* metadata);
    virtual Function* getIRFunc(const CodeGenMetadata* metadata);
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args);
    json asJson() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
