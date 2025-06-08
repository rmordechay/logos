#pragma once
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
    LgsFunc* implementsFunc = nullptr;

    explicit LgsFunc(const string& name, LgsType* rt, const vector<LgsParam*>& params = {}) {
        type = &funcType;
        funcType.name = name;
        funcType.rt = rt;
        funcType.params = params;
    }
    explicit LgsFunc(const LgsFuncType* funcType) : LgsFunc(funcType->name, funcType->rt, funcType->params) {}
    static bool shouldLoadIRArg(Value* value);
    void setBigObjAttrs(LgsRuntime* runtime, Function& IRFunc) const;
    void swapReturnIfNeeded();
    LgsParam* getReturnSwapParam() const;
    static void addIRArg(LgsRuntime* runtime, vector<Value*>& IRArgs, Type* type, Value* value);
    Value* createIRValue(LgsRuntime* runtime) override;
    string format(string& tabs) override;
    string prettyName() override;
    json asJSON() override;
    virtual void generateIR(LgsRuntime* runtime);
    virtual Function* getIRFunc(LgsRuntime* runtime);
    virtual Value* callIR(LgsRuntime* runtime, const vector<Value*>& args = {});
    virtual Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};


