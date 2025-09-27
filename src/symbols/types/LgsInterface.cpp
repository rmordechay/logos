#include "types/LgsInterface.h"
#include "funcs/LgsFunc.h"
#include "codegen/LgsLLVMGen.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

Type* LgsInterface::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    std::vector<Type*> elementTypes;
    for (int i = 0; i < methods.size(); ++i) {
        elementTypes.emplace_back(cg.ptrTy());
    }
    IRType = cg.getStructType(elementTypes, name);
    return IRType;
}

std::string LgsInterface::getName() {
    return name;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(0);
}

Lgs_RTType LgsInterface::getRTType() {
    return LgsObject::getRTType();
}

bool LgsInterface::canCastTo(LgsType* other) {
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

json::value LgsInterface::asJsonStr() {
    assert(0);
}

LgsInterface::~LgsInterface() {
    for (const auto interface : interfaces) {
        delete interface;
    }
}
