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
    LgsFuncType* funcType;
    vector<LgsExpr*> returnExprs;
    LgsStmtBlock* stmtBlock = nullptr;
    LgsFunc* implementsFunc = nullptr;

    explicit LgsFunc(const string& name, LgsType* rt, const vector<LgsParam>& params = {}) {
        funcType = new LgsFuncType();
        funcType->name = name;
        funcType->rt = rt;
        funcType->params = params;
        type = funcType;

    }
    explicit LgsFunc(LgsFuncType* funcType) : funcType(funcType) {
        type = funcType;
    }
    string prettyName() override;
    void setBigObjAttrs(Function& IRFunc) const;
    void swapReturnIfNeeded() const;
    LgsParam& getReturnSwapParam() const;
    void setExceptionFuncs(LgsModule* runtime) const;
    string format(string& tabs) override;
    Value* createIRValue(LgsModule* runtime) override;
    virtual void generateIR(LgsModule* runtime);
    virtual Type* getIRFuncType(LLVMContext& context);
    virtual Function* getIRFunc(LgsModule* runtime);
    virtual Value* callIR(LgsModule* runtime, const vector<Value*>& args = {});
    virtual Value* call(LgsModule* runtime, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};
