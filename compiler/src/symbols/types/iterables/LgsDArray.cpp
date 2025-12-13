#include "types/iterables/LgsDArray.h"
#include "LgsBinaryTokens.h"
#include "Lgs_DArrayExpr.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsLong.h"
#include <llvm/IR/Module.h>

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    constexpr auto flags = BUILTIN | PUBLIC | METHOD;
    if (methodName == ADD_FUNC) {
        if (methods.contains(ADD_FUNC)) return methods[ADD_FUNC];
        const auto func = new LgsFunc(ADD_FUNC, name, &LGS_VOID, {this, baseType}, flags);
        addMethod(func);
        return func;
    }
    return LgsIterable::getMethod(methodName);
}

bool LgsDArray::inferBaseType(const std::vector<LgsExpr*>& args) {
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

std::string LgsDArray::getName() {
    return baseType->getName() + name;
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
    return cg.callLgsFunc("DArray_len", cg.sizeTy(), {cg.ptrTy(), cg.ptrTy()}, {iterable, getRTType(cg)});
}

Value* LgsDArray::inIR(LgsCgModule& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    return cg.callLgsFunc("DArray_contains", cg.i1Ty(), {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, getRTType(cg), cg.getPtrTo(value->IRValue)});
}

Value* LgsDArray::getIRElement(LgsCgModule& cg, Value* iterable, Value* index) {
    return cg.callLgsFunc("DArray_get", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy(), cg.sizeTy()}, {iterable, getRTType(cg), index});
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

CallFn LgsDArray::getAddFn() {
    return [this](LgsCgModule& cg, const std::vector<Value*>& args) -> Value* {
        const auto arr = args[0];
        const auto value = args[1];
        if (value->getType()->isIntegerTy(LGS_INT.sizeBytes() * 8)) {
            return cg.callLgsFunc(std::string(name) + "_addInt", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.i32Ty()}, {arr, getRTType(cg), value});
        }
        if (value->getType()->isIntegerTy(LGS_LONG.sizeBytes() * 8)) {
            return cg.callLgsFunc(std::string(name) + "_addLong", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.i64Ty()}, {arr, getRTType(cg), value});
        }
        if (value->getType()->isIntegerTy(LGS_SIZE.sizeBytes() * 8)) {
            return cg.callLgsFunc(std::string(name) + "_addSize", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.sizeTy()}, {arr, getRTType(cg), value});
        }
        return cg.callLgsFunc(std::string(name) + "_add", cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, {arr, getRTType(cg), value});
    };
}
