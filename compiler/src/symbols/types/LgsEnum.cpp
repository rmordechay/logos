#include "types/LgsEnum.h"
#include "codegen/LgsCgModule.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"

LgsExpr* LgsEnum::getZeroValue() {
    return nullptr;
}

Type* LgsEnum::getIRType(LgsCgModule& cg) {
    if (const auto expr = fields.front()->expr) {
        return cg.getStructType({cg.sizeTy(), expr->type->getIRType(cg)});
    }
    return cg.getStructType({cg.sizeTy(), cg.ptrTy()});
}

Constant* LgsEnum::getRTType(LgsCgModule& cg) {
    assert(0);
}

std::string LgsEnum::getName() {
    return name;
}

bool LgsEnum::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return name == otherName;
}

LgsType* LgsEnum::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

std::string LgsEnum::fmtStr() const {
    return "%s";
}

size_t LgsEnum::sizeBytes() {
    return sizeof(void*);
}

DIType* LgsEnum::getDebugType(LgsCgModule& cg) {
    assert(0);
}
