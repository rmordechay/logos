#include "types/LgsVec2.h"
#include "exprs/unary/vectors/LgsVector.h"

std::string LgsVec2::getName() {
    return name;
}

std::string LgsVec2::prettyName() {
    return getName();
}

Type* LgsVec2::getIRType(LgsCodeGen* codeGen) {
    IRType = FixedVectorType::get(baseType->getIRType(codeGen), 2);
    return IRType;
}

size_t LgsVec2::getSizeBytes() {
    return sizeof(float) * 2;
}

LgsExpr* LgsVec2::getZeroValue() {
    return new LgsVector();
}

LgsType* LgsVec2::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsVec2::getUnpackCount() const {
    return 1;
}

Value* LgsVec2::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->isize(2);
}

Value* LgsVec2::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getFalse();
}

Value* LgsVec2::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return codeGen->builder.getTrue();
}

bool LgsVec2::equals(LgsType* other) {
    assert(0);
}
