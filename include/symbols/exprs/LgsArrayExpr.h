#pragma once

#include "exprs/LgsExpr.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"

class LgsArrayExpr final : public LgsExpr {
public:
    std::vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsSArray* arrType) : LgsExpr(arrType) {}
    explicit LgsArrayExpr(LgsDArray* arrType) : LgsExpr(arrType) {
        type->isHeapAlloc = true;
    }
    std::string pname() override;
    json::value asJsonStr() override;
    void completeType(LgsType* toType) override;
    Value* loadIR(LgsLLVMGen& cg) override;
    ~LgsArrayExpr() override;
};
