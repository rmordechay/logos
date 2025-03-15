#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsParam.h"
#include "LgsValue.h"
#include "constants/LgsConst.h"
#include "stmts/LgsStmtBlock.h"

class LgsParam;
class LgsExpr;
class LgsStmt;
class LgsType;

class LgsFunc : public LgsValue {
public:
    string name;
    string IRName;
    LgsType* type;
    vector<LgsParam*> params;
    vector<Type*> IRParamsTypes;
    Function* IRFunc = nullptr;
    LgsStmtBlock* stmtBlock = nullptr;

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : name(name), type(funcType), params(params) {}
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) = 0;
    virtual void setIRNames() = 0;
    ~LgsFunc() override;
};

#endif //LOGOSFUNC_H
