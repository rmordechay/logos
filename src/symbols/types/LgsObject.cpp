#include "types/LgsObject.h"
#include "codegen/CodegenMetadata.h"
#include "codegen/CodeGenerator.h"
#include "exprs/LgsNull.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

string LgsObject::prettyName() const {
    return name;
}

Type* LgsObject::getIRType() {
    if (IRType) return IRType;
    CodeGenerator::generateObjModule(this);
    size_t structPosition = 0;
    vector<Type*> elementTypes;

    // First field of any object is a ptr to its vtable
    elementTypes.push_back(ptrTy);;
    for (const auto& [_, field] : fields) {
        auto fieldType = field->type->getIRType();
        elementTypes.push_back(fieldType);
        field->position = structPosition++;
    }

    IRType = StructType::getTypeByName(context, name);
    if (!IRType) {
        IRType = StructType::create(context, elementTypes, name);
    }
    return IRType;
}

void LgsObject::setVirtualFuncs(vector<Type*>& elementTypes) const {
    vector<Type*> vtableTypes;
    for (const auto [_, method] : methods) {
        if (!method->implements) continue;
        method->funcType.isVirtual = true;
        vtableTypes.push_back(ptrTy);
    }
    const auto vtable = StructType::create(context, vtableTypes, name + "_vtable");
    elementTypes.push_back(vtable);
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
