#include "types/LgsObject.h"
#include "exprs/unary/LgsInstance.h"
#include "stmts/LgsField.h"
#include "types/LgsGroup.h"
#include "utils/LgsUtils.h"

LgsObject* LgsObject::clone() {
    const auto cloned = new LgsObject(*this);
    cloned->fields.clear();
    for (const auto& [fieldName, field] : fields) {
        cloned->fields[fieldName] = new LgsField(*field);
    }
    return cloned;
}

bool LgsObject::hasVirtuals() const {
    return std::any_of(methods.begin(), methods.end(), [](const auto& pair) {
        return pair.second->funcType->isVirtual;
    });
}

Type* LgsObject::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    // const auto fieldsStartOffset = hasVirtuals();
    std::vector<Type*> elementTypes(fields.size());
    int iCounter = 0;
    for (const auto& [fieldName, field] : fields) {
        field->position = iCounter++;
        Type* fieldType;
        if (field->type->asObject()) {
            fieldType = codeGen->ptrTy();
        } else {
            fieldType = field->type->getIRType(codeGen);
        }
        elementTypes[field->position] = fieldType;
    }
    IRType = StructType::getTypeByName(codeGen->context, name);
    if (!IRType) {
        IRType = StructType::create(codeGen->context, elementTypes, name);
    }
    for (const auto& [_, field] : fields) {
        field->parentIRType = IRType;
    }
    return IRType;
}

LgsField* LgsObject::getField(const std::string& fieldName) {
    const auto field = fields.find(fieldName);
    if (field != fields.end()) {
        return field->second;
    }
    for (const auto interface : interfaces) {
        const auto interfaceField = interface->getField(fieldName);
        if (interfaceField) {
            return interfaceField;
        }
    }
    return nullptr;
}

LgsFunc* LgsObject::getMethod(const std::string& methodName) {
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

void LgsObject::freeValue(LgsCodeGen* codeGen, Value* value) {
    codeGen->builder.CreateFree(value);
}

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& [_, field] : fields) {
        if (name == field->type->getName()) {
            sum += sizeof(void*);
        } else {
            sum += field->type->getSizeBytes();
        }
    }
    return sum;
}

LgsExpr* LgsObject::getZeroValue() {
    return new LgsInstance(this);
}

std::string LgsObject::strFormatPart() const {
    std::stringstream str;
    str << '{';
    for (const auto& [fieldName, field] : fields) {
        str << fieldName << " = " << field->type->strFormatPart();
    }
    str << '}';
    return str.str();
}

bool LgsObject::equals(LgsType* other) {
    if (const auto group = other->asGroup()) {
        for (const auto groupType : group->types) {
            if (name == groupType->getName()) {
                return true;
            }
        }
        return false;
    }
    return name == other->getName();
}

std::string LgsObject::getName() {
    return name;
}

json::object LgsObject::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = getName();
    json::array jsonFields;
    for (auto& [_, field] : fields) {
        jsonFields.emplace_back(field->asJSON());
    }
    jsonObj["fields"] = jsonFields;
    return jsonObj;
}

std::string LgsObject::pname() {
    return name;
}

LgsObject::~LgsObject() {
    for (const auto interface : interfaces) {
        freeType(interface);
    }
    interfaces.clear();
}
