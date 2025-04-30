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
    LgsFuncSignature signature;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam>& params) : signature(LgsFuncSignature(name, funcType, params)) {}
    void generateIRCode(CodeGenMetadata* metadata);
    void setStructRet(Function::arg_iterator& args, LgsObject* obj) const;
    Function* getIRFunc(const CodeGenMetadata* metadata);
    string format(string& indentStr) override;
    json asJSON() override;
    virtual bool equals(const LgsFuncCall* funcCall) = 0;
    virtual bool equals(const LgsFuncSignature* other) = 0;
    virtual void setIRName() = 0;
    virtual void setIRFuncType(const CodeGenMetadata* metadata) = 0;
    virtual void setIRFuncParams(Argument* args) = 0;
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
