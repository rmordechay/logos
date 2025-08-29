#pragma once
#include "LgsMock.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

using CallFn = std::function<Value*(LgsLLVMGen&, const std::vector<LgsExpr*>&)>;

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
    void setIRArgs(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args, std::vector<Value*>& IRArgs) const;
    virtual Value* call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args);
    Value* callIR(LgsLLVMGen& cg, const std::vector<Value*>& args = {});
    virtual Function* getIRFunc(LgsLLVMGen& cg);
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops);
    BasicBlock* getCleanupBlock(LgsLLVMGen& cg);
    void completeType(LgsType* toType) override;
    bool needsCleanup() const;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* clone() override;
    void setDebugValue(LgsLLVMGen& cg) override;
    ~LgsFunc() override;
};
