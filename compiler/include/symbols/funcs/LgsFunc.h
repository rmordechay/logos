#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsFuncType.h"

class LgsReturn;
class LgsFuncType;
struct LgsFuncArg;
class LgsStmtsBlock;
class LgsParam;
class LgsStmt;
class LgsType;

typedef std::function<Value*(LgsCgModule&, const std::vector<LgsFuncArg>&)> CallFn;

class LgsFunc : public LgsExpr {
public:
    LgsFuncType* funcType;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<const LgsReturn*> returnStmts;
    std::vector<std::pair<LgsExpr*, LgsExpr*>> mocks;
    BasicBlock* epilogue = nullptr;
    bool isLambda = false;
    bool isTest = false;
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
    explicit LgsFunc(const std::string& name, const std::string& parentName, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops = 0): LgsFunc(name, rt, paramTypes, ops) {
        funcType->parentName = parentName;
    }

    virtual Function* getIRFunc(LgsCgModule& cg);
    virtual Value* call(LgsCgModule& cg, std::vector<LgsFuncArg>& args);
    Value* callIR(LgsCgModule& cg, const std::vector<Value*>& args = {});
    Value* call(LgsCgModule& cg, const std::vector<LgsExpr*>& args);
    Value* callWithVariadic(LgsCgModule& cg, const std::vector<LgsFuncArg>& args);
    Value* loadIR(LgsCgModule& cg) override;
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, uint32_t ops);
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
    void setType(LgsType* newType) override;
    void hashNode(size_t& oldHash) override;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsFunc() override;
};
