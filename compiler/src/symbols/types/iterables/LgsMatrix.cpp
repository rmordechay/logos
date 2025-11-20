#include "types/iterables/LgsMatrix.h"
#include "exprs/LgsMatrixExpr.h"

Type* LgsMatrix::getIRType(LgsLLVMGen& cg) {
    return ArrayType::get(baseType->getIRType(cg), rows * columns);
}

size_t LgsMatrix::sizeBytes() {
    assert(0);
}

LgsExpr* LgsMatrix::getZeroValue() {
    return new LgsMatrixExpr(rows, columns);
}

Lgs_TypeKind LgsMatrix::getRTTypeKind() {
    assert(0);
}

std::string LgsMatrix::getName() {
    return "Mat" + std::to_string(rows) + "x" + std::to_string(columns);
}

bool LgsMatrix::canCastTo(LgsType* other) {
    if (getName() == other->getName()) return true;
    return false;
}

std::string LgsMatrix::strFormatPart() const {
    assert(0);
}

Value* LgsMatrix::lengthIR(LgsLLVMGen& cg, Value* iterable) {
    assert(0);
}

Value* LgsMatrix::inIR(LgsLLVMGen& cg, LgsExpr* iterableExpr, LgsExpr* value) {
    assert(0);
}
