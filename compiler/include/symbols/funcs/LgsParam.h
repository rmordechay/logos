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
    Value* level = nullptr;
    bool isSelf = false;
    bool isVariadic = false;
    LgsGenericType* genericType = nullptr;

    explicit LgsParam(LgsType* type, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType);
    void setDebugValue(LgsCodeGen& cg) override;
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
