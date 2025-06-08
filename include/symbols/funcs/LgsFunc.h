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
    LgsFunc* implementsFunc = nullptr;

    explicit LgsFunc(const string& name, LgsType* rt, const vector<LgsParam*>& params = {}) {
        type = &funcType;
        funcType.name = name;
        funcType.rt = rt;
        funcType.params = params;
    }
    explicit LgsFunc(const LgsFuncType* funcType) : LgsFunc(funcType->name, funcType->rt, funcType->params) {}
    void swapReturnIfNeeded();
    LgsParam* getReturnSwapParam() const;
    void setBigObjAttrs(Function& IRFunc) const;
    json asJSON() override;
    string prettyName() override;
    string format(string& tabs) override;
    Value* createIRValue(LgsRuntime* runtime) override;
    virtual void generateIR(LgsRuntime* runtime);
    virtual Function* getIRFunc(LgsRuntime* runtime);
    virtual Value* callIR(LgsRuntime* runtime, const vector<Value*>& args = {});
    virtual Value* call(LgsRuntime* runtime, const vector<LgsExpr*>& args = {});
    static bool shouldLoadIRArg(Value* value);
    static void addIRArg(LgsRuntime* runtime, vector<Value*>& IRArgs, Type* type, Value* value);
    ~LgsFunc() override;
};


