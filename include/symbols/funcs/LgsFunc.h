#pragma once
#include "types/LgsFuncType.h"

class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

using CallFn = std::function<Value*(LgsLLVMGen&, const std::vector<LgsExpr*>&)>;

class LgsFunc : public LgsExpr {
public:
    LgsFuncType* funcType;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<LgsExpr*> owners;
    std::vector<LgsExpr*> orphans;
    std::vector<LgsReturn*> returnStmts;
    BasicBlock* cleanupBlock = nullptr;
    bool hasDefers = false;
    bool isTest = false;
    bool isLambda = false;
    CallFn fn;

    explicit LgsFunc(const std::string& name, LgsType* rt = nullptr, const std::vector<LgsType*>& paramTypes = {}, const uint32_t ops = 0) {
        initFunc(name, rt, paramTypes, ops);
    }
    explicit LgsFunc(LgsFuncType* funcType) : funcType(funcType) {}
    virtual Function* getIRFunc(LgsLLVMGen& cg);
    virtual Value* call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args);
    Value* callIR(LgsLLVMGen& cg, const std::vector<Value*>& args = {});
    Value* loadIR(LgsLLVMGen& cg) override;
    void setIRArgs(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args, std::vector<Value*>& IRArgs);
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, uint32_t ops);
    void setDebugValue(LgsLLVMGen& cg) override;
    void completeType(LgsType* toType) override;
    LgsExpr* castTo(LgsType* toType) override;
    BasicBlock* getCleanupBlock(LgsLLVMGen& cg);
    bool needsCleanup() const;
    std::string pname() override;
    json::value asJSON() override;
    LgsExpr* clone() override;
    ~LgsFunc() override;
};
