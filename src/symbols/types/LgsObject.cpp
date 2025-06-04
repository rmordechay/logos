#include "types/LgsObject.h"

#include "codegen/CodeGenerator.h"
#include "exprs/LgsNull.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

string LgsObject::prettyName() const {
    return name;
}

Type* LgsObject::getIRType(LgsRuntime* runtime) {
    if (IRType) return IRType;
    size_t structPosition = 0;
    vector<Type*> elementTypes;

    // First field of any object is a ptr to its vtable
    elementTypes.push_back(runtime->builder.getPtrTy());;
    for (const auto& [_, field] : fields) {
        auto fieldType = field->type->getIRType(runtime);
        elementTypes.push_back(fieldType);
        field->position = structPosition++;
    }

    IRType = StructType::getTypeByName(runtime->context, name);
    if (!IRType) {
        IRType = StructType::create(runtime->context, elementTypes, name);
    }
    return IRType;
}

LgsExpr* LgsObject::getZeroValue() {
    if (isNullable) return new LgsNull();
    // TODO return empty constructor
    return nullptr;
}

LgsType* LgsObject::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsObject::equals(LgsType* other) {
    // TODO make Object object
    if (name == LOGOS_PARENT_OBJ) return true;
    return name == other->getIRName();
}

json LgsObject::asJSON() const {
    json tree;
    tree["name"] = name;
    tree["fields"] = {};
    for (const auto& field : fields) {
        tree["fields"].emplace_back(field.second->asJSON());
    }
    return tree;
}

LgsInterface* LgsObject::getInterface(const string& interfaceName) const {
    for (const auto implement : implements) {
        const auto interface = implement->asInterface();
        if (interface->interfaceName == interfaceName) {
            return interface;
        }
    }
    return nullptr;
}

LgsObject* LgsObject::clone() {
    const auto newObj = new LgsObject(*this);
    newObj->name = name;
    for (const auto& [name, field] : fields) {
        newObj->fields[name] = new LgsField(*field);
    }
    for (const auto interface : implements) {
        newObj->implements.emplace_back(new LgsInterface(*interface->asInterface()));
    }
    newObj->methods = methods;
    return newObj;
}

string LgsObject::getIRName() {
    return name;
}
