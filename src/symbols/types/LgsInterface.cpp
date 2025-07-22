#include "types/LgsInterface.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsModule.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Type* LgsInterface::getIRType(LgsModule* module) {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(module->context, interfaceName);
    vector<Type*> elementTypes;
    for (const auto [_, method] : methods) {
        method->funcType->isVirtual = true;
        elementTypes.emplace_back(ptrTy(module));
    }
    if (!IRType) {
        IRType = StructType::create(module->context, elementTypes, interfaceName);
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

LgsInterface::~LgsInterface() {
    for (const auto interface : interfaces) {
        delete interface;
    }
}
