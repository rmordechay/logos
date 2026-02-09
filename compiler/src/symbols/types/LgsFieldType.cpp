#include "types/LgsFieldType.h"

#include <cassert>

#include "LgsDefinitions.h"
#include "LgsRTTIndices.h"
#include "types/LgsObject.h"

std::string LgsFieldType::getName() {
    return name;
}

size_t LgsFieldType::sizeBytes() {
    return sizeof(Lgs_Field);
}

LgsExpr* LgsFieldType::getZeroValue() {
    return nullptr;
}

Type* LgsFieldType::getIRType(LgsCodeGen& cg) {
    return getFieldRTTStruct(cg);
}

bool LgsFieldType::canCastTo(LgsType* other) {
    if (other->isAny()) return true;
    return equals(other);
}

LgsType* LgsFieldType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    return nullptr;
}

std::string LgsFieldType::fmtStr() const {
    return "%s";
}

DIType* LgsFieldType::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Value* LgsFieldType::loadRTName(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getFieldRTTStruct(cg), ptr, LgsFieldIndices::name, cg.ptrTy());
}

Value* LgsFieldType::loadRTSize(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getFieldRTTStruct(cg), ptr, LgsFieldIndices::size, cg.sizeTy());
}

Value* LgsFieldType::loadRTOffset(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getFieldRTTStruct(cg), ptr, LgsFieldIndices::offset, cg.sizeTy());
}

Value* LgsFieldType::loadRTKind(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getFieldRTTStruct(cg), ptr, LgsFieldIndices::kind, cg.i32Ty());
}

Value* LgsFieldType::loadRTType(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getFieldRTTStruct(cg), ptr, LgsFieldIndices::type, cg.ptrTy());
}

StructType* LgsFieldType::getFieldRTTStruct(LgsCodeGen& cg) {
    constexpr auto rttName = std::string(LGS_TYPEINFO_PREFIX) + "field";
    return cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.i32Ty(), cg.ptrTy()}, rttName);
}
