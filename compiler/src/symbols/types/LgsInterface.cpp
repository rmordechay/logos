#include "types/LgsInterface.h"
#include "codegen/LgsCgModule.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

Type* LgsInterface::getIRType(LgsCgModule& cg) {
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

size_t LgsInterface::sizeBytes() {
    return 0;
}

llvm::DIType* LgsInterface::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsInterface* LgsInterface::clone() {
    const auto newInterface = new LgsInterface(*this);
    cloneFields(newInterface);
    cloneMethods(newInterface);
    return newInterface;
}
