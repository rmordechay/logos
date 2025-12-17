#include "types/iterables/LgsSet.h"

#include "LgsBinaryTokens.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsDArray.h"

Type* LgsSet::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    IRType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy()}, name);
    return IRType;
}

Constant* LgsSet::getRTType(LgsCgModule& cg) {
    const auto setName = getName();
    const auto sv = cg.getRTTExtraStruct(setName, {cg.ptrTy()}, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(setName, sizeBytes(), RTT_SET, isHeapAlloc, sv);
}

size_t LgsSet::sizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsSet::getZeroValue() {
    assert(0);
}

std::string LgsSet::getName() {
    return name;
}

std::string LgsSet::pname() {
    return std::string(name) + "<" + (genericArgs.empty() ? "" : genericArgs.front()->pname()) + ">";
}

bool LgsSet::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asSet();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

std::string LgsSet::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSet::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    const auto IRName = rightType->getName();
    switch (op.opType) {
    case IN: {
        if (rightType->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

bool LgsSet::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(!args.empty());
    if (baseType) return true;
    const auto baseExprType = args.front()->type;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!baseExprType->canCastTo(arg->type)) return false;
    }
    baseType = baseExprType;
    return true;
}

Value* LgsSet::lenIR(LgsCgModule& cg, Value* iterable) {
    return cg.callLgsFunc(name, "len", cg.sizeTy(), {cg.ptrTy()}, {iterable});
}

Value* LgsSet::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector IRArgs = {iterableExpr->IRValue, cg.getPtrTo(value->IRValue)};
    return cg.callLgsFunc(name, "contains", cg.i1Ty(), params, IRArgs);
}

Value* LgsSet::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.sizeTy()};
    const std::vector IRArgs = {iterable, index};
    return cg.callLgsFunc(name, "get", cg.ptrTy(), params, IRArgs);
}

DIType* LgsSet::getDebugType(LgsCgModule& cg) {
    assert(0);
}