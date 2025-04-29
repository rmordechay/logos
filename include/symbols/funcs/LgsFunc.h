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
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam>& params, const string& parentName = "") : signature(LgsFuncSignature(name, parentName, funcType, params)) {}

    void generateIRCode(CodeGenMetadata* metadata);
    void setSRet(Function::arg_iterator& args, LgsObject* obj) const;
    Function* getIRFunc(const CodeGenMetadata* metadata);
    string format(string& indentStr) override;
    json asJSON() override;
    virtual bool isEqual(const LgsFuncCall* funcCall) = 0;
    virtual bool isEqual(const LgsFuncSignature* other) = 0;
    virtual void setIRFuncType(const CodeGenMetadata* metadata) = 0;
    virtual void setIRFuncParams(Argument* args) = 0;
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
