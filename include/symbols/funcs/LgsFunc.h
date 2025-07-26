#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsUnaryExpr {
public:
    LgsFuncType* funcType;
    vector<LgsExpr*> returnExprs;
    LgsStmtsBlock* stmtBlock = nullptr;
    BasicBlock* cleanupBlock = nullptr;
    vector<pair<BasicBlock*, Value*>> returnValues;

    explicit LgsFunc(const string& name, LgsType* rt, const vector<LgsParam>& params = {}) {
        funcType = new LgsFuncType();
        funcType->name = name;
        funcType->rt = rt;
        funcType->params = params;
        type = funcType;
    }
    explicit LgsFunc(LgsFuncType* funcType) : LgsUnaryExpr(funcType), funcType(funcType) {}
    string prettyName() override;
    void setBigObjAttrs(LgsModule* module, Function& IRFunc) const;
    void addReturnExpr(LgsModule* module, Value* rv);
    void createCleanupBlock(LgsModule* module);
    LgsParam& getReturnSwapParam() const;
    string format(string& tabs) override;
    Value* createIRValue(LgsModule* module) override;
    virtual void generateIR(LgsModule* module);
    virtual Function* getIRFunc(LgsModule* module);
    virtual Value* callIR(LgsModule* module, const vector<Value*>& args = {});
    virtual Value* call(LgsModule* module, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};
