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

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam>& params, const string& parentName = "")
        : signature(LgsFuncSignature(name, parentName, funcType, params)) {}

    void generateIRCode(CodeGenMetadata* metadata);
    void setIRFuncType(const CodeGenMetadata* metadata);
    Function* getIRFunc(const CodeGenMetadata* metadata);
    virtual vector<Type*> getIRParamTypes(const CodeGenMetadata* metadata) = 0;
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {});
    string format(string& indentStr) override;
    json asJSON() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
