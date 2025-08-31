#pragma once
#include "LgsUnaryExpr.h"
#include "exprs/LgsExpr.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"

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
    Value* loadIR(LgsLLVMGen& cg) override;
    ~LgsArrayExpr() override;
};
