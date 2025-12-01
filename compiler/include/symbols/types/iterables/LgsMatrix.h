#pragma once
#include "LgsIterable.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"

class LgsMatrix final : public LgsIterable {
public:
    size_t rows;
    size_t columns;

    LgsMatrix(const size_t rows, const size_t columns): LgsIterable(&LGS_FLOAT), rows(rows), columns(columns) {
        passByRef = true;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getValueType() override;
    std::string getName() override;
    std::string getGenericName() override;
    bool canCastTo(LgsType* other) override;
    bool inferBaseType(const std::vector<LgsExpr*>& args) override;
    Type* getIRType(LgsCgModule& cg) override;
    Constant* getRTType(LgsCgModule& cg) override;
    LgsType* applyBinOp(LgsType* toType, LgsBinOp& op) override;
    LgsType* applyMatScalarOp(const LgsType* number, const LgsBinOp& op) const;
    LgsType* applyMatVecOp(const LgsVec* vec, const LgsBinOp& op) const;
    LgsType* applyMatMatOp(const LgsMatrix* otherMat, const LgsBinOp& op) const;
    Value* getIRElement(LgsCgModule& cg, Value* iterable, Value* index) override;
    Value* mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) override;
    Value* inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) override;
    Value* lenIR(LgsCgModule& cg, Value* iterable) override;
    DIType* getDebugType(LgsCgModule& cg) override;
    std::string fmtStr() const override;
};
