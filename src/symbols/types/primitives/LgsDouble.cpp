#include "types/primitives/LgsDouble.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "logos/LgsCodeGen.h"

std::string LgsDouble::getName() {
    return name;
}

json::value LgsDouble::asJSON() {
    assert(0);
}

std::string LgsDouble::pname() {
    return getName();
}

size_t LgsDouble::getSizeBytes() {
    return sizeof(double_t);
}

LgsExpr* LgsDouble::getZeroValue() {
    return new LgsFloatConst(this, 0.0);
}

std::string LgsDouble::strFormatPart() const {
    return "%f";
}

Type* LgsDouble::getIRType(LgsCodeGen* codeGen) {
    return codeGen->builder.getDoubleTy();
}

bool LgsDouble::canCastTo(LgsType* other) {
    return name == other->getName();
}
