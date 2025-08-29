

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsCharConst.h"


json::value LgsChar::asJSON() {
    assert(0);
}

std::string LgsChar::pname() {
    return name;
}

size_t LgsChar::getSizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsLLVMGen& cg) {
    return cg.i8Ty();
}

std::string LgsChar::getName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

std::string LgsChar::strFormatPart() const {
    return "%c";
}

bool LgsChar::canCastTo(LgsType* other) {
    return name == other->getName();
}