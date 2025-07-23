#include "types/LgsObject.h"
#include "exprs/unary/LgsInstance.h"
#include "stmts/LgsField.h"
#include "types/LgsGroup.h"
#include "utils/LgsUtils.h"

string LgsObject::prettyName() const {
    return name;
}

string LgsObject::getIRName() {
    return name;
}

Type* LgsObject::getIRType(LgsModule* module) {
    if (IRType) return IRType;
    // Add one or zero if table exists
    const size_t offset = !!vtable;
    vector<Type*> elementTypes(fields.size() + offset);
    size_t position = 0;
    if (vtable) {
        setVirtualFuncs(module);
        elementTypes[position++] = vtable->type->getIRType(module);
    }
    for (const auto [_, field] : fields) {
        const auto fieldType = field->type->getIRType(module);
        field->position = position++;
        elementTypes[field->position + offset] = fieldType;
    }
    IRType = StructType::getTypeByName(module->context, name);
    if (!IRType) {
        IRType = StructType::create(module->context, elementTypes, name);
    }
    return IRType;
}

LgsExpr* LgsObject::getZeroValue() {
    return new LgsInstance(this);
}

string LgsObject::getStrFormatPart() const {
    stringstream str;
    str << '{';
    for (const auto [name, field] : fields) {
        str << name << " = " << field->type->getStrFormatPart();
    }
    str << '}';
    return str.str();
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

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& [name, field] : fields) {
        sum += field->type->getSizeBytes();
    }
    return sum;
}

void LgsObject::setVirtualFuncs(LgsModule* module) {
    const auto vtablePtr = vtable->getIRValue(module);
    // for (const auto [_, method] : methods) {
    //     if (!method->funcType->isVirtual) continue;
    //     const auto keyIRStr = getIRStr(module, method->funcType->getIRName());
    //     const auto IRFunc = method->getIRFunc(module);
    //     auto valuePtr = module->builder.CreateAlloca(module->builder.getPtrTy());
    //     module->builder.CreateStore(IRFunc, valuePtr);
    //     vtable->type->asMap()->addFunc.callIR(module, {vtablePtr, keyIRStr, valuePtr});
    // }
}

LgsObject::~LgsObject() {
    for (const auto interface : interfaces) {
        delete interface;
    }
}
