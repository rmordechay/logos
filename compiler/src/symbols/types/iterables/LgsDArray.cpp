#include "types/iterables/LgsDArray.h"
#include "Lgs_DArrayExpr.h"
#include "codegen/LgsLLVMGen.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsLong.h"

bool LgsDArray::inferBaseType(const std::vector<LgsExpr*>& args) {
    assert(!args.empty());
    if (baseType) return true;
    const auto baseExprType = args.front()->type;
    for (size_t i = 1; i < args.size(); ++i) {
        const auto arg = args[i];
        if (!baseExprType->equals(arg->type)) return false;
    }
    baseType = baseExprType->clone();
    return true;
}

Type* LgsDArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    IRType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy()}, name);
    return IRType;
}

Constant* LgsDArray::getRTType(LgsLLVMGen& cg) {
    const auto genericName = getGenericName();
    const auto st = cg.getStructType({cg.ptrTy()}, genericName);
    const auto sv = llvm::ConstantStruct::get(st, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(genericName, sizeBytes(), RTT_DARRAY, sv);
}

std::string LgsDArray::getName() {
    return name;
}

std::string LgsDArray::getGenericName() {
    return name + baseType->getGenericName();
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

std::string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

LgsType* LgsDArray::applyBinOp(LgsType* toType, LgsBinOp& op) {
    switch (op.opType) {
    case IN: {
        const auto otherIter = toType->asIterable();
        if (!otherIter) return nullptr;
        if (otherIter->getDimension() - 1 == getDimension()) return &LGS_BOOL;
        break;
    }
    default:
        break;
    }
    return nullptr;
}

Value* LgsDArray::lenIR(LgsLLVMGen& cg, Value* iterable) {
    return cg.callLgsFunc("DArray_len", cg.sizeTy(), {cg.ptrTy()}, {iterable});
}

Value* LgsDArray::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    return cg.callLgsFunc("DArray_contains", cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()}, {
        iterableExpr->IRValue,
        cg.getPtrTo(value->IRValue),
    });
}

Value* LgsDArray::getIRElement(LgsLLVMGen& cg, Value* iterable, Value* index) {
    return cg.callLgsFunc("DArray_get", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {iterable, index});;
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    if (!otherArr->baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

llvm::DIType* LgsDArray::getDebugType(LgsLLVMGen& cg) {
    const auto di = cg.debugger.diBuilder;
    const auto file = cg.debugger.diFile;
    constexpr auto ptrSizeInBits = sizeof(void*) * 8;
    const auto t_data = di->createPointerType(di->createBasicType("char", 8, llvm::dwarf::DW_ATE_unsigned_char), ptrSizeInBits);
    const auto t_length = di->createBasicType("size_t", ptrSizeInBits, llvm::dwarf::DW_ATE_unsigned);
    const auto t_capacity = t_length;
    const auto t_base = di->createPointerType(baseType->getDebugType(cg), ptrSizeInBits);
    llvm::Metadata* fields[] = {
        di->createMemberType(nullptr, "data", file, 0, ptrSizeInBits, ptrSizeInBits, 0, llvm::DINode::FlagZero, t_data),
        di->createMemberType(nullptr, "length", file, 0, ptrSizeInBits, ptrSizeInBits, ptrSizeInBits,llvm::DINode::FlagZero, t_length),
        di->createMemberType(nullptr, "capacity", file, 0, ptrSizeInBits, ptrSizeInBits, sizeof(void*) * 16,llvm::DINode::FlagZero, t_capacity),
        di->createMemberType(nullptr, "baseType", file, 0, ptrSizeInBits, ptrSizeInBits, sizeof(void*) * 24,llvm::DINode::FlagZero, t_base)
    };

    return di->createStructType(
        cg.debugger.subprogram,
        "Lgs_DArrayExpr",
        file,
        0,
        ptrSizeInBits * 4,
        ptrSizeInBits,
        llvm::DINode::FlagZero,
        nullptr,
        di->getOrCreateArray(fields)
    );
}

LgsType* LgsDArray::clone() {
    return new LgsDArray(baseType->clone());
}
