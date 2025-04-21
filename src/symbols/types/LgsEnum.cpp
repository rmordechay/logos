#include "types/LgsEnum.h"

#include "stmts/LgsField.h"

LgsExpr* LgsEnum::getZeroValue() {
    for (const auto& [_, field] : fields) {
        return field->expr;
    }
    assert(false);
}

size_t LgsEnum::size() {
    return sizeof(void*);
}

Type* LgsEnum::getIRType() {
    return ptrTy;
}

json LgsEnum::asJSON() const {
    json tree;
    tree["name"] = name;
    return tree;
}

const string LgsEnum::getName() const {
    return name;
}

bool LgsEnum::equals(LgsType* other) const {
    return name == other->getName();
}

LgsType* LgsEnum::inferBinaryType(LgsType* other) {
    assert(false);
}
