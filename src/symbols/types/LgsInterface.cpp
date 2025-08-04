#include "types/LgsInterface.h"

#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"
#include "types/LgsObject.h"

#include "utils/LgsUtils.h"

Type* LgsInterface::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(codeGen->context, name);
    vector<Type*> elementTypes;
    for (int i = 0; i < methods.size(); ++i) {
        elementTypes.emplace_back(codeGen->ptrTy());
    }
    if (!IRType) {
        IRType = StructType::create(codeGen->context, elementTypes, name);
    }
    return IRType;
}

string LgsInterface::getName() {
    return name;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(0);
}

bool LgsInterface::equals(LgsType* other) {
    if (const auto interface = other->asInterface()) {
        if (interface->name == getName()) return true;
    } else if (const auto obj = other->asObject()) {
        if (obj->name == getName()) return true;
        for (const auto& implement : obj->interfaces) {
            if (implement->getName() == getName()) return true;
        }
    }
    return false;
}

size_t LgsInterface::getSizeBytes() {
    return 0;
}

string LgsInterface::prettyName() {
    return name;
}

LgsInterface::~LgsInterface() {
    for (const auto interface : interfaces) {
        delete interface;
    }
}
