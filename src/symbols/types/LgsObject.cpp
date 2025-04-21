#include "types/LgsObject.h"
#include "CodeGenerator.h"
#include "exprs/LgsNull.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"

LgsObject::LgsObject(LgsObject& other) {
    name = other.name;
    for (const auto& [name, fieldPtr] : other.fields) {
        if (!fieldPtr) continue;
        fields[name] = new LgsField(*fieldPtr);
    }
    for (const auto& [name, methodList] : other.methods) {
        vector<LgsMethodImpl*> clonedList;
        for (const auto& methodPtr : methodList) {
            if (!methodPtr) continue;
            clonedList.emplace_back(new LgsMethodImpl(*methodPtr));
        }
        methods[name] = std::move(clonedList);
    }
}

const string LgsObject::getName() const {
    return name;
}

size_t LgsObject::size() {
    return sizeof(void*);
}

Type* LgsObject::getIRType() {
    if (IRType) return IRType;
    // CodeGenerator::generateObjModule(this);
    vector<Type*> elementTypes;
    for (const auto& [_, val] : fields) {
        auto fieldType = val->type->getIRType();
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
