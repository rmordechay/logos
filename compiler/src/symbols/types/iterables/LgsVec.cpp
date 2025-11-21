#include "types/iterables/LgsVec.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/LgsAny.h"
#include "LgsUtils.h"
#include <iostream>
#include <sstream>

LgsField* LgsVec::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    const size_t newFieldDim = fieldName.size();
    const auto scalarOrVector = newFieldDim == 1 ? baseType->clone() : new LgsVec(newFieldDim);
    const auto field = new LgsField(fieldName, scalarOrVector);
    addField(field);
    return field;
}

Type* LgsVec::getIRType(LgsLLVMGen& cg) {
    IRType = llvm::FixedVectorType::get(baseType->getIRType(cg), vectorDim);
    return IRType;
}

std::string LgsVec::getName() {
    return baseName + std::to_string(vectorDim);
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

LgsType* LgsVec::applyBinOp(LgsType* toType, LgsBinOp& op) {
    const auto thisNme = getName();
    const auto otherName = toType->getName();
    switch (op.opType) {
    case ADD:
    case SUB: {
        if (thisNme == otherName) return clone();
        break;
    }
    case DIV:
    case MUL: {
        if (thisNme == otherName) return &LGS_FLOAT;
        if (toType->isNumber()) return clone();
        break;
    }
    case IN: {
        if (toType->canCastTo(baseType)) return baseType->clone();
        break;
    }
    default:
        break;
    }
    return nullptr;
}

bool LgsVec::inferBaseType(const std::vector<LgsExpr*>& args) {
    assert(!args.empty());
    const auto firstArg = args.front();
    const auto argsBaseType = firstArg->type->isNumber() ? firstArg->type : firstArg->type->asIterable()->baseType;
    if (!argsBaseType) return false;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto type = arg->type->isNumber() ? arg->type : arg->type->asIterable()->baseType;
        if (!type->equals(argsBaseType)) return false;
    }
    baseType = argsBaseType;
    return true;
}

Value* LgsVec::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateFAdd(left->loadIR(cg), right->loadIR(cg));
    }
    return cg.builder.CreateFAdd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsVec::subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateFSub(left->loadIR(cg), right->loadIR(cg));
    }
    return cg.builder.CreateFSub(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsVec::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(getIRType(cg));
        right->IRValue = cg.builder.CreateSIToFP(right->IRValue, vecTy->getElementType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFMul(left->loadIR(cg), right->loadIR(cg));
    }
    if (right->IRValue->getType()->isVectorTy()) {
        return dotProduct(cg, left, right);
    }
    if (right->IRValue->getType()->isFloatingPointTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(left->IRValue->getType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFMul(left->IRValue, right->IRValue);
    }
    return cg.builder.CreateFMul(left->IRValue, right->IRValue);
}

Value* LgsVec::divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(getIRType(cg));
        right->IRValue = cg.builder.CreateSIToFP(right->IRValue, vecTy->getElementType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFDiv(left->loadIR(cg), right->loadIR(cg));
    }
    if (right->IRValue->getType()->isVectorTy()) {
        return dotProduct(cg, left, right);
    }
    if (right->IRValue->getType()->isFloatingPointTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(left->IRValue->getType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFDiv(left->IRValue, right->IRValue);
    }
    return cg.builder.CreateFDiv(left->IRValue, right->IRValue);
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

LgsType* LgsVec::clone() {
    return new LgsVec(vectorDim, baseType->clone());
}
