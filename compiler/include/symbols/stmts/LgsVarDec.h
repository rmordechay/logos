#pragma once
#include <string>

#include "LgsStmt.h"
#include "exprs/LgsExpr.h"
#include "LgsValue.h"

class LgsExpr;
class LgsType;

namespace llvm {
    class Type;
}

class LgsVarDec final : public LgsStmt {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isNullable = false;
    bool isMutable = false;

    explicit LgsVarDec(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {}
    LgsVarDec(const std::string& name, LgsType* type, LgsExpr* expr) : name(name), type(type), expr(expr) {}
    LgsType* getType() override;
    void setType(LgsType* newType) override;
    void setDebugValue(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    LgsStmt* clone() const override;
};


