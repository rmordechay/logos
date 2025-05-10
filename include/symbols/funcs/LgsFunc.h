#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsValue.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsFuncType.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsValue {
public:
    string path;
    LgsFuncType funcType;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    void generateIRCode(CodeGenMetadata* metadata);
    void setStructRet(Function::arg_iterator& args, LgsObject* obj) const;
    bool setIRArgs(CodeGenMetadata* metadata, vector<Value*>& argValues, const vector<LgsExpr*>& args) const;

    json asJSON() override;
    string format(string& tabs) override;
    virtual void setIRParams(Function* func, Argument* IRParams);
    virtual Function* createIRFunc(const CodeGenMetadata* metadata);
    virtual FunctionType* getIRFuncType(const CodeGenMetadata* metadata);
    virtual Value* makeCall(CodeGenMetadata* metadata, const vector<Value*>& args);
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
