#pragma once
#include "exprs/LgsExpr.h"
#include <LgsValue.h>

class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    std::string name;
    // TODO free type and expr
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    bool isVariadic = false;
    llvm::Value* vaList = nullptr;

    explicit LgsParam(LgsType* type = nullptr, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value asJSON() override;
};
