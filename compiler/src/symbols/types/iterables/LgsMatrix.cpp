#include "types/iterables/LgsMatrix.h"

#include "LgsBinaryTokens.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsMatrixExpr.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsVec.h"

Type* LgsMatrix::getIRType(LgsCodeGen& cg) {
    return ArrayType::get(baseType->getIRType(cg), rows * columns);
}

size_t LgsMatrix::sizeBytes() {
    return rows * columns * baseType->sizeBytes();
}

LgsType* LgsMatrix::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (rightType->isNumber()) {
        return applyMatScalarOp(rightType, op);
    }
    if (const auto vec = rightType->asVec()) {
        return applyMatVecOp(vec, op);
    }
    if (const auto otherMat = rightType->asMatrix()) {
        return applyMatMatOp(otherMat, op);
    }
    return nullptr;
}

LgsType* LgsMatrix::applyMatScalarOp(LgsType* number, const LgsBinOp& op) const {
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
    if (vec->dimVec != columns) return nullptr;
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

Value* LgsMatrix::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto leftMat = left->type->asMatrix();
    const auto rightMat = right->type->asMatrix();
    const auto order = cg.i32(CBLAS_ROW_MAJOR);
    const auto noTranspose = cg.i32(CBLAS_NO_TRANS);
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
        order, noTranspose, noTranspose, M, N, K, alpha, A, K, B, N, beta, results, N
    };
    cg.builder.CreateCall(cg.getFunc("cblas_sgemm", ft), args);
    return results;
}

LgsExpr* LgsMatrix::getZeroValue() {
    return new LgsMatrixExpr(rows, columns);
}

LgsType* LgsMatrix::getValueType() {
    return new LgsSArray(baseType, new LgsIntConst(columns));
}

std::string LgsMatrix::getBaseName() {
    return name;
}

std::string LgsMatrix::getName() {
    return "Mat" + std::to_string(rows) + "x" + std::to_string(columns);
}

bool LgsMatrix::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (getName() == other->getName()) return true;
    return false;
}

std::string LgsMatrix::fmtStr() const {
    return "%s";
}

bool LgsMatrix::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsMatrix::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    const auto i = cg.builder.CreateMul(index, cg.i32(columns));
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), i});
    const auto rows2 = cg.builder.CreateAlloca(baseType->getIRType(cg), cg.i32(columns));
    cg.callMemcpy(rows2, gep, cg.builder.CreateMul(baseType->IRSize(cg), cg.usize(columns)));
    return rows2;
}

Value* LgsMatrix::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.i32(rows);
}

DIType* LgsMatrix::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Value* LgsMatrix::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    assert(0);
}
