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
    uint32_t index = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    bool isVariadic = false;

    explicit LgsParam(LgsType* type, const std::string& name, LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    void setType(LgsType* newType);
    LgsParam* clone() override;
    ~LgsParam() override = default;
};

void freeParams(std::vector<LgsParam>& params);
