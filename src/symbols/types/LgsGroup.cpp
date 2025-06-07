#include "types/LgsGroup.h"

Type* LgsGroup::getIRType() {
    assert(false);
}

LgsExpr* LgsGroup::getZeroValue() {
    assert(false);
}

string LgsGroup::getIRName() {
    return name;
}

string LgsGroup::prettyName() const {
    return name;
}

bool LgsGroup::equals(LgsType* other) {
    assert(false);
}

LgsType* LgsGroup::inferBinaryType(LgsType* other) {
    assert(false);
}
