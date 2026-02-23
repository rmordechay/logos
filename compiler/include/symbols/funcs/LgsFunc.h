#pragma once
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "exprs/LgsExpr.h"
#include "types/LgsFuncType.h"
#include "codegen/LgsCodeGen.h"
#include "funcs/LgsParam.h"

class LgsReturn;
class LgsFuncType;
struct LgsFuncArg;
class LgsStmtsBlock;
class LgsParam;
class LgsStmt;
class LgsType;
namespace llvm {
class BasicBlock;
class Function;
class Value;
}

typedef std::function<Value*(LgsCodeGen&, const std::vector<LgsFuncArg>&)> CallFn;

class LgsFunc : public LgsExpr {
public:
    size_t id{};
    LgsFuncType* funcType;
    LgsStmtsBlock* stmtsBlock = nullptr;
    std::vector<const LgsReturn*> returnStmts;
    std::vector<std::pair<LgsExpr*, LgsExpr*>> mocks;
    BasicBlock* epilogue = nullptr;
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
    explicit LgsFunc(const std::string& name, const std::string& parentName, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops = 0) : LgsFunc(name, rt, paramTypes, ops) {
        funcType->parentName = parentName;
    }
    std::string asText() override;
    LgsExpr* cast(LgsType* toType, bool explicitly) override;
    void setType(LgsType* newType) override;
    virtual Function* getIRFunc(LgsCodeGen& cg);
    virtual Value* call(LgsCodeGen& cg, const std::vector<LgsFuncArg>& args);
    Value* callIR(LgsCodeGen& cg, const std::vector<Value*>& args = {});
    Value* callExternal(LgsCodeGen& cg, const std::vector<LgsFuncArg>& args);
    void replaceGenerics(const std::unordered_map<std::string, LgsType*>& replacements);
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, uint32_t ops);
    void setDebugValue(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    void inferRetType() const;
    ~LgsFunc() override;
};
