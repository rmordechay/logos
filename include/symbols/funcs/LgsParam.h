#pragma once
#include "exprs/LgsExpr.h"
#include <LgsValue.h>

class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    bool isVariadic = false;
    llvm::Value* vaList = nullptr;

    explicit LgsParam(LgsType* type = nullptr, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    json::value asJSON() override;
    LgsParam clone() const;
};
