#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    vector<LgsVariable*> refs;

    explicit LgsVarDec(const string& name, LgsExpr* expr = nullptr) : name(name), expr(expr) {}
    Value* getIRValue(CodeGenMetadata* metadata) const;
    void createIRStmt(CodeGenMetadata* metadata) override;
    string format(string& indentStr) override;
    json asJSON() override;
    ~LgsVarDec() override;
};

#endif //LOGOSVARDEFINITION_H
