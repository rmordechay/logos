#include "types/primitives/LgsLong.h"

#include "logos/LgsRuntime.h"

string LgsLong::prettyName() const {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    if (other->getIRName() == "Any") return true;
    return name == other->getIRName();
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

string LgsLong::getStrFormatPart() const {
    return "%lu";
}

string LgsLong::getIRName() {
    return name;
}
