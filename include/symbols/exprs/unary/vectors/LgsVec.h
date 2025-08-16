#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec : public LgsUnaryExpr {
public:
    std::vector<LgsExpr*> args;
    ~LgsVec() override;
};

inline LgsVec::~LgsVec() {
    for (const auto arg : args) {
        delete arg;
    }
    args.clear();
}
