#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRBaseType(LgsLLVMGen* cg) const {
    return ArrayType::get(baseType->getIRType(*cg), sizeExpr->getConstInt());
}

Type* LgsStr::getIRType(LgsLLVMGen& cg) {
    return cg.ptrTy();
}

std::string LgsStr::getName() {
    return name;
}

std::string LgsStr::pname() {
    return name;
}

json::value LgsStr::asJsonStr() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

size_t LgsStr::getSizeBytes() {
    return sizeof(void*);
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

Lgs_RTType LgsStr::getRTType() {
    return RTT_STR;
}

LgsType* LgsStr::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsStr::applyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    switch (op) {
    case ADD: {
        if (other->isNumber() || name == IRName) {
            return this;
        }
        break;
    }
    case IN: {
        if (equals(other)) return &LGS_BOOL;
        if (canCastTo(other->asIterable()->baseType)) return &LGS_BOOL;
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

Value* LgsStr::addIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto selfSize = lengthIR(cg, self);
    const auto otherSize = lengthIR(cg, other);
    auto newStrSize = cg.builder.CreateAdd(selfSize, otherSize);
    newStrSize = cg.builder.CreateAdd(newStrSize, cg.i64(1));
    const auto newStrPtr = cg.builder.CreateAlloca(cg.i8Ty(), newStrSize);
    cg.callMemCpy(newStrPtr, self, selfSize);
    const auto dstPtr = cg.builder.CreateInBoundsGEP(cg.i8Ty(), newStrPtr, selfSize);
    cg.callMemCpy(dstPtr, other, otherSize);
    return newStrPtr;
}

Value* LgsStr::eqIR(LgsLLVMGen& cg, Value* self, Value* other) {
    const auto rt = cg.callFunc("strcmp", cg.getFT(cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}), {self, other});
    return cg.builder.CreateICmpEQ(rt, cg.i32(0));
}

Value* LgsStr::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(cg.i8Ty(), gep);
}

LgsFunc* LgsStr::getLenFunc() {
    const auto lenFunc = LgsIterable::getLenFunc();
    if (!lenFunc->fn) {
        lenFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
            return cg.callStrLen(args[0]->IRValue);
        };
    }
    return lenFunc;
}

LgsFunc* LgsStr::getIsEmptyFunc() {
    const auto isEmptyFunc = LgsIterable::getIsEmptyFunc();
    if (!isEmptyFunc->fn) {
        isEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
            const auto strLen = cg.callStrLen(args[0]->IRValue);
            return cg.builder.CreateICmpEQ(strLen, cg.builder.getInt64(0));
        };
    }
    return isEmptyFunc;
}

LgsFunc* LgsStr::getIsNotEmptyFunc() {
    const auto isNotEmptyFunc = LgsIterable::getIsNotEmptyFunc();
    if (!isNotEmptyFunc->fn) {
        isNotEmptyFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
            const auto strLen = cg.callStrLen(args[0]->IRValue);
            return cg.builder.CreateICmpNE(strLen, cg.builder.getInt64(0));
        };
    }
    return isNotEmptyFunc;
}

std::string LgsStr::strFormatPart() const {
    return "%s";
}

Value* LgsStr::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return getLenFunc()->callIR(cg, {iterable});
}

Value* LgsStr::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto rv = cg.callFunc("strstr", cg.getFT(cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}), {iterableExpr->IRValue, value->IRValue});
    return cg.builder.CreateIsNotNull(rv);
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto iter = other->asIterable()) {
        return iter->baseType && iter->baseType->asChar();
    }
    return name == other->getName();
}
