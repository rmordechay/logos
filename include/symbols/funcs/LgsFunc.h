#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsParam.h"
#include "../types/LgsType.h"
#include "LgsValue.h"
#include "stmts/LgsStmtBlock.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsValue {
public:
    string name;
    string composedName;
    LgsType* type;
    vector<LgsParam*> params;
    vector<Type*> IRParamsTypes;
    Function* IRFunc = nullptr;
    LgsStmtBlock* stmtBlock = nullptr;
    BasicBlock* entryBlock = BasicBlock::Create(context, "entry");

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : name(name), type(funcType), params(params) {
        composedName = getComposedName(name, getParamTypeNames());
    }

    virtual void createIRValue(CodeGenMetadata* metadata);
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) = 0;
    virtual void setIRFunc(CodeGenMetadata* metadata) = 0;
    vector<string> getParamTypeNames() const;
    static string getComposedName(const string& name, const vector<string>& paramTypeNames);
    json asJson() override;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
