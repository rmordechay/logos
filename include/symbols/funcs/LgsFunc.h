#pragma once
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsFuncType.h"

struct LgsFuncArg;
class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

typedef std::function<Value*(LgsLLVMGen&, const std::vector<LgsFuncArg>&)> CallFn;

class LgsFunc : public LgsExpr {
public:
    LgsFuncType* funcType;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<LgsExpr*> owners;
    std::vector<LgsExpr*> orphans;
    std::vector<LgsReturn*> returnStmts;
    BasicBlock* cleanupBlock = nullptr;
    Value* variadicCount = nullptr;
    bool hasDefers = false;
    bool isTest = false;
    bool isLambda = false;
    std::vector<std::pair<LgsExpr*, LgsExpr*>> mocks;
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
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, uint32_t ops);
    virtual Value* call(LgsLLVMGen& cg, std::vector<LgsFuncArg>& args);
    Value* callWithVariadic(LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args);
    Value* callIR(LgsLLVMGen& cg, const std::vector<Value*>& args = {});
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    void completeType(LgsType* toType) override;
    bool needsCleanup() const;
    std::string asText() override;
    LgsFunc* cloneExpr() override;
    void hashNode(size_t& oldHash) override;
    BasicBlock* getCleanupBlock(LgsLLVMGen& cg);
    void setDebugValue(LgsLLVMGen& cg) override;
    ~LgsFunc() override;
};
