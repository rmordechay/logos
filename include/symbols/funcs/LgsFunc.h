#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtsBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

enum LgsFuncFlags : uint32_t {
    METHOD = 1 << 0,
    PUBLIC = 1 << 1,
    INTERNAL = 1 << 2,
    VIRTUAL = 1 << 3,
    STATIC = 1 << 4,
    VARIADIC = 1 << 5,
    HAS_DEFAULTS = 1 << 6,
    OPTIONAL = 1 << 7,
    TERMINATOR = 1 << 8,
};

class LgsFunc : public LgsUnaryExpr {
public:
    LgsFuncType* funcType;
    std::vector<LgsReturn*> returnStmts;
    LgsStmtsBlock* stmtsBlock = nullptr;
    bool hasDefers = false;

    explicit LgsFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes = {}, const uint32_t ops = 0) {
        funcType = new LgsFuncType();
        funcType->name = name;
        funcType->rt = rt;
        funcType->isMethod = ops & METHOD;
        funcType->isPublic = ops & PUBLIC;
        funcType->isInternal = ops & INTERNAL;
        funcType->isVirtual = ops & VIRTUAL;
        funcType->isStatic = ops & STATIC;
        funcType->isVariadic = ops & VARIADIC;
        funcType->hasDefaults = ops & HAS_DEFAULTS;
        funcType->isOptional = ops & OPTIONAL;
        funcType->isTerminator = ops & TERMINATOR;
        if (funcType->isMethod) {
            funcType->parentName = paramTypes.front()->getName();
        }
        for (const auto paramsType : paramTypes) {
            funcType->params.emplace_back(paramsType);
        }
        type = funcType;
    }

    std::string prettyName() override;
    std::string format(std::string& tabs) override;
    Value* createIRValue(LgsCodeGen* codeGen) override;
    Value* callIR(LgsCodeGen* codeGen, const std::vector<Value*>& args = {});
    void createPrologue(LgsCodeGen* codeGen);
    void createEpilogue(LgsCodeGen* codeGen) const;
    static Value* getIRArg(LgsCodeGen* codeGen, LgsExpr* arg);
    virtual Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args);
    virtual void generateIR(LgsCodeGen* codeGen);
    virtual Function* getIRFunc(LgsCodeGen* codeGen);
    ~LgsFunc() override;
};
