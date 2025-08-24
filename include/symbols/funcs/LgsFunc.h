#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

using CallFn = std::function<Value*(LgsCodeGen&, const std::vector<LgsExpr*>&)>;

class LgsFunc : public LgsUnaryExpr {
public:
    LgsFuncType* funcType;
    std::vector<LgsReturn*> returnStmts;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<LgsExpr*> heapAllocExprs;
    BasicBlock* cleanupBlock = nullptr;
    bool hasDefers = false;
    CallFn fn;

    explicit LgsFunc(const std::string& name, LgsType* rt = nullptr, const std::vector<LgsType*>& paramTypes = {}, const uint32_t ops = 0) {
        initFunc(name, rt, paramTypes, ops);
    }
    explicit LgsFunc(LgsFuncType* funcType) : funcType(funcType) {}
    void setIRArgs(LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args, std::vector<Value*>& IRArgs) const;
    virtual Value* call(LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args);
    Value* callIR(LgsCodeGen& codeGen, const std::vector<Value*>& args = {});
    virtual Function* getIRFunc(LgsCodeGen& codeGen);
    static Value* loadIRArg(LgsCodeGen* codeGen, Value* v, LgsType* type);
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops);
    BasicBlock* getCleanupBlock(LgsCodeGen& codeGen);
    void completeType(LgsType* toType) override;
    bool needsCleanup() const;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* clone() override;
    void setDebugValue(LgsCodeGen& codeGen) override;
    ~LgsFunc() override;
};
