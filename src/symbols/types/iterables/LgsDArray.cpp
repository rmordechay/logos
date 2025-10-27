#include "types/iterables/LgsDArray.h"
#include "Lgs_DArray.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsArrayExpr.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsVoid.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"

LgsFunc* LgsDArray::getMethod(const std::string& methodName) {
    const auto method = methods.find(methodName);
    if (method != methods.end()) {
        if (method->second) {
            return method->second;
        }
        if (methodName == RESERVE_FUNC_NAME) {
            return getReserveFunc();
        }
    }
    return LgsIterable::getMethod(methodName);
}

Type* LgsDArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    IRType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy(), cg.i32Ty()}, name);
    return IRType;
}

std::string LgsDArray::getName() {
    return name;
}

std::string LgsDArray::pname() {
    if (baseType) return baseType->pname() + "[]";
    return "[]";
}

size_t LgsDArray::getSizeBytes() {
    return sizeof(Lgs_DArray);
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Lgs_RTType LgsDArray::getRTType() {
    return RTT_DARRAY;
}

std::string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsDArray::applyBinOp(const LgsBinOpType op, LgsType* other) {
    switch (op) {
    case IN: {
        const auto otherIter = other->asIterable();
        if (!otherIter) return nullptr;
        if (otherIter->getDimension() - 1 == getDimension()) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

LgsFunc* LgsDArray::getAddFunc() {
    const auto func = methods.find(ADD_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(ADD_FUNC_NAME, &LGS_VOID, {this, baseType}, BUILTIN | PUBLIC | METHOD);
    func->second->fn = [this](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        if (!baseType->isPrimitive) {
            return cg.callLgsFunc(std::string(name) + "_add", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {cg.getPtrTo(args[0]->IRValue), args[1]->IRValue});
        }
        if (baseType->asInt()) {
            return cg.callLgsFunc(std::string(name) + "_addInt", cg.voidTy(), {cg.ptrTy(), cg.i32Ty()}, {cg.getPtrTo(args[0]->IRValue), args[1]->IRValue});
        }
        if (baseType->asLong()) {
            return cg.callLgsFunc(std::string(name) + "_addLong", cg.voidTy(), {cg.ptrTy(), cg.i64Ty()}, {cg.getPtrTo(args[0]->IRValue), args[1]->IRValue});
        }
        assert(0);
    };
    methods[func->second->funcType->name] = func->second;
    return func->second;
}

LgsFunc* LgsDArray::getReserveFunc() {
    const auto func = methods.find(RESERVE_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(RESERVE_FUNC_NAME, &LGS_VOID, {this, &LGS_SIZE}, BUILTIN | PUBLIC | METHOD);
    methods[func->second->funcType->name] = func->second;
    return func->second;
}

Value* LgsDArray::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return getLenFunc()->callIR(cg, {iterable});
}

Value* LgsDArray::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    return cg.callLgsFunc(std::string(name) + "_contains", cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, cg.getPtrTo(value->IRValue)});
}

Value* LgsDArray::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    LgsFunc f("get", &LGS_ANY, {this, &LGS_LONG}, BUILTIN | PUBLIC | METHOD);
    return f.callIR(cg, {iterable, index});
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}