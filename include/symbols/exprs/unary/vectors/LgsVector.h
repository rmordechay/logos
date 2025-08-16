#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsVec2.h"

class LgsVector final : public LgsUnaryExpr {
public:
    size_t vecSize = 0;
    std::vector<LgsExpr*> args;

    void createIRValue(LgsCodeGen* codeGen) override;
    LgsField* getScalars(const std::string& fieldName);
    std::string pname() override;
    ~LgsVector() override = default;
};
