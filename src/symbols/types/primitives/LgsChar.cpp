

#include "exprs/LgsNull.h"
#include "exprs/unary/constants/LgsCharConst.h"


string LgsChar::prettyName() {
    return name;
}

size_t LgsChar::getSizeBytes() {
    return sizeof(char);
}

Type* LgsChar::getIRType(LgsCodeGen* codeGen) {
    return codeGen->i8Ty();
}

string LgsChar::getName() {
    return name;
}

LgsExpr* LgsChar::getZeroValue() {
    return new LgsCharConst('0');
}

string LgsChar::getStrFormatPart() const {
    return "%c";
}

bool LgsChar::equals(LgsType* other) {
    return name == other->getName();
}