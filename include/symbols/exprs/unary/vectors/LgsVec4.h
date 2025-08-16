#pragma once
#include "LgsVec.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec4 final : public LgsVec {
public:
    LgsExpr* x = nullptr;
    LgsExpr* y = nullptr;
    LgsExpr* z = nullptr;
    LgsExpr* w = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsVec4() override;
};

inline LgsVec4::~LgsVec4() {
    if (x) {
        delete x;
        x = nullptr;
    }
    if (y) {
        delete y;
        y = nullptr;
    }
    if (z) {
        delete z;
        z = nullptr;
    }
    if (w) {
        delete w;
    }
}


