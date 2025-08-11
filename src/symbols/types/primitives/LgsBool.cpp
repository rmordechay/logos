
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/LgsNull.h"


string LgsBool::prettyName() {
    return name;
}

Type* LgsBool::getIRType(LgsCodeGen* codeGen) {
    return codeGen->i1Ty();
}

string LgsBool::getName() {
    return name;
}

LgsExpr* LgsBool::getZeroValue() {
    return new LgsBoolConst(false);
}

bool LgsBool::equals(LgsType* other) {
    if (asNullable()) {
        return name == other->getName();
    }
    return name == other->getName();
}

string LgsBool::getStrFormatPart() const {
    return "%d";
}

size_t LgsBool::getSizeBytes() {
    return sizeof(bool);
}
