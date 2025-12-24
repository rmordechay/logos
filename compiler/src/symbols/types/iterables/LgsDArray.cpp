#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_DArrayExpr.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include <llvm/IR/Module.h>

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, baseType}, flags);
        func->fn = [this](LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
            addIRElement(cg, args[0].expr->IRValue, nullptr, cg.getPtrTo(args[1].expr->IRValue));
            return nullptr;
        };
        addMethod(func);
        return func;
    }
    return LgsIterable::getMethod(methodName);
}

bool LgsDArray::inferBaseType(std::vector<LgsExpr*>& args) {
    assert(!args.empty());
    if (baseType) return true;
    const auto baseExprType = args.front()->type;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!baseExprType->equals(arg->type)) return false;
    }
    baseType = baseExprType;
    return true;
}

Type* LgsDArray::getIRType(LgsCgModule& cg) {
    if (IRType) return IRType;
    IRType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy()}, name);
    return IRType;
}

Constant* LgsDArray::getRTType(LgsCgModule& cg) {
    const auto dArrName = getName();
    const auto sv = cg.getRTTExtraStruct(dArrName, {cg.ptrTy()}, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(dArrName, sizeBytes(), RTT_DARRAY, isHeapAlloc, sv);
}

std::string LgsDArray::getBaseName() {
    return name;
}

std::string LgsDArray::getName() {
    return name + baseType->getName();
}

std::string LgsDArray::pname() {
    if (baseType) return baseType->pname() + "[]";
    return "[]";
}

size_t LgsDArray::sizeBytes() {
    return sizeof(Lgs_DArrayExpr);
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Value* LgsDArray::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    auto rtType = getRTType(cg);
    Value* v = pointee;
    if (!pointee) {
        v = cg.heapAllocate(cg.usize(sizeBytes()), rtType, false);
    }
    cg.callLgsFunc(name, "init", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {v, rtType});
    return v;
}

std::string LgsDArray::fmtStr() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsDArray::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    switch (op.opType) {
    case IN: {
        const auto otherIter = rightType->asIterable();
        if (!otherIter) return nullptr;
        if (otherIter->getDimension() - 1 == getDimension()) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsDArray::lenIR(LgsCgModule& cg, Value* iterable) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {iterable, getRTType(cg)};
    return cg.callLgsFunc(name, "len", cg.sizeTy(), params, IRArgs);
}

Value* LgsDArray::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {iterableExpr->IRValue, getRTType(cg), cg.getPtrTo(value->IRValue)};
    return cg.callLgsFunc(name, "contains", cg.i1Ty(), params, IRArgs);
}

Value* LgsDArray::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy(), cg.sizeTy()};
    const std::vector<Value*> IRArgs = {iterable, getRTType(cg), index};
    return cg.callLgsFunc(name, "get", cg.ptrTy(), params, IRArgs);
}

void LgsDArray::addIRElement(LgsCgModule& cg, Value* iterable, Value* index, Value* value) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {iterable, getRTType(cg), cg.getPtrTo(value)};
    cg.callLgsFunc(name, "add", cg.voidTy(), params, IRArgs);
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (other->asGenericType()) return true;
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

DIType* LgsDArray::getDebugType(LgsCgModule& cg) {
    assert(0);
}