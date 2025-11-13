#include "types/iterables/LgsVec.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsSize.h"
#include "utils/LgsUtils.h"
#include <sstream>

Type* LgsVec::getIRType(LgsLLVMGen& cg) {
    IRType = llvm::FixedVectorType::get(baseType->getIRType(cg), vectorDim);
    return IRType;
}

std::string LgsVec::getName() {
    return "vec" + std::to_string(vectorDim);
}

size_t LgsVec::sizeBytes() {
    return baseType->sizeBytes() * 2;
}

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr(this);
}

Lgs_TypeKind LgsVec::getRTTypeKind() {
    if (vectorDim == 2) return RTT_VEC2;
    if (vectorDim == 3) return RTT_VEC3;
    if (vectorDim == 4) return RTT_VEC4;
    return RTT_UNKNOWN;
}

bool LgsVec::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherVec = other->asVec();
    if (!otherVec) return false;
    return vectorDim == otherVec->vectorDim && baseType->canCastTo(otherVec->baseType);
}

LgsType* LgsVec::applyBinOp(LgsBinaryExpr* binExpr) {
    const auto thisNme = getName();
    const auto other = binExpr->right->type;
    const auto otherName = other->getName();
    switch (binExpr->op) {
    case ADD:
    case SUB:
    case DIV: {
        if (thisNme == otherName) return this;
        break;
    }
    case MUL: {
        if (thisNme == otherName) return &LGS_SIZE;
        if (other->isNumber()) return this;
        break;
    }
    case IN: {
        if (other->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsVec::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    if (other->IRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateAdd(self->IRValue, other->IRValue);
    }
    return cg.builder.CreateFAdd(self->IRValue, other->IRValue);
}

Value* LgsVec::subIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    if (other->IRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateSub(self->loadIR(cg), other->loadIR(cg));
    }
    return cg.builder.CreateFSub(self->loadIR(cg), other->loadIR(cg));
}

Value* LgsVec::mulIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    if (other->IRValue->getType()->isIntegerTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(self->IRValue->getType());
        other->IRValue = cg.builder.CreateSIToFP(other->IRValue, vecTy->getElementType());
        other->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), other->IRValue);
        return cg.builder.CreateFMul(self->IRValue, other->IRValue);
    }
    if (other->IRValue->getType()->isVectorTy()) {
        return dotProduct(cg, self, other);
    }
    if (other->IRValue->getType()->isFloatingPointTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(self->IRValue->getType());
        other->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), other->IRValue);
        return cg.builder.CreateFMul(self->IRValue, other->IRValue);
    }
    return cg.builder.CreateFMul(self->IRValue, other->IRValue);
}

Value* LgsVec::divIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    auto loadOther = other->IRValue;
    if (other->IRValue->getType()->isIntegerTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(self->IRValue->getType());
        loadOther = cg.builder.CreateSIToFP(loadOther, vecTy->getElementType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFDiv(self->IRValue, loadOther);
    }
    if (other->IRValue->getType()->isFloatingPointTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(self->IRValue->getType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFDiv(self->IRValue, loadOther);
    }
    return cg.builder.CreateFDiv(self->IRValue, loadOther);
}

Value* LgsVec::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.i1Ty());
    cg.builder.CreateStore(cg.false_(), resultPtr);
    cg.loop(cg.i64(vectorDim), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto tempExpr = iterableExpr->type->asIterable()->baseType->getZeroValue();
        tempExpr->IRValue = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = baseType->eqIR(cg, tempExpr, value);
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.builder.CreateStore(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
        freeExpr(tempExpr);
    });
    return cg.builder.CreateLoad(cg.i1Ty(), resultPtr);
}

Value* LgsVec::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return cg.usize(2);
}

Value* LgsVec::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(baseType->getIRType(cg), gep);
}

Value* LgsVec::dotProduct(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) const {
    const auto vecTypeIR = self->IRValue->getType();
    cg.savedIP = cg.builder.saveIP();
    const auto dotFunc = cg.getFunc("Lgs_dotProduct", cg.getFT(cg.sizeTy(), {vecTypeIR, vecTypeIR}));
    const auto block = cg.createBlock("entry", dotFunc);
    cg.builder.SetInsertPoint(block);
    const auto l = dotFunc->getArg(0);
    const auto r = dotFunc->getArg(1);

    const auto lx = cg.builder.CreateExtractValue(l, {0});
    const auto rx = cg.builder.CreateExtractValue(r, {0});
    const auto ly = cg.builder.CreateExtractValue(l, {1});
    const auto ry = cg.builder.CreateExtractValue(r, {1});
    const auto mulX = cg.builder.CreateFMul(lx, rx);
    const auto mulY = cg.builder.CreateFMul(ly, ry);
    Value* result = cg.builder.CreateFAdd(mulX, mulY);
    if (vectorDim == 3) {
        const auto lz = cg.builder.CreateExtractValue(l, {2});
        const auto rz = cg.builder.CreateExtractValue(r, {2});
        const auto mulZ = cg.builder.CreateFMul(lz, rz);
        result = cg.builder.CreateFAdd(result, mulZ);
    } else if (vectorDim == 4) {
        const auto lw = cg.builder.CreateExtractValue(l, {3});
        const auto rw = cg.builder.CreateExtractValue(r, {3});
        const auto mulW = cg.builder.CreateFMul(lw, rw);
        result = cg.builder.CreateFAdd(result, mulW);
    }
    cg.builder.CreateRet(result);
    cg.builder.restoreIP(cg.savedIP);

    return cg.builder.CreateCall(dotFunc, {self->IRValue, other->IRValue});
}

int8_t LgsVec::getSwizzleSet(const char c) {
    if (strchr("xyzw", c)) return 0;
    if (strchr("rgba", c)) return 1;
    if (strchr("stpq", c)) return 2;
    return -1;
}

int8_t LgsVec::getComponentIndex(const char c) {
    switch (c) {
    case 'x': case 'r': case 's': return 0;
    case 'y': case 'g': case 't': return 1;
    case 'z': case 'b': case 'p': return 2;
    case 'w': case 'a': case 'q': return 3;
    default: return -1;
    }
}

std::string LgsVec::strFormatPart() const {
    std::stringstream str;
    str << '<';
    for (int8_t i = 0; i < vectorDim; i++) {
        str << baseType->strFormatPart();
        if (i < vectorDim - 1) str << ", ";
    }
    str << '>';
    return str.str();
}