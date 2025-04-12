#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    string name;
    LgsType* type = nullptr;
    LgsType* userType = nullptr;
    LgsExpr* expr = nullptr;
    vector<LgsVariable*> refs;

    LgsVarDec(const string& name, LgsType* type, LgsExpr* expr) : name(name), type(type), expr(expr) {}
    explicit LgsVarDec(const string& name, LgsExpr* expr = nullptr) : name(name), expr(expr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsVarDec() override;
};




#endif //LOGOSVARDEFINITION_H
