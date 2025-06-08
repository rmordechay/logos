#include "types/LgsInterface.h"

#include "types/LgsObject.h"

Type* LgsInterface::getIRType(LgsRuntime* runtime) {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(context, interfaceName);
    vector<Type*> elementTypes;
    for (const auto [_, method] : methods) {
        method->funcType.isVirtual = true;
        elementTypes.emplace_back(runtime->builder.getPtrTy());
    }
    if (!IRType) {
        IRType = StructType::create(context, elementTypes, interfaceName);
    }
    return IRType;
}

string LgsInterface::getIRName() {
    return interfaceName;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(false);
}

bool LgsInterface::equals(LgsType* other) {
    // Interface must be checked first
    if (const auto interface = other->asInterface()) {
        if (interface->getIRName() == getIRName()) return true;
    } else if (const auto obj = other->asObject()) {
        for (const auto& implement : obj->interfaces) {
            if (implement->getIRName() == getIRName()) return true;
        }
    }
    return false;
}

LgsType* LgsInterface::inferBinaryType(LgsType* other) {
    assert(false);
}

string LgsInterface::prettyName() const {
    return interfaceName;
}
