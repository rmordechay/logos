#include "types/LgsNullable.h"
#include "logos/LgsModule.h"
#include "utils/LgsUtils.h"

Type* LgsNullable::getIRType(LLVMContext& context) {
    return ptrTy(context);
}

string LgsNullable::getIRName() {
    assert(0);
}

LgsExpr* LgsNullable::getZeroValue() {
    return baseType->getZeroValue();
}

string LgsNullable::prettyName() const {
    return baseType->prettyName() + '?';
}

bool LgsNullable::equals(LgsType* other) {
    assert(0);
}
