#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LgsStmt.h"
#include "LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    string name;
    LgsType* type = nullptr;
    LgsType* userType = nullptr;
    LgsExpr* expr = nullptr;

    LgsVarDec(const string& name, LgsType* userType, LgsExpr* expr) : name(name), userType(userType), expr(expr) {}
    LgsVarDec(const string& name, LgsType* inferredType) : name(name), type(inferredType){}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsVarDec() override;
};




#endif //LOGOSVARDEFINITION_H
