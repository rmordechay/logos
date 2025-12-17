#pragma once
#include "LgsOwner.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include <LgsValue.h>

class LgsVariable;
class LgsExpr;
class LgsType;

class LgsParam final : public LgsValue, public LgsOwner {
public:
    std::string name;
    uint32_t index = 0;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isSelf = false;
    bool isOwner = true;
    bool isVariadic = false;

    explicit LgsParam(LgsType* type, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType);
    Value* loadIR(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    std::string getName() override;
    LgsType* getType() override;
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
