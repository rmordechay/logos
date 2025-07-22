#include "types/LgsInterface.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsModule.h"
#include "types/LgsObject.h"
#include "utils/LgsUtils.h"

Type* LgsInterface::getIRType(LgsModule* module) {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(module->context, name);
    vector<Type*> elementTypes;
    for (int i = 0; i < methods.size(); ++i) {
        elementTypes.emplace_back(ptrTy(module));
    }
    if (!IRType) {
        IRType = StructType::create(module->context, elementTypes, name);
    }
    return IRType;
}

string LgsInterface::getIRName() {
    return name;
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
    return name;
}

LgsInterface::~LgsInterface() {
    for (const auto interface : interfaces) {
        delete interface;
    }
}
