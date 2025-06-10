#include "types/primitives/LgsLong.h"

#include "logos/LgsRuntime.h"
#include "types/LgsAny.h"

string LgsLong::prettyName() const {
    return name;
}

bool LgsLong::equals(LgsType* other) {
    if (other->getIRName() == LgsAny::name) return true;
    return name == other->getIRName();
}

Type* LgsLong::getIRType() {
    return Type::getInt64Ty(context);
}

LgsExpr* LgsLong::getZeroValue() {
    assert(0);
}

LgsType* LgsLong::inferBinaryType(LgsType* other) {
    assert(0);
}

string LgsLong::getStrFormatPart() const {
    return "%lu";
}

string LgsLong::getIRName() {
    return name;
}
