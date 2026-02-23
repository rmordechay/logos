#pragma once
#include <LgsValue.h>
#include <string>
#include <vector>

#include "LgsType.h"
#include "exprs/LgsExpr.h"

class LgsVariable;
class LgsExpr;
class LgsType;
namespace llvm {
class Value;
}

class LgsParam final : public LgsValue {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    Value* level = nullptr;
    bool isSelf = false;
    bool isVariadic = false;

    explicit LgsParam(LgsType* type, const std::string& name = "", LgsExpr* expr = nullptr) : name(name), type(type), expr(expr) {}
    LgsType* getType() override;
    void setType(LgsType* newType) override;
    void setDebugValue(LgsCodeGen& cg) override;
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
