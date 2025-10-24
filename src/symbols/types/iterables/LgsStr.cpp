#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRType(LgsLLVMGen& cg) {
    if (isStatic) return ArrayType::get(cg.i8Ty(), *size->getConstInt() + 1);
    return cg.ptrTy();
}

std::string LgsStr::getName() {
    return name;
}

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

Lgs_rttype LgsStr::getRTType() {
    return RTT_STR;
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto iter = other->asSArray()) {
        return iter->baseType && iter->baseType->asChar();
    }
    return name == other->getName();
}

LgsType* LgsStr::applyBinOp(const LgsBinOpType op, LgsType* other) {
    const auto IRName = other->getName();
    switch (op) {
    case ADD: {
        if (other->isNumber() || name == IRName) {
            isHeapAlloc = true;
            return this;
        }
        break;
    }
    case IN: {
        if (equals(other)) return &LGS_BOOL;
        if (other->asIterable() && canCastTo(other->asIterable()->baseType)) return &LGS_BOOL;
    }
    case EQ: {
        if (equals(other)) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsStr::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(cg.i8Ty(), gep);
}

LgsFunc* LgsStr::getLenFunc() {
    const auto lenFunc = LgsIterable::getLenFunc();
    if (lenFunc->fn) return lenFunc;
    lenFunc->fn = [this](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        return lengthIR(cg, args.front()->IRValue);
    };
    return lenFunc;
}

LgsFunc* LgsStr::getIsEmptyFunc() {
    const auto isEmptyFunc = LgsIterable::getIsEmptyFunc();
    if (isEmptyFunc->fn) return isEmptyFunc;
    isEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        const auto strLen = cg.callStrLen(args[0]->IRValue);
        return cg.builder.CreateICmpEQ(strLen, cg.builder.getInt64(0));
    };
    return isEmptyFunc;
}

LgsFunc* LgsStr::getIsNotEmptyFunc() {
    const auto isNotEmptyFunc = LgsIterable::getIsNotEmptyFunc();
    if (isNotEmptyFunc->fn) return isNotEmptyFunc;
    isNotEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        const auto strLen = cg.callStrLen(args[0]->IRValue);
        return cg.builder.CreateICmpNE(strLen, cg.builder.getInt64(0));
    };
    return isNotEmptyFunc;
}

std::string LgsStr::strFormatPart() const {
    return "%s";
}

Value* LgsStr::addIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto otherStr = other->type->asStr();
    if (isStatic && otherStr->isStatic) {
        const auto selfConstStr = self->getConstStr();
        const auto otherConstStr = other->getConstStr();
        if (selfConstStr && otherConstStr) {
            return cg.getIRStr(*selfConstStr + *otherConstStr);
        }
    }
    const auto selfSize = lengthIR(cg, self->IRValue);
    const auto otherSize = lengthIR(cg, other->IRValue);
    const auto totalSize = cg.builder.CreateAdd(selfSize, otherSize);
    const auto newStrSize = cg.builder.CreateAdd(totalSize, cg.i64(1));
    const auto newStrPtr = cg.callMalloc(newStrSize, true, getRTType());
    cg.callMemCpy(newStrPtr, self->IRValue, selfSize);
    const auto dstPtr = cg.builder.CreateInBoundsGEP(cg.i8Ty(), newStrPtr, selfSize);
    cg.callMemCpy(dstPtr, other->IRValue, otherSize);
    cg.addNullTerminate(newStrPtr, totalSize);
    return newStrPtr;
}

Value* LgsStr::eqIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {self->IRValue, other->IRValue});
    return cg.builder.CreateICmpEQ(rt, cg.i32Zero());
}

Value* LgsStr::neIR(LgsLLVMGen& cg, LgsExpr* self, LgsExpr* other) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {self->IRValue, other->IRValue});
    return cg.builder.CreateICmpNE(rt, cg.i32Zero());
}

Value* LgsStr::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return cg.callStrLen(iterable);
}

Value* LgsStr::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, value->IRValue});
    return cg.builder.CreateIsNotNull(rv);
}

LgsType* LgsStr::clone() {
    const auto newStr = new LgsStr();
    if (size) {
        newStr->size = size->clone();
    }
    newStr->baseType = baseType;
    return newStr;
}
