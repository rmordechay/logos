#include "types/LgsVector.h"

#include "exprs/unary/vectors/LgsVec2.h"

std::string LgsVector::getName() {
    return name;
}

std::string LgsVector::prettyName() {
    return getName();
}

Type* LgsVector::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    IRType = ArrayType::get(codeGen->i1Ty(), size);
    return IRType;
}

size_t LgsVector::getSizeBytes() {
    return sizeof(float) * size;
}

LgsExpr* LgsVector::getZeroValue() {
    return new LgsVec2();
}

LgsType* LgsVector::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsVector::getUnpackCount() const {
    return 1;
}

Value* LgsVector::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return sizeExpr->getIRValue(codeGen);
}

Value* LgsVector::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getFalse();
}

Value* LgsVector::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getTrue();
}

bool LgsVector::equals(LgsType* other) {
    assert(0);
}
