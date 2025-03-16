#ifndef LOGOSFUNC_H
#define LOGOSFUNC_H
#include "LgsParam.h"
#include "LgsValue.h"
#include "constants/LgsConst.h"
#include "stmts/LgsStmtBlock.h"

#include <LgsConfig.h>

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

    explicit LgsFunc(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {})
        : name(name), type(funcType), params(params) {
        setComposedName();
    }
    virtual Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) = 0;
    void setComposedName();
    Value* createIRValue(CodeGenMetadata* metadata) override;
    virtual void setIRFunc(CodeGenMetadata* metadata) = 0;
    ~LgsFunc() override;
};

inline void LgsFunc::setComposedName() {
    if (name == LOGOS_MAIN_FUNC) {
        composedName = name;
        return;
    }
    auto tempName = name;
    for (int i = 0; i < params.size(); ++i) {
        tempName += "_" + params[i]->type->getName();
    }
    composedName = tempName;
}

inline Value* LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    if (!IRFunc) setIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;
    const auto entryBlock = BasicBlock::Create(context, "entry");
    startBlock(metadata, entryBlock);
    stmtBlock->getIRValue(metadata);
    metadata->logosStack.exitScope();
    return IRFunc;
}

#endif //LOGOSFUNC_H
