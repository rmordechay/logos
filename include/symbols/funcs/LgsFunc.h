#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsUnaryExpr {
public:
    LgsFuncType funcType;
    vector<LgsVariable*> refs;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");
    string path;

    explicit LgsFunc() {
        type = &funcType;
    }
    void generateIRCode(CodeGenMetadata* metadata);
    virtual Function* getIRFunc(CodeGenMetadata* metadata);
    virtual FunctionType* getIRFuncType(const CodeGenMetadata* metadata);
    virtual Value* callIR(CodeGenMetadata* metadata, const vector<Value*>& args = {});
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args = {});
    void addIRArg(CodeGenMetadata* metadata, vector<Value*>& IRArgs, LgsExpr* arg) const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string prettyName() override;
    string format(string& tabs) override;
    json asJSON() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
