#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"

class LgsMatrix final : public LgsIterable {
public:
    size_t rows;
    size_t columns;

    LgsMatrix(const size_t rows, const size_t columns): LgsIterable(&LGS_DOUBLE), rows(rows), columns(columns) {}
    Type* getIRType(LgsLLVMGen& cg) override;
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    Lgs_TypeKind getRTTypeKind() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    std::string strFormatPart() const override;
    Value* lengthIR(LgsLLVMGen& cg, Value* iterable) override;
    Value* inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
};
