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
    Value* vaList = nullptr;

    explicit LgsParam(LgsType* type = nullptr, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    LgsParam(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {}
    std::string format(std::string& indentStr) override;
    Value* getIRValue(LgsCodeGen* codeGen);
    std::string getIRName();
    ~LgsParam() override = default;
};
