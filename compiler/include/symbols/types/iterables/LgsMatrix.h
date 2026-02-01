#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"

#define CBLAS_ROW_MAJOR 101
#define CBLAS_NO_TRANS 111

class LgsMatrix final : public LgsIterable {
public:
    static constexpr auto name = "Mat";
    size_t rows;
    size_t columns;

    LgsMatrix(const size_t rows, const size_t columns): LgsIterable(&LGS_FLOAT), rows(rows), columns(columns) {
        passByRef = true;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getValueType() override;
    std::string getBaseName() override;
    std::string getName() override;
    bool canCastTo(LgsType* other) override;
    bool inferBaseType(std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    LgsType* applyMatScalarOp(LgsType* number, const LgsBinOp& op) const;
    LgsType* applyMatVecOp(const LgsVec* vec, const LgsBinOp& op) const;
    LgsType* applyMatMatOp(const LgsMatrix* otherMat, const LgsBinOp& op) const;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    std::string fmtStr() const override;
};
