#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsVector.h"

class LgsVec2 final : public LgsUnaryExpr {
public:
    LgsExpr* x = nullptr;
    LgsExpr* y = nullptr;
    std::vector<LgsExpr*> args;

    LgsVec2() {
        type = new LgsVector(2);
        type->location = location;
    }

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsVec2() override = default;
};


