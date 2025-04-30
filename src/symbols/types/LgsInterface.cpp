#include "types/LgsInterface.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

const string LgsInterface::getName() const {
    return name;
}

Type* LgsInterface::getIRType() {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(context, name);
    vector<Type*> elementTypes;
    size_t structPosition = 0;
    for (const auto method : getAllMethods()) {
        method->vtableKey = structPosition++;
        elementTypes.emplace_back(ptrTy);
    }
    if (!IRType) {
        IRType = StructType::create(context, elementTypes, name);
    }
    return IRType;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(false);
}

bool LgsInterface::equals(LgsType* other) const {
    if (const auto obj = other->asObject()) {
        for (const auto& implement : obj->implements) {
            if (implement->getName() == name) return true;
        }
    }
    return false;
}

LgsType* LgsInterface::inferBinaryType(LgsType* other) {
    assert(false);
}
