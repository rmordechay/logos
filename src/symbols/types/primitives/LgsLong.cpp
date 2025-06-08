#include "types/primitives/LgsLong.h"




string LgsLong::prettyName() const {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    assert(false);
}

Type* LgsLong::getIRType() {
    return Type::getInt64Ty(context);
}

LgsExpr* LgsLong::getZeroValue() {
    assert(false);
}

LgsType* LgsLong::inferBinaryType(LgsType* other) {
    assert(false);
}

string LgsLong::getIRName() {
    return name;
}
