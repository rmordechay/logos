#include "types/iterables/LgsSet.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsAny.h"
#include "types/iterables/LgsDArray.h"
#include "types/primitives/LgsLong.h"

Type* LgsSet::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    IRType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy()}, name);
    return IRType;
}

Constant* LgsSet::getRTType(LgsCgModule& cg) {
    const auto genericName = getGenericName();
    const auto st = cg.getStructType({cg.ptrTy()}, genericName);
    const auto sv = llvm::ConstantStruct::get(st, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(genericName, sizeBytes(), sizeBytes(), RTT_SET, sv);
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

std::string LgsSet::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsSet::applyBinOp(LgsType* toType, LgsBinOp& op) {
    const auto IRName = toType->getName();
    switch (op.opType) {
    case IN: {
        if (toType->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

bool LgsSet::inferBaseType(const std::vector<LgsExpr*>& args) {
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
    return cg.callLgsFunc("Set_len", cg.sizeTy(), {cg.ptrTy()}, {iterable});
}

Value* LgsSet::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    return cg.callLgsFunc("Set_contains", cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, cg.getPtrTo(value->IRValue)});
}

Value* LgsSet::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    return cg.callLgsFunc("Set_get", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {iterable, index});
}

llvm::DIType* LgsSet::getDebugType(LgsCgModule& cg) {
    assert(0);
}