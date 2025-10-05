#pragma once

#include "types/iterables/LgsVec.h"

class LgsVectorExpr final : public LgsExpr {
public:
    LgsVec* vecType;
    std::vector<LgsExpr*> args;

    explicit LgsVectorExpr(const int8_t dim) {
        isMutable = true;
        vecType = new LgsVec(dim);
        type = vecType;
    }

    explicit LgsVectorExpr(LgsVec* vecType): vecType(vecType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    Value* addIR(LgsLLVMGen& cg, Value* other) override;
    Value* subIR(LgsLLVMGen& cg, Value* other) override;
    Value* mulIR(LgsLLVMGen& cg, Value* other) override;
    Value* divIR(LgsLLVMGen& cg, Value* other) override;
    Value* dotProduct(LgsLLVMGen& cg, Value* lVec, Value* rVec) const;
    std::string getName() override;
    json::value asJsonStr() override;
    ~LgsVectorExpr() override;
};
