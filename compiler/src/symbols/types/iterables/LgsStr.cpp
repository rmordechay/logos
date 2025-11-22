#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "LgsConfigs.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRType(LgsLLVMGen& cg) {
    // if (isStatic) return ArrayType::get(cg.i8Ty(), *size->getConstInt() + 1);
    return cg.ptrTy();
}

std::string LgsStr::getName() {
    return name;
}

size_t LgsStr::sizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

Lgs_TypeKind LgsStr::getRTTypeKind() {
    return RTT_STR;
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto iter = other->asSArray()) {
        return iter->baseType && iter->baseType->asChar();
    }
    if (other->asGeneric()) return true;
    return name == other->getName();
}

LgsType* LgsStr::applyBinOp(LgsType* toType, LgsBinOp& op) {
    const auto IRName = toType->getName();
    switch (op.opType) {
    case ADD: {
        if (toType->isNumber() || name == IRName) {
            isHeapAlloc = true;
            return this;
        }
        break;
    }
    case IN: {
        if (equals(toType)) return &LGS_BOOL;
        if (toType->asIterable() && canCastTo(toType->asIterable()->baseType)) return &LGS_BOOL;
    }
    case EQ: {
        if (equals(toType)) return &LGS_BOOL;
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
    lenFunc->fn = [this](LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args) {
        return lenIR(cg, args.front().expr->IRValue);
    };
    return lenFunc;
}

LgsFunc* LgsStr::getIsEmptyFunc() {
    const auto isEmptyFunc = LgsIterable::getIsEmptyFunc();
    if (isEmptyFunc->fn) return isEmptyFunc;
    isEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args) {
        const auto strLen = cg.callStrLen(args.front().expr->IRValue);
        return cg.builder.CreateICmpEQ(strLen, cg.builder.getInt64(0));
    };
    return isEmptyFunc;
}

LgsFunc* LgsStr::getIsNotEmptyFunc() {
    const auto isNotEmptyFunc = LgsIterable::getIsNotEmptyFunc();
    if (isNotEmptyFunc->fn) return isNotEmptyFunc;
    isNotEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args) {
        const auto strLen = cg.callStrLen(args.front().expr->IRValue);
        return cg.builder.CreateICmpNE(strLen, cg.builder.getInt64(0));
    };
    return isNotEmptyFunc;
}

std::string LgsStr::strFormatPart() const {
    return "%s";
}

bool LgsStr::inferBaseType(const std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsStr::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto selfSize = lenIR(cg, left->IRValue);
    const auto buffer = cg.builder.CreateAlloca(ArrayType::get(cg.i8Ty(), STRING_BUFFER_SIZE));
    cg.callSnprintf(buffer, cg.getIRStr("%d"), {right->IRValue});
    const auto otherSize = lenIR(cg, buffer);
    const auto totalSize = cg.builder.CreateAdd(selfSize, otherSize);
    const auto newStrSize = cg.builder.CreateAdd(totalSize, cg.i64(1));
    const auto newStrPtr = cg.callAllocate(newStrSize, true, getRTTypeKind());

    cg.callMemCpy(newStrPtr, left->IRValue, selfSize);
    const auto dstPtr = cg.builder.CreateInBoundsGEP(cg.i8Ty(), newStrPtr, selfSize);
    cg.callMemCpy(dstPtr, buffer, otherSize);
    cg.addNullTerminate(newStrPtr, totalSize);
    return newStrPtr;
}

Value* LgsStr::eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left->IRValue, right->IRValue});
    return cg.builder.CreateICmpEQ(rt, cg.i32Zero());
}

Value* LgsStr::neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left->IRValue, right->IRValue});
    return cg.builder.CreateICmpNE(rt, cg.i32Zero());
}

Value* LgsStr::lenIR(LgsLLVMGen& cg, Value* iterable) {
    return cg.callStrLen(iterable);
}

Value* LgsStr::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, value->IRValue});
    return cg.builder.CreateIsNotNull(rv);
}

llvm::DIType* LgsStr::getDebugType(LgsLLVMGen& cg) {
    const auto& diBuilder = cg.debugger.diBuilder;
    const auto charType = diBuilder->createBasicType("char", sizeof(char), llvm::dwarf::DW_ATE_signed_char);
    return diBuilder->createPointerType(charType, sizeof(void*));
}

LgsType* LgsStr::clone() {
    const auto newStr = new LgsStr(*this);
    if (size) {
        newStr->size = size->clone();
    }
    newStr->baseType = baseType;
    return newStr;
}
