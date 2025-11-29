#include "types/iterables/LgsVec.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/LgsAny.h"
#include "LgsUtils.h"
#include "cblas/cblas.h"
#include "types/iterables/LgsMatrix.h"

#include <sstream>

LgsField* LgsVec::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    const size_t newFieldDim = fieldName.size();
    LgsField* field = nullptr;
    if (newFieldDim == 1) {
        field = new LgsField(fieldName, baseType);
        field->position = getComponentIndex(fieldName[0]);
    } else {
        field = new LgsField(fieldName, new LgsVec(newFieldDim));
    }
    addField(field);
    return field;
}

Type* LgsVec::getIRType(LgsCgModule& cg) {
    IRType = llvm::FixedVectorType::get(baseType->getIRType(cg), vectorDim);
    return IRType;
}

Constant* LgsVec::getRTType(LgsCgModule& cg) {
    const auto genericName = getGenericName();
    const auto st = cg.getStructType({cg.ptrTy()}, genericName);
    const auto sv = llvm::ConstantStruct::get(st, {baseType->getRTType(cg)});
    if (vectorDim == 2) {
        return cg.getRTTypeInfo(genericName, sizeBytes(), sizeBytes(), RTT_VEC2, sv);
    }
    if (vectorDim == 3) {
        return cg.getRTTypeInfo(genericName, sizeBytes(), sizeBytes(), RTT_VEC3, sv);
    }
    if (vectorDim == 4) {
        return cg.getRTTypeInfo(genericName, sizeBytes(), sizeBytes(), RTT_VEC4, sv);
    }
    assert(0);
}

std::string LgsVec::getGenericName() {
    return getName() + baseType->getGenericName();
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
        if (thisNme == otherName) return this;
        break;
    }
    case MUL: {
        if (thisNme == otherName) return &LGS_FLOAT;
        if (toType->isNumber()) return this;
        break;
    }
    case IN: {
        if (toType->canCastTo(baseType)) return baseType;
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

Value* LgsVec::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateFAdd(left->loadIR(cg), right->loadIR(cg));
    }
    return cg.builder.CreateFAdd(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsVec::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        return cg.builder.CreateFSub(left->loadIR(cg), right->loadIR(cg));
    }
    return cg.builder.CreateFSub(left->loadIR(cg), right->loadIR(cg));
}

Value* LgsVec::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (right->type->isNumber()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(getIRType(cg));
        right->IRValue = cg.builder.CreateSIToFP(right->IRValue, vecTy->getElementType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFMul(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->asMatrix() && right->type->asVec()) {
        return matMul(cg, left, right);
    }
    if (right->IRValue->getType()->isFloatingPointTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(left->IRValue->getType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFMul(left->IRValue, right->IRValue);
    }
    return cg.builder.CreateFMul(left->IRValue, right->IRValue);
}

Value* LgsVec::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (right->IRValue->getType()->isIntegerTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(getIRType(cg));
        right->IRValue = cg.builder.CreateSIToFP(right->IRValue, vecTy->getElementType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFDiv(left->loadIR(cg), right->loadIR(cg));
    }
    if (right->IRValue->getType()->isFloatingPointTy()) {
        const auto vecTy = llvm::cast<llvm::VectorType>(left->IRValue->getType());
        right->IRValue = cg.builder.CreateVectorSplat(vecTy->getElementCount(), right->IRValue);
        return cg.builder.CreateFDiv(left->IRValue, right->IRValue);
    }
    return cg.builder.CreateFDiv(left->IRValue, right->IRValue);
}

Value* LgsVec::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
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

Value* LgsVec::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.usize(2);
}

Value* LgsVec::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const auto gep = cg.builder.CreateGEP(getIRType(cg), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(baseType->getIRType(cg), gep);
}

Value* LgsVec::matMul(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) const {
    const auto mat = left->type->asMatrix();
    const auto order = cg.i32(CblasRowMajor);
    const auto transpose = cg.i32(CblasNoTrans);
    const auto m = cg.i32(mat->rows);
    const auto n = cg.i32(mat->columns);
    const auto alpha = cg.floatv(1);
    const auto matrixPtr = left->IRValue;
    const auto lda = cg.i32(mat->columns);
    const auto vectorPtr = right->IRValue;
    const auto incx = cg.i32(1);
    const auto beta = cg.floatv(0);
    const auto results = cg.builder.CreateAlloca(baseType->getIRType(cg), m);
    const auto incy = cg.i32(1);

    const auto ft = cg.getFT(cg.voidTy(), {
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
        order, transpose, m, n, alpha, matrixPtr, lda, vectorPtr, incx, beta, results, incy
    };
    cg.builder.CreateCall(cg.getFunc("cblas_sgemv", ft), args);
    return results;
}

size_t LgsVec::getSwizzleSet(const char c) {
    if (strchr("xyzw", c)) return 0;
    if (strchr("rgba", c)) return 1;
    if (strchr("stpq", c)) return 2;
    return -1;
}

size_t LgsVec::getComponentIndex(const char c) {
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
    for (size_t i = 0; i < vectorDim; i++) {
        str << baseType->strFormatPart();
        if (i < vectorDim - 1) str << ", ";
    }
    str << '>';
    return str.str();
}

llvm::DIType* LgsVec::getDebugType(LgsCgModule& cg) {
    assert(0);
}