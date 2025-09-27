#include "types/iterables/LgsSet.h"
#include "codegen/LgsLLVMGen.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsFuncType.h"
#include "types/LgsVoid.h"
#include "types/iterables/LgsDArray.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"

Type* LgsSet::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    return getArrStruct(cg);
}

size_t LgsSet::getSizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsSet::getZeroValue() {
    assert(0);
}

Lgs_RTType LgsSet::getRTType() {
    return RTT_SET;
}

std::string LgsSet::getName() {
    return name;
}

std::string LgsSet::pname() {
    return baseType->pname() + "{}";
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

StructType* LgsSet::getArrStruct(LgsLLVMGen& cg) {
    if (arrStruct) return arrStruct;
    arrStruct = cg.getStructType({cg.i64Ty(), cg.ptrTy()}, name);
    return arrStruct;
}

LgsFunc* LgsSet::getAddFunc() {
    const auto func = methods.find(ADD_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(ADD_FUNC_NAME, &LGS_VOID, {this, &LGS_ANY}, BUILTIN | PUBLIC | METHOD);
    func->second->fn = [func](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        return func->second->callIR(cg, {args[0]->IRValue, args[1]->getIRPtr(cg)});
    };
    addMethod(func->second);
    return func->second;
}

LgsType* LgsSet::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsSet::applyOp(LgsType* other, const LgsOperator op) {
    const auto IRName = other->getName();
    switch (op) {
    case IN: {
        if (other->canCastTo(baseType)) return baseType;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsSet::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    return getLenFunc()->callIR(cg, {iterable});
}

Value* LgsSet::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    return cg.callLgsFunc("Set_contains", cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()}), {iterableExpr->IRValue, value->getIRPtr(cg)});
}

Value* LgsSet::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    LgsFunc f("get", &LGS_ANY, {this, &LGS_LONG}, BUILTIN | PUBLIC | METHOD);
    return f.callIR(cg, {iterable, index});
}

json::value LgsSet::asJsonStr() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}

