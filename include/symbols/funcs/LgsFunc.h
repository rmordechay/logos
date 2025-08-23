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
    std::vector<LgsReturn*> returnStmts;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<LgsExpr*> heapAllocExprs;
    BasicBlock* cleanupBlock = nullptr;
    bool hasDefers = false;

    explicit LgsFunc(const std::string& name, LgsType* rt = nullptr, const std::vector<LgsType*>& paramTypes = {}, const uint32_t ops = 0) {
        initFunc(name, rt, paramTypes, ops);
    }
    explicit LgsFunc(LgsFuncType* funcType) : funcType(funcType) {}
    virtual Value* call(LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args);
    static Value* loadIRArg(LgsCodeGen* codeGen, Value* v, LgsType* type);
    virtual Function* getIRFunc(LgsCodeGen& codeGen);
    Value* callIR(LgsCodeGen& codeGen, const std::vector<Value*>& args = {});
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops);
    bool completeType(LgsType* toType) override;
    BasicBlock* getCleanupBlock(LgsCodeGen& codeGen);
    bool needsCleanup() const;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* clone() override;
    void setDebugValue(LgsCodeGen& codeGen) override;
    ~LgsFunc() override;
};
