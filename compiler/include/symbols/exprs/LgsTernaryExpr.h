#pragma once
#include <string>

#include "LgsExpr.h"

class LgsTernaryExpr final : public LgsExpr {
public:
    LgsExpr* condExpr;
    LgsExpr* thenExpr;
    LgsExpr* elseExpr;

    LgsTernaryExpr(LgsExpr* codeExpr, LgsExpr* thenExpr, LgsExpr* elseExpr) : condExpr(codeExpr), thenExpr(thenExpr), elseExpr(elseExpr) {}
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsTernaryExpr() override;
};
