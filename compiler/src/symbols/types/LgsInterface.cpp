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
    assert(0);
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

Constant* LgsInterface::getRTType(LgsCgModule& cg) {
    assert(0);
}

std::string LgsInterface::strFormatPart() const {
    assert(0);
}
