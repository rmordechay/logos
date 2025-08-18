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
    bool hasDefers = false;

    explicit LgsFunc(const std::string& name, LgsType* rt = nullptr, const std::vector<LgsType*>& paramTypes = {}, const uint32_t ops = 0) {
        funcType = new LgsFuncType();
        funcType->name = name;
        funcType->rt = rt;
        funcType->setFuncOptions(ops);
        if (funcType->isMethod && !funcType->isStatic) {
            funcType->parentName = paramTypes.front()->getName();
        }
        for (const auto paramsType : paramTypes) {
            funcType->params.push_back(LgsParam(paramsType));
        }
        type = funcType;
    }

    Value* callIR(LgsCodeGen* codeGen, const std::vector<Value*>& args = {});
    void createPrologue(LgsCodeGen* codeGen);
    void createEpilogue(LgsCodeGen* codeGen) const;
    void createIRValue(LgsCodeGen* codeGen) override;
    void createDebugValue(LgsCodeGen* codeGen) override;
    bool castTo(LgsType* toType) override;
    std::string pname() override;
    json::value_ref asJSON() override;
    virtual Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args);
    virtual void generateIR(LgsCodeGen* codeGen);
    virtual Function* getIRFunc(LgsCodeGen* codeGen);
    static Value* getIRArg(LgsCodeGen* codeGen, LgsExpr* arg);
    ~LgsFunc() override;
};
