#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsParam.h"
#include "LgsValue.h"
#include "constants/LgsConstant.h"
#include "stmts/LgsStmtBlock.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsValue {
public:
    string name;
    string combinedName;
    LgsType* type;
    vector<LgsParam*> params;
    LgsStmtBlock* stmtBlock = nullptr;

    vector<Type*> IRParamsTypes;
    Function* IRFunc = nullptr;

    explicit LgsFunc(const string& name, LgsType* funcType) : name(name), type(funcType) {}
    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params) : name(name), type(funcType), params(params) {}
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) = 0;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
