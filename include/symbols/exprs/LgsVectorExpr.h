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
    Value* addIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* subIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* other) override;
    Value* divIR(LgsLLVMGen& cg, LgsExpr* other) override;
    std::string pname() override;
    json::value asJSON() override;
    ~LgsVectorExpr() override;
};
