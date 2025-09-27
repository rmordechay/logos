#pragma once
#include "exprs/LgsExpr.h"
#include "types/iterables/LgsDArray.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsSet.h"

class LgsArrayExpr final : public LgsExpr {
public:
    std::vector<LgsExpr*> initialElements;

    explicit LgsArrayExpr(LgsSArray* arrType) : LgsExpr(arrType) {}
    explicit LgsArrayExpr(LgsDArray* arrType) : LgsExpr(arrType) {
        type->isHeapAlloc = true;
    }
    explicit LgsArrayExpr(LgsSet* setType) : LgsExpr(setType) {
        type->isHeapAlloc = true;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    void completeType(LgsType* toType) override;
    std::string pname() override;
    json::value asJsonStr() override;
    ~LgsArrayExpr() override;
};
