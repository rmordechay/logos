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
    size_t defersCounter = 0;

    explicit LgsFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params = {}) {
        funcType = new LgsFuncType();
        funcType->name = name;
        funcType->rt = rt;
        funcType->params = params;
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
