#include "types/iterables/LgsSet.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsFuncCall.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsFuncType.h"
#include "types/primitives/LgsVoid.h"
#include "types/iterables/LgsDArray.h"
#include "types/primitives/LgsLong.h"

Type* LgsSet::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    return getArrStruct(cg);
}

size_t LgsSet::sizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsSet::getZeroValue() {
    assert(0);
}

Lgs_TypeKind LgsSet::getRTTypeKind() {
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
    func->second->fn = [func](LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args) {
        return func->second->callIR(cg, {args[0].expr->IRValue, cg.getPtrTo(args[1].expr->IRValue)});
    };
    addMethod(func->second);
    return func->second;
}

LgsType* LgsSet::applyBinOp(LgsBinaryExpr* binExpr) {
    const auto other = binExpr->right->type;
    const auto IRName = other->getName();
    switch (binExpr->op) {
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
    return cg.callLgsFunc("Set_contains", cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()}, {iterableExpr->IRValue, cg.getPtrTo(value->IRValue)});
}

Value* LgsSet::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    LgsFunc f("get", &LGS_ANY, {this, &LGS_LONG}, BUILTIN | PUBLIC | METHOD);
    return f.callIR(cg, {iterable, index});
}