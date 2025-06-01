#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    std::vector<LgsVariable*> refs;

    explicit LgsVarDec(const std::string& name, LgsExpr* expr = nullptr) : name(name), expr(expr) {}
    void createIRStmt(Module* module) override;
    std::string format(std::string& indentStr) override;
    nlohmann::json asJSON() override;
    ~LgsVarDec() override;
};

#endif //LOGOSVARDEFINITION_H
