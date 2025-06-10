#include "types/LgsGroup.h"

Type* LgsGroup::getIRType() {
    return PointerType::getUnqual(context);
}

LgsExpr* LgsGroup::getZeroValue() {
    assert(0);
}

string LgsGroup::getIRName() {
    return name;
}

string LgsGroup::prettyName() const {
    return name;
}

bool LgsGroup::equals(LgsType* other) {
    for (const auto type : types) {
        if (type->equals(other)) return true;
    }
    return false;
}

LgsType* LgsGroup::inferBinaryType(LgsType* other) {
    assert(0);
}
