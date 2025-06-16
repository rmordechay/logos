#include "types/LgsInterface.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsRuntime.h"
#include "types/LgsObject.h"

Type* LgsInterface::getIRType() {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(context, interfaceName);
    vector<Type*> elementTypes;
    for (const auto [_, method] : methods) {
        method->funcType->isVirtual = true;
        elementTypes.emplace_back(PointerType::getUnqual(context));
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
    assert(0);
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

string LgsInterface::prettyName() const {
    return interfaceName;
}
