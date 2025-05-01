#include "types/LgsObject.h"
#include "CodeGenerator.h"
#include "exprs/LgsNull.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

const string LgsObject::getName() const {
    return name;
}

Type* LgsObject::getIRType() {
    if (IRType) return IRType;
    CodeGenerator::generateObjModule(this);

    vector<Type*> elementTypes;
    size_t structPosition = 0;
    for (const auto& [_, field] : fields) {
        auto fieldType = field->type->getIRType();
        elementTypes.push_back(fieldType);
        field->position = structPosition++;
    }

    for (const auto& implement : implements) {
        elementTypes.push_back(implement->getIRType());
    }

    IRType = StructType::getTypeByName(context, name);
    if (!IRType) {
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
    // TODO make Object object
    if (name == "Object") return true;
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
    newObj->methods = methods;
    return newObj;
}