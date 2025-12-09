#pragma once
#include "LgsType.h"
#include "exprs/LgsExpr.h"
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

    explicit LgsParam(LgsType* type, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    Value* loadIR(LgsCgModule& cg) override;
    void setType(LgsType* newType);
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsParam() override = default;
};

inline void freeParams(std::vector<LgsParam>& params) {
    for (const auto& param : params) {
        if (param.isSelf) continue;
        if (param.expr) {
            freeExpr(param.expr);
        }
        freeType(param.type);
    }
    params.clear();
}
