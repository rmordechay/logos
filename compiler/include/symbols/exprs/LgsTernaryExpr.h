#pragma once
#include "LgsExpr.h"

class LgsTernaryExpr final : public LgsExpr {
public:
    LgsExpr* condExpr;
    LgsExpr* thenExpr;
    LgsExpr* elseExpr;

    LgsTernaryExpr(LgsExpr* codeExpr, LgsExpr* thenExpr, LgsExpr* elseExpr)
        : condExpr(codeExpr), thenExpr(thenExpr), elseExpr(elseExpr) {
    }
    std::string asText() override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
};

inline std::string LgsTernaryExpr::asText() {
    assert(0);
}

inline Value* LgsTernaryExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}
