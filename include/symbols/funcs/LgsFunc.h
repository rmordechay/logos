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
        initFunc(name, rt, paramTypes, ops);
    }
    explicit LgsFunc(LgsFuncType* funcType) : funcType(funcType) {}
    virtual Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args);
    virtual void generateIR(LgsCodeGen* codeGen);
    virtual Function* getIRFunc(LgsCodeGen* codeGen);
    void initFunc(const std::string& name, LgsType* rt, const std::vector<LgsType*>& paramTypes, const uint32_t ops);
    Value* callIR(LgsCodeGen* codeGen, const std::vector<Value*>& args = {});
    void createPrologue(LgsCodeGen* codeGen);
    void createEpilogue(LgsCodeGen* codeGen) const;
    void createIRValue(LgsCodeGen* codeGen) override;
    void createDebugValue(LgsCodeGen* codeGen) override;
    bool castTo(LgsType* toType) override;
    std::string pname() override;
    json::value asJSON() override;
    static Value* loadIRArg(LgsCodeGen* codeGen, Value* v, LgsType* type);
    ~LgsFunc() override;
};
