#pragma once
#include "LgsMock.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

using CallFn = std::function<Value*(LgsLLVM&, const std::vector<LgsExpr*>&)>;

class LgsFunc : public LgsUnaryExpr {
public:
    LgsFuncType* funcType;
    std::vector<LgsReturn*> returnStmts;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<LgsExpr*> heapAllocExprs;
    BasicBlock* cleanupBlock = nullptr;
    std::vector<LgsMock> mocks;
    bool hasDefers = false;
    CallFn fn;

    explicit LgsFunc(const std::string& name, LgsType* rt = nullptr, const std::vector<LgsType*>& paramTypes = {}, const uint32_t ops = 0) {
        initFunc(name, rt, paramTypes, ops);
    }
    explicit LgsFunc(LgsFuncType* funcType) : funcType(funcType) {}
    void setIRArgs(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args, std::vector<Value*>& IRArgs) const;
    virtual Value* call(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args);
    Value* callIR(LgsLLVM& codeGen, const std::vector<Value*>& args = {});
    virtual Function* getIRFunc(LgsLLVM& codeGen);
    static Value* loadIRArg(LgsLLVM* codeGen, Value* v, LgsType* type);
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops);
    BasicBlock* getCleanupBlock(LgsLLVM& codeGen);
    void completeType(LgsType* toType) override;
    bool needsCleanup() const;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* clone() override;
    void setDebugValue(LgsLLVM& codeGen) override;
    ~LgsFunc() override;
};
