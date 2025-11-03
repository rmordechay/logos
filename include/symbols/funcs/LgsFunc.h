#pragma once
#include "stmts/LgsStmtsBlock.h"
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
    Value* variadicCount = nullptr;
    std::vector<std::pair<LgsExpr*, LgsExpr*>> mocks;
    bool hasDefers = false;
    bool isTest = false;
    bool isLambda = false;
    CallFn fn;

    explicit LgsFunc(LgsFuncType* funcType) : LgsExpr(funcType), funcType(funcType) {}
    explicit LgsFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, const uint32_t ops = 0) {
        initFunc(name, rt, params, ops);
    }
    explicit LgsFunc(const std::string& name, LgsType* rt, const uint32_t ops = 0) {
        initFunc(name, rt, {}, ops);
    }
    explicit LgsFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops = 0) {
        std::vector<LgsParam> params;
        for (const auto paramType : paramTypes) {
            params.push_back(LgsParam(paramType, ""));
        }
        initFunc(name, rt, params, ops);
    }

    virtual Function* getIRFunc(LgsLLVMGen& cg);
    virtual Value* call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args, const std::vector<LgsType*>& generics = {});
    Value* callIR(LgsLLVMGen& cg, const std::vector<Value*>& args = {});
    Value* loadIR(LgsLLVMGen& cg) override;
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, uint32_t ops);
    void setDebugValue(LgsLLVMGen& cg) override;
    void completeType(LgsType* toType) override;
    BasicBlock* getCleanupBlock(LgsLLVMGen& cg);
    bool needsCleanup() const;
    std::string asText() override;
    std::string getIRName() const;
    void hashNode(size_t& oldHash) override;
    LgsFunc* cloneExpr() override;
    ~LgsFunc() override;
};
