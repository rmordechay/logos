#include "exprs/LgsFuncCall.h"
#include "exprs/constants/LgsStrConst.h"
#include "LgsConfigs.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsSArray.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsChar.h"

Type* LgsStr::getIRType(LgsCgModule& cg) {
    return cg.ptrTy();
}

std::string LgsStr::getBaseName() {
    return name;
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

Value* LgsStr::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    return cg.emptyStr();
}

Constant* LgsStr::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(getName(), sizeBytes(), RTT_STR, baseType->getRTType(cg));
}

bool LgsStr::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    if (other->asGenericType()) return true;
    if (const auto sArr = other->asSArray()) {
        return sArr->baseType && sArr->baseType->asChar();
    }
    return name == other->getName();
}

LgsType* LgsStr::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case ADD: {
        if (rightType->asStr() || rightType->asChar() || rightType->isNumber()) {
            return new LgsStr();
        }
        break;
    }
    case IN: {
        if (equals(rightType)) return &LGS_BOOL;
        const auto rightIterable = rightType->asIterable();
        if (rightIterable && canCastTo(rightIterable->baseType)) return &LGS_BOOL;
    }
    case EQ: {
        if (equals(rightType)) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsStr::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable, {cg.i32Zero(), index});
    return cg.load(cg.i8Ty(), gep);
}

std::string LgsStr::fmtStr() const {
    return "\"%s\"";
}

bool LgsStr::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(0);
}

Value* LgsStr::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto leftStrConst = left->getConstStr();
    const auto rightStrConst = right->getConstStr();
    if (leftStrConst.has_value() && rightStrConst.has_value()) {
        return cg.getString(leftStrConst.value() + rightStrConst.value());
    }
    const auto rightIntConst = right->getConstInt();
    if (leftStrConst.has_value() && rightIntConst.has_value()) {
        return cg.getString(leftStrConst.value() + std::to_string(rightIntConst.value()));
    }
    const auto rightFloatConst = right->getConstFloat();
    if (leftStrConst.has_value() && rightFloatConst.has_value()) {
        return cg.getString(leftStrConst.value() + std::to_string(rightFloatConst.value()));
    }

    const auto leftSize = lenIR(cg, left->IRValue);
    const auto rightSize = lenIR(cg, right->IRValue);
    const auto sumSize = cg.builder.CreateAdd(leftSize, rightSize);
    const auto allocSize = cg.builder.CreateAdd(sumSize, cg.usize(1));

    Value* level = nullptr;
    if (left->isReturnExpr) {
        level = cg.builder.CreateSub(cg.currentLevel, cg.usize(1));
    } else if (left->level) {
        level = left->level;
    }
    const auto buffer = cg.heapAlloc(allocSize, level);
    const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, leftSize);
    cg.callMemcpy(buffer, left->IRValue, leftSize);
    cg.callMemcpy(rightPos, right->IRValue, rightSize);
    cg.addNullTerminate(buffer, sumSize);
    return buffer;
}

Value* LgsStr::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.callStrLen(iterable);
}

Value* LgsStr::inIR(LgsCgModule& cg, Value* iterableExpr, Value* value) {
    const auto rv = cg.callFunc("strstr", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr, value});
    return cg.builder.CreateIsNotNull(rv);
}

DIType* LgsStr::getDebugType(LgsCgModule& cg) {
    const auto& diBuilder = cg.debugger.diBuilder;
    const auto charType = diBuilder->createBasicType("char", sizeof(char), dwarf::DW_ATE_signed_char);
    return diBuilder->createPointerType(charType, sizeof(void*));
}
