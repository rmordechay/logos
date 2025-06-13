#include "types/LgsObject.h"
#include "codegen/CodeGenerator.h"
#include "exprs/LgsNull.h"
#include "exprs/unary/LgsInstance.h"
#include "stmts/LgsField.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

string LgsObject::prettyName() const {
    return name;
}

Type* LgsObject::getIRType() {
    if (IRType) return IRType;
    vector<Type*> elementTypes;
    auto fieldPos = 0;
    if (vtable) {
        elementTypes.push_back(PointerType::getUnqual(context));
        fieldPos++;
    }
    for (const auto& [_, field] : fields) {
        auto fieldType = field->type->getIRType();
        field->position = fieldPos++;
        elementTypes.push_back(fieldType);
    }
    IRType = StructType::getTypeByName(context, name);
    if (!IRType) {
        IRType = StructType::create(context, elementTypes, name);
    }
    return IRType;
}

LgsExpr* LgsObject::getZeroValue() {
    if (isNullable) return new LgsNull();
    assert(0);
}

LgsType* LgsObject::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsObject::equals(LgsType* other) {
    if (const auto group = other->asGroup()) {
        for (const auto groupType : group->types) {
            if (name == groupType->getIRName()) {
                return true;
            }
        }
        return false;
    }
    return name == other->getIRName();
}

LgsInterface* LgsObject::getInterface(const string& interfaceName) const {
    for (const auto implement : interfaces) {
        const auto interface = implement->asInterface();
        if (interface->interfaceName == interfaceName) {
            return interface;
        }
    }
    return nullptr;
}

LgsObject* LgsObject::clone() {
    const auto newObj = new LgsObject(name, path);
    for (const auto& [name, field] : fields) {
        const auto newField = field->clone();
        newField->parent = newObj;
        newObj->fields[name] = newField;
    }
    newObj->methods = methods;
    newObj->interfaces = interfaces;
    return newObj;
}

void LgsObject::setVFuncs(LgsRuntime* runtime) const {
    assert(runtime);
    const auto vtablePtr = vtable->getIRValue(runtime);
    for (const auto [_, method] : methods) {
        const auto keyIRStr = getIRStr(runtime, method->funcType->getIRName());
        const auto IRFunc = method->getIRFunc(runtime);
        auto valuePtr = runtime->builder.CreateAlloca(runtime->builder.getPtrTy());
        runtime->builder.CreateStore(IRFunc, valuePtr);
        vtable->type->asMap()->addFunc.callIR(runtime, {vtablePtr, keyIRStr, valuePtr});
    }
}

string LgsObject::getIRName() {
    return name;
}

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& [name, field] : fields) {
        sum += field->type->getSizeBytes();
    }
    return sum;
}
