#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"

class LgsMatrix final : public LgsIterable {
public:
    int32_t rows;
    int32_t columns;

    LgsMatrix(const int32_t rows, const int32_t columns): LgsIterable(&LGS_FLOAT), rows(rows), columns(columns) {
        passByRef = true;
    }
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    LgsType* applyMatScalarOp(LgsType* number, LgsBinOp& op);
    LgsType* applyMatVecOp(const LgsVec* vec, const LgsBinOp& op) const;
    LgsType* applyMatMatOp(LgsMatrix* otherMat, LgsBinOp& op);
    Value* mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
};
