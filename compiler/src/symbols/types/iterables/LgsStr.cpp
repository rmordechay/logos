#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "LgsConfigs.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRType(LgsCgModule& cg) {
    if (isStatic) return ArrayType::get(cg.i8Ty(), size->getConstInt().value() + 1);
    return cg.ptrTy();
}

std::string LgsStr::getName() {
    return name;
}

size_t LgsStr::sizeBytes() {
    if (isStatic) {
        const auto constInt = size->getConstInt();
        assert(constInt.has_value());
        return constInt.value();
    }
    return sizeof(void*);
}

LgsExpr* LgsStr::getZeroValue() {
    return new LgsStrConst("");
}

Constant* LgsStr::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getGenericName(), sizeBytes(), sizeof(void*), RTT_STR, cg.null());
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
        if (name == IRName) return this;
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

Value* LgsStr::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable, {cg.i32Zero(), index});
    return cg.builder.CreateLoad(cg.i8Ty(), gep);
}

std::string LgsStr::fmtStr() const {
    return "%s";
}

bool LgsStr::inferBaseType(const std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsStr::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto leftSize = lenIR(cg, left->IRValue);
    const auto rightSize = right->type->asStr()->lenIR(cg, right->IRValue);
    const auto sumSize = cg.builder.CreateAdd(leftSize, rightSize);
    const auto buffer = cg.allocate(sumSize, getRTType(cg), true);
    const auto gep = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, leftSize);
    cg.callMemCpy(buffer, left->IRValue, leftSize); // cpy left str
    cg.callMemCpy(gep, right->IRValue, rightSize); // cpy right str
    return buffer;
}

Value* LgsStr::eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left->IRValue, right->IRValue});
    return cg.builder.CreateICmpEQ(rt, cg.i32Zero());
}

Value* LgsStr::neIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left->IRValue, right->IRValue});
    return cg.builder.CreateICmpNE(rt, cg.i32Zero());
}

Value* LgsStr::lenIR(LgsCgModule& cg, Value* iterable) {
    if (isStatic) return cg.extendToSize(size->IRValue);
    return cg.callStrLen(iterable);
}

Value* LgsStr::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, value->IRValue});
    return cg.builder.CreateIsNotNull(rv);
}

DIType* LgsStr::getDebugType(LgsCgModule& cg) {
    const auto& diBuilder = cg.debugger.diBuilder;
    const auto charType = diBuilder->createBasicType("char", sizeof(char), dwarf::DW_ATE_signed_char);
    return diBuilder->createPointerType(charType, sizeof(void*));
}