#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
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
    virtual Function* getIRFunc(const CodeGenMetadata* metadata);
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args, Value* callback = nullptr);
    Value* setIRArgs(CodeGenMetadata* metadata, vector<Value*>& argValues, const vector<LgsExpr*>& args);
    virtual FunctionType* getIRFuncType(const CodeGenMetadata* metadata);
    virtual void setIRFuncParams(Argument* IRParams);
    void setStructRet(Function::arg_iterator& args, LgsObject* obj) const;
    string format(string& indentStr) override;
    json asJSON() override;
    virtual bool equals(const LgsFuncCall* funcCall) = 0;
    virtual LgsFuncType* getFuncType() = 0;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
