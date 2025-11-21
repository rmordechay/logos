#include "types/iterables/LgsMatrix.h"
#include "exprs/LgsMatrixExpr.h"
#include "types/iterables/LgsVec.h"

Type* LgsMatrix::getIRType(LgsLLVMGen& cg) {
    return ArrayType::get(baseType->getIRType(cg), rows * columns);
}

size_t LgsMatrix::sizeBytes() {
    assert(0);
}

LgsType* LgsMatrix::applyBinOp(LgsType* toType, LgsBinOp& op) {
    if (toType->isNumber()) {
        return applyMatScalarOp(toType, op);
    }
    if (const auto vec = toType->asVec()) {
        return applyMatVecOp(vec, op);
    }
    if (const auto otherMat = toType->asMatrix()) {
        return applyMatMatOp(otherMat, op);
    }
    return nullptr;
}

LgsType* LgsMatrix::applyMatScalarOp(LgsType* number, LgsBinOp& op) {
    return nullptr;
}

LgsType* LgsMatrix::applyMatVecOp(const LgsVec* vec, const LgsBinOp& op) const {
    if (op.opType != MUL) return nullptr;
    if (vec->vectorDim != columns) return nullptr;
    return new LgsVec(rows, baseType);
}

LgsType* LgsMatrix::applyMatMatOp(LgsMatrix* otherMat, LgsBinOp& op) {
    return nullptr;
}

Value* LgsMatrix::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    return LgsIterable::mulIR(cg, left, right);
}

LgsExpr* LgsMatrix::getZeroValue() {
    return new LgsMatrixExpr(rows, columns);
}

Lgs_TypeKind LgsMatrix::getRTTypeKind() {
    assert(0);
}

std::string LgsMatrix::getName() {
    return "Mat" + std::to_string(rows) + "x" + std::to_string(columns);
}

bool LgsMatrix::canCastTo(LgsType* other) {
    if (getName() == other->getName()) return true;
    return false;
}

std::string LgsMatrix::strFormatPart() const {
    assert(0);
}

Value* LgsMatrix::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    assert(0);
}

Value* LgsMatrix::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}
