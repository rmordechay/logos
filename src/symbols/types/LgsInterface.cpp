#include "types/LgsInterface.h"
#include "funcs/LgsFunc.h"
#include "logos/LgsCodeGen.h"
#include "stmts/LgsField.h"
#include "types/LgsObject.h"

Type* LgsInterface::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    IRType = StructType::getTypeByName(codeGen->context, name);
    std::vector<Type*> elementTypes;
    for (int i = 0; i < methods.size(); ++i) {
        elementTypes.emplace_back(codeGen->ptrTy());
    }
    if (!IRType) {
        IRType = StructType::create(codeGen->context, elementTypes, name);
    }
    return IRType;
}

LgsField* LgsInterface::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == name) return f;
    }
    for (const auto interface : interfaces) {
        const auto interfaceField = interface->getField(fieldName);
        if (interfaceField) {
            return interfaceField;
        }
    }
    return nullptr;
}

LgsFunc* LgsInterface::getMethod(const std::string& methodName) {
    const auto method = methods.find(methodName);
    if (method != methods.end()) {
        return method->second;
    }
    for (const auto interface : interfaces) {
        const auto interfaceMethod = interface->getMethod(methodName);
        if (interfaceMethod) {
            return interfaceMethod;
        }
    }
    return nullptr;
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
        for (const auto& implement : obj->interfaces) {
            if (implement->getName() == getName()) return true;
        }
    }
    return false;
}

size_t LgsInterface::getSizeBytes() {
    return 0;
}

json::value LgsInterface::asJSON() {
    assert(0);
}

std::string LgsInterface::pname() {
    return name;
}

LgsInterface::~LgsInterface() {
    for (const auto interface : interfaces) {
        delete interface;
    }
}
