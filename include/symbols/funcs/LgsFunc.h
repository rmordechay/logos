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
    string filePath;
    LgsFuncType funcType;
    vector<LgsVariable*> refs;
    vector<LgsExpr*> returnExprs;
    LgsStmtBlock* stmtBlock = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    LgsFunc* implements = nullptr;

    explicit LgsFunc(const string& name, LgsType* rt, const vector<LgsParam*>& params = {}) {
        type = &funcType;
        funcType.name = name;
        funcType.rt = rt;
        funcType.params = params;
    }

    Value* createIRValue(LgsRuntime* runtime) override;
    string prettyName() override;
    void setBigObjAttrs(Function& IRFunc) const;
    string format(string& tabs) override;
    json asJSON() override;
    void addIRArg(LgsRuntime* runtime, vector<Value*>& IRArgs, LgsExpr* arg) const;
    bool shouldLoadIRArg(Value* value) const;
    LgsParam* getReturnParam() const;
    void swapReturnIfNeeded();
    virtual void generateIR(LgsRuntime* runtime);
    virtual Function* getIRFunc(LgsRuntime* runtime);
    virtual Value* callIR(LgsRuntime* runtime, const vector<Value*>& args = {});
    virtual Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
