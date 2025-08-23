#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/LgsDArray.h"
#include "types/LgsSArray.h"

class LgsArrayExpr final : public LgsUnaryExpr {
public:
    std::vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsSArray* arrType) : LgsUnaryExpr(arrType) {}
    explicit LgsArrayExpr(LgsDArray* arrType) : LgsUnaryExpr(arrType) {
        type->isHeapAlloc = true;
    }
    std::string pname() override;
    json::value asJSON() override;
    void completeType(LgsType* toType) override;
    ~LgsArrayExpr() override;
};
