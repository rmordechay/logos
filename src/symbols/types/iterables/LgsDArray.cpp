#include "types/iterables/LgsDArray.h"
#include "exprs/LgsArrayExpr.h"
#include "types/LgsVoid.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

Type* LgsDArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    return getArrStruct(cg);
}

std::string LgsDArray::getName() {
    return name;
}

std::string LgsDArray::pname() {
    return baseType->pname() + "[]";
}

size_t LgsDArray::getSizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Lgs_RTType LgsDArray::getRTType() {
    return RTT_DARRAY;
}

LgsType* LgsDArray::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsDArray::getUnpackCount() const {
    return 1;
}

std::string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

StructType* LgsDArray::getArrStruct(LgsLLVMGen& cg) {
    if (arrStruct) return arrStruct;
    arrStruct = cg.getStructType({cg.i64Ty(), cg.ptrTy()}, name);
    return arrStruct;
}

LgsFunc* LgsDArray::getAddFunc() {
    const auto func = methods.find(ADD_FUNC_NAME);
    if (func != methods.end() && func->second) return func->second;
    func->second = new LgsFunc(ADD_FUNC_NAME, &LGS_VOID, {this, &LGS_ANY}, BUILTIN | PUBLIC | METHOD);
    func->second->fn = [func](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
        return func->second->callIR(cg, {args[0]->IRValue, args[1]->getIRPtrTo(cg)});
    };
    addMethod(func->second);
    return func->second;
}

Value* LgsDArray::IRLength(LgsLLVMGen& cg, Value* iterable) {
    return getLenFunc()->callIR(cg, {iterable});
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

json::value LgsDArray::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}
