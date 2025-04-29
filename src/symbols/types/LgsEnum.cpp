#include "types/LgsEnum.h"

#include "stmts/LgsField.h"

LgsExpr* LgsEnum::getZeroValue() {
    for (const auto& [_, field] : fields) {
        return field->expr;
    }
    assert(false);
}

Type* LgsEnum::getIRType() {
    return ptrTy;
}

json LgsEnum::asJSON() const {
    json tree;
    tree["name"] = name;
    tree["fields"] = {};
    for (const auto& field : fields) {
        tree["fields"].emplace_back(field.second->asJSON());
    }
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
