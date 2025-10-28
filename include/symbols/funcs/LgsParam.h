#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsInterface.h"

#include <LgsValue.h>

class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    Value* vaList = nullptr;
    bool isVariadic = false;

    explicit LgsParam(LgsType* type, const std::string& name, LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    void setType(LgsType* newType);
    ~LgsParam() override = default;
};
