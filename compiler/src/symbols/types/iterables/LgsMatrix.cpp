#include "types/iterables/LgsMatrix.h"

#include <assert.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <vector>

#include "LgsBinaryTokens.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsMatrixExpr.h"
#include "codegen/LgsCodeGen.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsVec.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"
#include "exprs/constants/LgsIntConst.h"
#include "types/primitives/LgsSize.h"

size_t LgsMatrix::sizeBytes() {
    return rows * columns * baseType->sizeBytes();
}

LgsExpr* LgsMatrix::getZeroValue() {
    return new LgsMatrixExpr(rows, columns);
}

LgsType* LgsMatrix::getValueType() {
    return new LgsSArray(baseType, new LgsIntConst(&LGS_SIZE, columns));
}

std::string LgsMatrix::getBaseName() {
    return name;
}

std::string LgsMatrix::getName() {
    return "Mat" + std::to_string(rows) + "x" + std::to_string(columns);
}

std::string LgsMatrix::fmtStr() const {
    return "%s";
}

bool LgsMatrix::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (getName() == other->getName()) return true;
    return false;
}

Type* LgsMatrix::getIRType(LgsCodeGen& cg) {
    return ArrayType::get(baseType->getIRType(cg), rows * columns);
}

LgsType* LgsMatrix::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (rightType->isScalar()) {
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
    if (!number->isScalar()) return nullptr;
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

Value* LgsMatrix::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    if (pointee) return pointee;
    return cg.builder.CreateAlloca(getIRType(cg));
}

LgsType* LgsMatrix::applyMatMatOp(const LgsMatrix* otherMat, const LgsBinOp& op) const {
    if (columns != otherMat->rows) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case DIV:
        if (rows != otherMat->rows || columns != otherMat->columns) return nullptr;
        return new LgsMatrix(rows, columns);
    case MUL:
        return new LgsMatrix(rows, otherMat->columns);
    default:
        return nullptr;
    }
}

Value* LgsMatrix::getIRElement(LgsCodeGen& cg, Value* iterable, Value* index) {
    const auto i = cg.builder.CreateMul(index, cg.i32(columns));
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.zero32(), i});
    const auto rows2 = cg.builder.CreateAlloca(baseType->getIRType(cg), cg.i32(columns));
    cg.callMemcpy(rows2, gep, cg.builder.CreateMul(baseType->IRSize(cg), cg.usize(columns)));
    return rows2;
}

Value* LgsMatrix::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto func1 = [&](Value* l, Value* r) { return cg.builder.CreateAdd(l, r); };
    const auto func2 = [&](Value* l, Value* r) { return cg.builder.CreateFAdd(l, r); };
    return applyElemWise(cg, binExpr, func1, func2);
}

Value* LgsMatrix::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto func1 = [&](Value* l, Value* r) { return cg.builder.CreateSub(l, r); };
    const auto func2 = [&](Value* l, Value* r) { return cg.builder.CreateFSub(l, r); };
    return applyElemWise(cg, binExpr, func1, func2);
}

Value* LgsMatrix::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    if (binExpr->left->type->asMatrix() && binExpr->right->type->asMatrix()) {
        return mulIRMatMat(cg, binExpr);
    }
    const auto func1 = [&](Value* l, Value* r) { return cg.builder.CreateMul(l, r); };
    const auto func2 = [&](Value* l, Value* r) { return cg.builder.CreateFMul(l, r); };
    return applyElemWise(cg, binExpr, func1, func2);
}

Value* LgsMatrix::mulIRMatMat(LgsCodeGen& cg, const LgsBinaryExpr* binExpr) {
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
    const auto ft = cg.getFT(cg.voidTy(), {cg.i32Ty(), cg.i32Ty(), cg.i32Ty(), cg.i32Ty(), cg.i32Ty(), cg.i32Ty(), cg.floatTy(), cg.ptrTy(), cg.i32Ty(), cg.ptrTy(), cg.i32Ty(), cg.floatTy(), cg.ptrTy(), cg.i32Ty()});
    const std::vector<Value*> args = {order, noTranspose, noTranspose, M, N, K, alpha, A, K, B, N, beta, results, N};
    cg.builder.CreateCall(cg.getFunc("cblas_sgemm", ft), args);
    return results;
}

Value* LgsMatrix::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    const auto func1 = [&](Value* l, Value* r) { return cg.builder.CreateSDiv(l, r); };
    const auto func2 = [&](Value* l, Value* r) { return cg.builder.CreateFDiv(l, r); };
    return applyElemWise(cg, binExpr, func1, func2);
}

Value* LgsMatrix::inIR(LgsCodeGen& cg, Value* iterableExpr, Value* value) {
    assert(0);
}

Value* LgsMatrix::lenIR(LgsCodeGen& cg, Value* iterable) {
    return cg.i32(rows);
}

Constant* LgsMatrix::getRTTypeExtra(LgsCodeGen& cg) {
    const auto rttName = getRTTName();
    const auto st = cg.getStructType({cg.sizeTy(), cg.sizeTy(), cg.ptrTy()});
    const std::vector<Constant*> args = {cg.usize(rows), cg.usize(columns), baseType->getRTType(cg)};
    return cg.createGlobal(rttName + "_extra", st, ConstantStruct::get(st, args));
}

DIType* LgsMatrix::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

std::pair<Value*, Value*> LgsMatrix::loadMatOperands(LgsCodeGen& cg, const LgsBinaryExpr* binExpr) {
    const auto lExpr = binExpr->left;
    const auto rExpr = binExpr->right;
    const auto ty = getIRType(cg);
    const auto isMatMat = rExpr->type->asMatrix() != nullptr;
    auto l = lExpr->IRValue;
    auto r = rExpr->IRValue;
    if (l->getType()->isPointerTy()) l = cg.load(ty, l);
    if (r->getType()->isPointerTy()) r = cg.load(isMatMat ? ty : baseType->getIRType(cg), r);
    return {l, r};
}

Value* LgsMatrix::applyElemWise(LgsCodeGen& cg, LgsBinaryExpr* binExpr, const std::function<Value*(Value*, Value*)>& intOp, const std::function<Value*(Value*, Value*)>& floatOp) {
    const auto [l, r] = loadMatOperands(cg, binExpr);
    const auto ty = getIRType(cg);
    const auto isMatMat = binExpr->right->type->asMatrix() != nullptr;
    Value* result = UndefValue::get(ty);
    for (size_t i = 0; i < rows * columns; ++i) {
        const auto u = static_cast<unsigned>(i);
        const auto lElem = cg.builder.CreateExtractValue(l, {u});
        const auto rElem = isMatMat ? cg.builder.CreateExtractValue(r, {u}) : r;
        const auto res = baseType->isInt ? intOp(lElem, rElem) : floatOp(lElem, rElem);
        result = cg.builder.CreateInsertValue(result, res, {u});
    }
    return cg.allocaAndStore(ty, result);
}
