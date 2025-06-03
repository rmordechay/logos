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
    IRBuilderBase::InsertPoint savedIP;
    string filePath;

    explicit LgsFunc() {
        type = &funcType;
    }

    Value* createIRValue(LgsRuntime* runtime) override;
    string prettyName() override;
    string format(string& tabs) override;
    json asJSON() override;
    void addIRArg(LgsRuntime* runtime, vector<Value*>& IRArgs, LgsExpr* arg) const;
    virtual void generateIR(LgsRuntime* runtime);
    virtual Function* getIRFunc(LgsRuntime* runtime);
    virtual FunctionType* getIRFuncType(LgsRuntime* runtime);
    virtual Value* callIR(LgsRuntime* runtime, const vector<Value*>& args = {});
    virtual Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
