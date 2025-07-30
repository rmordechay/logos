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
    vector<LgsReturn*> returnExprs;
    vector<LgsExpr*> heapAllocExprs;
    LgsStmtsBlock* stmtBlock = nullptr;
    BasicBlock* cleanupBlock = nullptr;
    off_t pathIndex = 0;

    explicit LgsFunc(const string& name, LgsType* rt, const vector<LgsParam>& params = {}) {
        funcType = new LgsFuncType();
        funcType->name = name;
        funcType->rt = rt;
        funcType->params = params;
        type = funcType;
    }
    explicit LgsFunc(LgsFuncType* funcType) : LgsUnaryExpr(funcType), funcType(funcType) {}
    string prettyName() override;
    string format(string& tabs) override;
    void freeAllocations(LgsCodeGen* codeGen) const;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* callIR(LgsCodeGen* codeGen, const vector<Value*>& args = {});
    void createCleanupBlock(LgsCodeGen* codeGen) const;
    static Value* getIRArg(LgsCodeGen* codeGen, LgsExpr* arg);
    virtual Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args = {});
    virtual void generateIR(LgsCodeGen* codeGen);
    virtual Function* getIRFunc(LgsCodeGen* codeGen);
    ~LgsFunc() override;
};
