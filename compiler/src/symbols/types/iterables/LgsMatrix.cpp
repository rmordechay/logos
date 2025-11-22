#include "types/iterables/LgsMatrix.h"
#include "cblas/cblas.h"
#include "exprs/LgsMatrixExpr.h"
#include "types/LgsAny.h"
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

LgsType* LgsMatrix::applyMatScalarOp(const LgsType* number, const LgsBinOp& op) const {
    if (!number->isNumber()) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case MUL:
    case DIV:
        return new LgsMatrix(rows, columns);
    default:
        return nullptr;
    }
}

LgsType* LgsMatrix::applyMatVecOp(const LgsVec* vec, const LgsBinOp& op) const {
    if (op.opType != MUL) return nullptr;
    if (vec->vectorDim != columns) return nullptr;
    return new LgsVec(rows, baseType);
}

LgsType* LgsMatrix::applyMatMatOp(const LgsMatrix* otherMat, const LgsBinOp& op) const {
    if (columns != otherMat->rows) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
        if (rows != otherMat->rows || columns != otherMat->columns) return nullptr;
        return new LgsMatrix(rows, columns);
    case MUL:
        return new LgsMatrix(rows, otherMat->columns);
    default:
        return nullptr;
    }
}

Value* LgsMatrix::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto leftMat = left->type->asMatrix();
    const auto rightMat = right->type->asMatrix();
    const auto order = cg.i32(CblasRowMajor);
    const auto transpose = cg.i32(CblasNoTrans);
    const auto M = cg.i32(leftMat->rows);
    const auto N = cg.i32(rightMat->columns);
    const auto K = cg.i32(leftMat->columns);
    const auto alpha = cg.floatv(1);
    const auto A = left->IRValue;
    const auto B = right->IRValue;
    const auto beta = cg.floatv(0);
    const auto results = cg.builder.CreateAlloca(getIRType(cg));
    const auto ft = cg.getFT(cg.voidTy(), {
        cg.i32Ty(),
        cg.i32Ty(),
        cg.i32Ty(),
        cg.i32Ty(),
        cg.i32Ty(),
        cg.i32Ty(),
        cg.floatTy(),
        cg.ptrTy(),
        cg.i32Ty(),
        cg.ptrTy(),
        cg.i32Ty(),
        cg.floatTy(),
        cg.ptrTy(),
        cg.i32Ty(),
    });
    const std::vector<Value*> args = {
        order, transpose, transpose, M, N, K, alpha, A, K, B, N, beta, results, N
    };
    cg.builder.CreateCall(cg.getFunc("cblas_sgemm", ft), args);
    return results;
}

LgsExpr* LgsMatrix::getZeroValue() {
    return new LgsMatrixExpr(rows, columns);
}

Lgs_TypeKind LgsMatrix::getRTTypeKind() {
    return RTT_MATRIX;
}

std::string LgsMatrix::getName() {
    return "Mat" + std::to_string(rows) + "x" + std::to_string(columns);
}

bool LgsMatrix::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (getName() == other->getName()) return true;
    return false;
}

std::string LgsMatrix::strFormatPart() const {
    assert(0);
}

Value* LgsMatrix::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(baseType->getIRType(cg), gep);
}

Value* LgsMatrix::lenIR(LgsLLVMGen& cg, Value* iterable) {
    return cg.i32(rows);
}

Value* LgsMatrix::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}
