#include "types/LgsEnum.h"

#include "logos/LgsRuntime.h"
#include "stmts/LgsField.h"

LgsExpr* LgsEnum::getZeroValue() {
    for (const auto& [_, field] : fields) {
        return field->expr;
    }
    assert(0);
}

Type* LgsEnum::getIRType() {
    return PointerType::getUnqual(context);
}

string LgsEnum::getIRName() {
    return name;
}

string LgsEnum::pName() const {
    return name;
}

bool LgsEnum::equals(LgsType* other) {
    return name == other->getIRName();
}

LgsType* LgsEnum::inferBinaryType(LgsType* other) {
    assert(0);
}
