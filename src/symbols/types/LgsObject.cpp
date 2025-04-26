#include "types/LgsObject.h"
#include "CodeGenerator.h"
#include "exprs/LgsNull.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"

const string LgsObject::getName() const {
    return name;
}

size_t LgsObject::size() {
    return sizeof(void*);
}

Type* LgsObject::getIRType() {
    if (IRType) return IRType;
    CodeGenerator::generateObjModule(this);
    vector<Type*> elementTypes;
    for (const auto& [_, field] : fields) {
        auto fieldType = field->type->getIRType();
        elementTypes.push_back(fieldType);
    }
    const auto typeByName = StructType::getTypeByName(context, name);
    if (typeByName) {
        IRType = typeByName;
    } else {
        IRType = StructType::create(context, elementTypes, name);
    }
    return IRType;
}

LgsExpr* LgsObject::getZeroValue() {
    if (nullable) return new LgsNull();
    // TODO return empty constructor
    return nullptr;
}

LgsType* LgsObject::inferBinaryType(LgsType* other) {
    return this;
}

bool LgsObject::equals(LgsType* other) const {
    return name == other->getName();
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

LgsObject* LgsObject::clone() {
    const auto newObj = new LgsObject(*this);
    newObj->name = name;
    for (const auto& [name, field] : fields) {
        newObj->fields[name] = new LgsField(*field);
    }
    // for (const auto& [name, methodList] : other.methods) {
    //     vector<LgsMethodImpl*> clonedList;
    //     for (const auto& method : methodList) {
    //         clonedList.emplace_back(new LgsMethodImpl(*method));
    //     }
    //     methods[name] = std::move(clonedList);
    // }
    newObj->methods = methods;
    return newObj;
}