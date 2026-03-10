#pragma once
#include <string>
#include <__functional/function.h>

#include "LgsIterable.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsFloat.h"
#include "Lgs_Types.h"

class LgsType;
class LgsVec;
struct LgsBinOp;

#define CBLAS_ROW_MAJOR 101
#define CBLAS_NO_TRANS 111

class LgsMatrix final : public LgsIterable {
public:
    static constexpr auto name = "Mat";
    size_t rows;
    size_t columns;

    LgsMatrix(const size_t rows, const size_t columns): LgsIterable(&LGS_FLOAT), rows(rows), columns(columns) {
        passByRef = true;
        rttKind = RTT_MATRIX;
    }
    size_t sizeBytes() override;
    LgsExpr* getZeroValue() override;
    LgsType* getValueType() override;
    std::string getBaseName() override;
    std::string getName() override;
    std::string fmtStr() const override;
    bool canCastTo(LgsType* other) override;
    Type* getIRType(LgsCodeGen& cg) override;
    LgsType* applyBinOp(LgsType* rightType, LgsBinOp& op) override;
    LgsType* applyMatScalarOp(LgsType* number, const LgsBinOp& op) const;
    LgsType* applyMatVecOp(const LgsVec* vec, const LgsBinOp& op) const;
    Value* getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) override;
    LgsType* applyMatMatOp(const LgsMatrix* otherMat, const LgsBinOp& op) const;
    Value* getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) override;
    Value* addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* mulIRMatMat(LgsCodeGen& cg, const LgsBinaryExpr* binExpr);
    Value* divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) override;
    Value* inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) override;
    Value* lenIR(LgsCodeGen& cg, Value* iterable) override;
    Constant* getRTTypeExtra(LgsCodeGen& cg) override;
    DIType* getDebugType(LgsCodeGen& cg) override;
    std::pair<Value*, Value*> loadMatOperands(LgsCodeGen& cg, const LgsBinaryExpr* binExpr);
    Value* applyElemWise(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(Value*, Value*)>& intOp, const std::function<Value*(Value*, Value*)>& floatOp);
};
