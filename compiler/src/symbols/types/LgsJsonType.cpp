#include "types/LgsJsonType.h"
#include <cassert>

size_t LgsJsonType::sizeBytes() {
    assert(0);
}

LgsExpr* LgsJsonType::getZeroValue() {
    assert(0);
}

Type* LgsJsonType::getIRType(LgsCodeGen& cg) {
    assert(0);
}

Constant* LgsJsonType::getRTType(LgsCodeGen& cg) {
    assert(0);
}

bool LgsJsonType::canCastTo(LgsType* other) {
    return true;
}

std::string LgsJsonType::fmtStr() const {
    assert(0);
}

DIType* LgsJsonType::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

LgsType* LgsJsonType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsJsonType::getName() {
    return name;
}

