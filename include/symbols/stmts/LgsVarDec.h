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

    LgsVarDec(const string& name, LgsType* userType, LgsExpr* expr) : name(name), userType(userType), expr(expr) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    json asJson() override;
    ~LgsVarDec() override;
};




#endif //LOGOSVARDEFINITION_H
