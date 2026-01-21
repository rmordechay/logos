#include "types/LgsComplex.h"

#include "LgsBinaryTokens.h"
#include "exprs/constants/LgsComplexConst.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"

#include <cassert>
#include <llvm/IR/Module.h>

#include "exprs/LgsBinaryExpr.h"

size_t LgsComplex::sizeBytes() {
    return realType->sizeBytes() + imaginaryType->sizeBytes();
}

LgsExpr* LgsComplex::getZeroValue() {
    return new LgsComplexConst(LGS_INT.getZeroValue(), LGS_INT.getZeroValue());
}

Type* LgsComplex::getIRType(LgsCgModule& cg) {
    return cg.getStructType({realType->getIRType(cg), imaginaryType->getIRType(cg)}, name);
}

Constant* LgsComplex::getRTType(LgsCgModule& cg) {
    const auto nullableName = getName();
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector args = {realType->getRTType(cg), imaginaryType->getRTType(cg)};
    const auto sv = cg.getRTTExtraStruct(nullableName, params, args);
    return cg.getRTTypeInfo(nullableName, IRSize(cg), RTT_COMPLEX, isHeapAlloc, sv);
}

bool LgsComplex::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (getName() == other->getName()) return true;
    return false;
}

Value* LgsComplex::addIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.load(getIRType(cg), left->IRValue);
    const auto r = cg.load(getIRType(cg), right->IRValue);
    const auto lReal = cg.builder.CreateExtractValue(l, 0);
    const auto rReal = cg.builder.CreateExtractValue(r, 0);
    const auto lImag = cg.builder.CreateExtractValue(l, 1);
    const auto rImag = cg.builder.CreateExtractValue(r, 1);
    const auto resultReal = cg.builder.CreateAdd(lReal, rReal);
    const auto resultImag = cg.builder.CreateAdd(lImag, rImag);
    const auto result = cg.builder.CreateAlloca(getIRType(cg));
    Value* temp = UndefValue::get(getIRType(cg));
    temp = cg.builder.CreateInsertValue(temp, resultReal, 0);
    temp = cg.builder.CreateInsertValue(temp, resultImag, 1);
    cg.store(temp, result);
    return result;
}

Value* LgsComplex::subIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto ty = getIRType(cg);
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.load(ty, left->IRValue);
    const auto r = cg.load(ty, right->IRValue);
    const auto lReal = cg.builder.CreateExtractValue(l, 0);
    const auto rReal = cg.builder.CreateExtractValue(r, 0);
    const auto lImag = cg.builder.CreateExtractValue(l, 1);
    const auto rImag = cg.builder.CreateExtractValue(r, 1);
    const auto resultReal = cg.builder.CreateSub(lReal, rReal);
    const auto resultImag = cg.builder.CreateSub(lImag, rImag);
    const auto result = cg.builder.CreateAlloca(ty);
    Value* temp = UndefValue::get(ty);
    temp = cg.builder.CreateInsertValue(temp, resultReal, 0);
    temp = cg.builder.CreateInsertValue(temp, resultImag, 1);
    cg.store(temp, result);
    return result;
}

Value* LgsComplex::mulIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto ty = getIRType(cg);
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.load(ty, left->IRValue);
    const auto r = cg.load(ty, right->IRValue);

    const auto a = cg.builder.CreateExtractValue(l, 0);  // lReal
    const auto b = cg.builder.CreateExtractValue(l, 1);  // lImag
    const auto c = cg.builder.CreateExtractValue(r, 0);  // rReal
    const auto d = cg.builder.CreateExtractValue(r, 1);  // rImag

    // real = ac - bd
    const auto ac = cg.builder.CreateMul(a, c);
    const auto bd = cg.builder.CreateMul(b, d);
    const auto resultReal = cg.builder.CreateSub(ac, bd);

    // imag = ad + bc
    const auto ad = cg.builder.CreateMul(a, d);
    const auto bc = cg.builder.CreateMul(b, c);
    const auto resultImag = cg.builder.CreateAdd(ad, bc);

    const auto result = cg.builder.CreateAlloca(ty);
    Value* temp = UndefValue::get(ty);
    temp = cg.builder.CreateInsertValue(temp, resultReal, 0);
    temp = cg.builder.CreateInsertValue(temp, resultImag, 1);
    cg.store(temp, result);

    return result;
}

Value* LgsComplex::divIR(LgsCgModule& cg, LgsBinaryExpr* binExpr) {
    const auto ty = getIRType(cg);
    const auto left = binExpr->left;
    const auto right = binExpr->right;
    const auto l = cg.load(ty, left->IRValue);
    const auto r = cg.load(ty, right->IRValue);

    const auto a = cg.builder.CreateExtractValue(l, 0);
    const auto b = cg.builder.CreateExtractValue(l, 1);
    const auto c = cg.builder.CreateExtractValue(r, 0);
    const auto d = cg.builder.CreateExtractValue(r, 1);

    const auto cc = cg.builder.CreateFMul(c, c);
    const auto dd = cg.builder.CreateFMul(d, d);
    const auto denominator = cg.builder.CreateFAdd(cc, dd);

    const auto ac = cg.builder.CreateFMul(a, c);
    const auto bd = cg.builder.CreateFMul(b, d);
    const auto numeratorReal = cg.builder.CreateFAdd(ac, bd);
    const auto resultReal = cg.builder.CreateFDiv(numeratorReal, denominator);

    const auto bc = cg.builder.CreateFMul(b, c);
    const auto ad = cg.builder.CreateFMul(a, d);
    const auto numeratorImag = cg.builder.CreateFSub(bc, ad);
    const auto resultImag = cg.builder.CreateFDiv(numeratorImag, denominator);

    const auto result = cg.builder.CreateAlloca(ty);
    cg.storeStructField(ty, result, 0, resultReal);
    cg.storeStructField(ty, result, 1, resultImag);

    return result;
}


std::string LgsComplex::fmtStr() const {
    return "%s";
}

DIType* LgsComplex::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsType* LgsComplex::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (!rightType->asComplex()) return nullptr;
    switch (op.opType) {
    case ADD:
    case SUB:
    case MUL:
    case DIV: {
        return this;
    }
    case EQ:
    case NE: {
        return &LGS_BOOL;
    }
    case NOOP:
        assert(0);
    default:
        break;
    }
    return nullptr;
}

std::string LgsComplex::getName() {
    return name;
}

LgsComplex::~LgsComplex() {
    freeType(realType);
    freeType(imaginaryType);
    realType = nullptr;
    imaginaryType = nullptr;
}
