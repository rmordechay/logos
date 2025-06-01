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
    void generateIRCode(CodegenMetadata* metadata);
    virtual Function* getIRFunc(CodegenMetadata* metadata);
    virtual FunctionType* getIRFuncType(const CodegenMetadata* metadata);
    virtual Value* callIR(CodegenMetadata* metadata, const vector<Value*>& args = {});
    virtual Value* call(CodegenMetadata* metadata, const vector<LgsExpr*>& args = {});
    void addIRArg(CodegenMetadata* metadata, vector<Value*>& IRArgs, LgsExpr* arg) const;
    Value* createIRValue(CodegenMetadata* metadata) override;
    string prettyName() override;
    string format(string& tabs) override;
    json asJSON() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
