#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsFuncType.h"

class LgsStmtBlock;
class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsUnaryExpr {
public:
    LgsFuncType funcType;
    vector<LgsVariable*> refs;
    LgsStmtBlock* stmtBlock = nullptr;
    FunctionType* IRFuncType = nullptr;
    IRBuilderBase::InsertPoint savedIP;
    bool IRGenerated = false;
    string filePath;

    explicit LgsFunc(const bool IRGenerated = false): IRGenerated(IRGenerated) {
        type = &funcType;
    }
    Value* createIRValue(Module* module) override;
    string prettyName() override;
    string format(string& tabs) override;
    json asJSON() override;
    void addIRArg(Module* module, vector<Value*>& IRArgs, LgsExpr* arg) const;
    virtual void generateIRCode(Module* module);
    virtual Function* getIRFunc(Module* module);
    virtual FunctionType* getIRFuncType(const Module* module);
    virtual Value* callIR(Module* module, const vector<Value*>& args = {});
    virtual Value* call(Module* module, const vector<LgsExpr*>& args = {});
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
