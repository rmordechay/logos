#include "types/LgsInterface.h"
#include "funcs/LgsFunc.h"
#include "codegen/LgsLLVMGen.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

Type* LgsInterface::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    IRType = cg.ptrTy();
    return IRType;
}

LgsFunc* LgsInterface::getMethod(const std::string& methodName) {
    return LgsObject::getMethod(methodName);
}

std::string LgsInterface::getName() {
    return name;
}

LgsExpr* LgsInterface::getZeroValue() {
    assert(0);
}

Lgs_rttype LgsInterface::getRTType() {
    return LgsObject::getRTType();
}

bool LgsInterface::canCastTo(LgsType* other) {
    if (const auto interface = other->asInterface()) {
        if (interface->name == getName()) return true;
    } else if (const auto obj = other->asObject()) {
        if (obj->name == getName()) return true;
        for (const auto& implement : obj->implements) {
            if (implement->getName() == getName()) return true;
        }
    }
    return false;
}

size_t LgsInterface::getSizeBytes() {
    return 0;
}

LgsInterface::~LgsInterface() {
    for (const auto interface : implements) {
        delete interface;
    }
}
