#include "types/LgsObject.h"
#include "exprs/LgsInstance.h"
#include "stmts/LgsField.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "utils/LgsUtils.h"

#include <llvm/IR/Module.h>

Type* LgsObject::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    std::vector<Type*> elementTypes;
    elementTypes.reserve(fields.size());
    for (int i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        field->position = i;
        Type* fieldType;
        const auto ptr = field->type->asObject() || field->type->asFuncType() || field->type->asInterface() || field->type->asDArray();
        if (ptr) {
            fieldType = cg.ptrTy();
        } else {
            fieldType = field->type->getIRType(cg);
        }
        elementTypes.push_back(fieldType);
    }
    IRType = StructType::getTypeByName(cg.context, name);
    if (!IRType) {
        IRType = StructType::create(cg.context, elementTypes, name);
    }
    for (const auto& field : fields) {
        field->parentIRType = IRType;
    }
    return IRType;
}

LgsField* LgsObject::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
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
    for (const auto* f : fields) {
        if (f->name != methodName) continue;
        if (f->expr && f->expr->asFunc()) {
            return f->expr->asFunc();
        }
    }
    for (const auto interface : interfaces) {
        const auto interfaceMethod = interface->getMethod(methodName);
        if (interfaceMethod) {
            return interfaceMethod;
        }
    }
    return nullptr;
}

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& field : fields) {
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
    bool first = true;
    for (const auto& field : fields) {
        if (!first) str << ", ";
        str << field->name << " = " << field->type->strFormatPart();
        first = false;
    }
    str << '}';
    return str.str();
}

bool LgsObject::hasVirtuals() const {
    return std::any_of(methods.begin(), methods.end(), [](const auto& pair) {
        return pair.second->funcType->isVirtual;
    });
}

LgsObject* LgsObject::clone() {
    const auto cloned = new LgsObject(*this);
    cloned->fields.clear();
    for (const auto& field : fields) {
        const auto newField = new LgsField(*field);
        if (field->expr) {
            assert(0);
        }
        cloned->addField(newField);
    }
    return cloned;
}

std::string LgsObject::getName() {
    return name;
}

std::string LgsObject::pname() {
    return name;
}

bool LgsObject::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    if (const auto otherInterface = other->asInterface()) {
        for (const auto objInterface : interfaces) {
            if (objInterface->getName() == otherInterface->name) {
                return true;
            }
        }
        return false;
    }
    if (const auto otherGroup = other->asGroup()) {
        for (const auto otherGroupType : otherGroup->types) {
            if (name == otherGroupType->getName()) {
                return true;
            }
        }
        return false;
    }
    return name == other->getName();
}

json::value LgsObject::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = getName();
    json::array jsonFields;
    for (const auto& field : fields) {
        jsonFields.emplace_back(field->asJSON());
    }
    jsonObj["fields"] = jsonFields;
    return jsonObj;
}

