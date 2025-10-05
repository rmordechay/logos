#include "types/iterables/LgsVec.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsVectorExpr.h"
#include "types/primitives/LgsSize.h"

Type* LgsVec::getIRType(LgsLLVMGen& cg) {
    IRType = FixedVectorType::get(baseType->getIRType(cg), vectorDim);
    return IRType;
}

std::string LgsVec::getName() {
    return "vec" + std::to_string(vectorDim);
}

json::value LgsVec::asJsonStr() {
    assert(0);
}

size_t LgsVec::getSizeBytes() {
    return baseType->getSizeBytes() * 2;
}

LgsExpr* LgsVec::getZeroValue() {
    return new LgsVectorExpr(this);
}

Lgs_RTType LgsVec::getRTType() {
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

LgsType* LgsVec::applyOp(const LgsOperator op, LgsType* other) {
    const auto thisNme = getName();
    const auto otherName = other->getName();
    switch (op) {
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

Value* LgsVec::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    if (other->getType()->isIntegerTy()) {
        return cg.builder.CreateAdd(self, other);
    }
    return cg.builder.CreateFAdd(self, other);
}

Value* LgsVec::subIR(LgsLLVMGen& cg, Value* self, Value* other) {
    if (other->getType()->isIntegerTy()) {
        return cg.builder.CreateSub(self, other);
    }
    return cg.builder.CreateFSub(self, other);
}

Value* LgsVec::mulIR(LgsLLVMGen& cg, Value* self, Value* other) {
    auto loadOther = other;
    if (other->getType()->isIntegerTy()) {
        const auto vecTy = cast<VectorType>(self->getType());
        loadOther = cg.builder.CreateSIToFP(loadOther, vecTy->getElementType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFMul(self, loadOther);
    }
    if (other->getType()->isVectorTy()) {
        return dotProduct(cg, self, loadOther);
    }
    if (other->getType()->isFloatingPointTy()) {
        const auto vecTy = cast<VectorType>(self->getType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFMul(self, loadOther);
    }
    return cg.builder.CreateFMul(self, loadOther);
}

Value* LgsVec::divIR(LgsLLVMGen& cg, Value* self, Value* other) {
    auto loadOther = other;
    if (other->getType()->isIntegerTy()) {
        const auto vecTy = cast<VectorType>(self->getType());
        loadOther = cg.builder.CreateSIToFP(loadOther, vecTy->getElementType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFDiv(self, loadOther);
    }
    if (other->getType()->isFloatingPointTy()) {
        const auto vecTy = cast<VectorType>(self->getType());
        loadOther = cg.builder.CreateVectorSplat(vecTy->getElementCount(), loadOther);
        return cg.builder.CreateFDiv(self, loadOther);
    }
    return cg.builder.CreateFDiv(self, loadOther);
}

Value* LgsVec::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto resultPtr = cg.builder.CreateAlloca(cg.i1Ty());
    cg.builder.CreateStore(cg.false_(), resultPtr);
    cg.loop(cg.i64(vectorDim), [this, &cg, iterableExpr, value, resultPtr](Value* index, BasicBlock* exitBlock) {
        const auto trueBlock = cg.createBlock();
        const auto falseBlock = cg.createBlock();
        const auto zeroValue = baseType->getZeroValue();
        zeroValue->IRValue = getIRElement(cg, iterableExpr->IRValue, index);
        const auto eq = zeroValue->eqIR(cg, value->loadIR(cg));
        cg.builder.CreateCondBr(eq, trueBlock, falseBlock);
        cg.startBlock(trueBlock);
        cg.builder.CreateStore(cg.true_(), resultPtr);
        cg.builder.CreateBr(exitBlock);
        cg.startBlock(falseBlock);
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

Value* LgsVec::dotProduct(LgsLLVMGen& cg, Value* lhs, Value* rhs) {
    const auto lx = cg.builder.CreateExtractValue(lhs, {0});
    const auto lhs_y = cg.builder.CreateExtractValue(lhs, {1});
    const auto rhs_x = cg.builder.CreateExtractValue(rhs, {0});
    const auto rhs_y = cg.builder.CreateExtractValue(rhs, {1});
    const auto res_x = cg.builder.CreateFMul(lx, rhs_x);
    const auto res_y = cg.builder.CreateFMul(lhs_y, rhs_y);
    Value* result = UndefValue::get(getIRType(cg));
    result = cg.builder.CreateInsertValue(result, res_x, {0});
    result = cg.builder.CreateInsertValue(result, res_y, {1});
    if (vectorDim == 2) return result;

    const auto lhs_z = cg.builder.CreateExtractValue(lhs, {2});
    const auto rhs_z = cg.builder.CreateExtractValue(rhs, {2});
    const auto res_z = cg.builder.CreateFMul(lhs_z, rhs_z);
    result = UndefValue::get(getIRType(cg));
    result = cg.builder.CreateInsertValue(result, res_x, {0});
    result = cg.builder.CreateInsertValue(result, res_y, {1});
    result = cg.builder.CreateInsertValue(result, res_z, {2});
    if (vectorDim == 3) return result;

    const auto lhs_w = cg.builder.CreateExtractValue(lhs, {3});
    const auto rhs_w = cg.builder.CreateExtractValue(rhs, {3});
    const auto res_w = cg.builder.CreateFMul(lhs_w, rhs_w);
    result = UndefValue::get(getIRType(cg));
    result = cg.builder.CreateInsertValue(result, res_x, {0});
    result = cg.builder.CreateInsertValue(result, res_y, {1});
    result = cg.builder.CreateInsertValue(result, res_z, {2});
    result = cg.builder.CreateInsertValue(result, res_w, {3});
    return result;
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
    for (int i = 0; i < vectorDim; i++) {
        str << baseType->strFormatPart();
        if (i < vectorDim - 1) str << ", ";
    }
    str << '>';
    return str.str();
}