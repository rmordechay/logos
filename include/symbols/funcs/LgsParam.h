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
    bool isVariadic = false;
    Value* vaList = nullptr;

    explicit LgsParam(LgsType* type = nullptr, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string getName() override;
    void parseAsJSON(std::stringstream& json) override;
    ~LgsParam() override = default;
};
