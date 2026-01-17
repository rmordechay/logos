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
    if (other->getName() == LgsAny::name) return true;
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
            const auto str = new LgsStr();
            str->isStatic = isStatic;
            return str;
        }
        break;
    }
    case IN: {
        if (equals(rightType)) return &LGS_BOOL;
        if (rightType->asIterable() && canCastTo(rightType->asIterable()->baseType)) return &LGS_BOOL;
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

Value* LgsStr::getIRElement(LgsCgModule& cg, LgsExpr* iterable, LgsExpr* index) {
    const auto gep =  cg.builder.CreateGEP(cg.i8Ty(), iterable->IRValue, {cg.i32Zero(), index->IRValue});
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

    const auto leftIterable = left->type->asStr();
    const auto rightIterable = right->type->asStr();
    assert(leftIterable && rightIterable);

    const auto leftSize = lenIR(cg, left->IRValue);
    const auto rightSize = lenIR(cg, right->IRValue);
    const auto sumSize = cg.builder.CreateAdd(leftSize, rightSize);
    const auto allocSize = cg.builder.CreateAdd(sumSize, cg.usize(1));

    const auto buffer = cg.heapAlloc(allocSize);
    const auto rightPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, leftSize);
    cg.callMemCpy(buffer, left->IRValue, leftSize);
    cg.callMemCpy(rightPos, right->IRValue, rightSize);
    const auto nullPos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, sumSize);
    cg.builder.CreateStore(cg.i8Zero(), nullPos);
    return buffer;
}

Value* LgsStr::lenIR(LgsCgModule& cg, Value* iterable) {
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
