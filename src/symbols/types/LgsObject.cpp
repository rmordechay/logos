#include "types/LgsObject.h"
#include "exprs/LgsInstance.h"
#include "stmts/LgsField.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "types/LgsSubType.h"

#include <llvm/IR/Module.h>

LgsFunc* LgsObject::getMethod(const std::string& methodName) {
    const auto method = methods.find(methodName);
    if (method != methods.end() && method->second) {
        return method->second;
    }
    for (const auto* f : fields) {
        if (f->name != methodName) continue;
        if (f->expr && f->expr->asFunc()) {
            return f->expr->asFunc();
        }
    }
    for (const auto interface : implements) {
        const auto interfaceMethod = interface->getMethod(methodName);
        if (interfaceMethod) {
            return interfaceMethod;
        }
    }
    return nullptr;
}

Type* LgsObject::getIRType(LgsLLVMGen& cg) {
    const auto type = cg.typesRegistry.find(name);
    if (type != cg.typesRegistry.end()) return type->second;
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
    IRType = StructType::create(cg.context, elementTypes, name);
    for (const auto& field : fields) {
        field->parentIRType = IRType;
    }
    cg.typesRegistry[name] = IRType;
    return IRType;
}

size_t LgsObject::getSizeBytes() {
    size_t sum = 0;
    for (const auto& field : fields) {
        if (field->type->asObject() || field->type->asFuncType() || field->type->asInterface() || field->type->asDArray()) {
            sum += sizeof(void*);
        } else {
            sum += field->type->getSizeBytes();
        }
    }
    return sum;
}

LgsExpr* LgsObject::getZeroValue() {
    return new LgsInstance(clone());
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

Lgs_rttype LgsObject::getRTType() {
    return RTT_OBJECT;
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
            newField->expr = field->expr->clone();
        }
        cloned->addField(newField);
    }
    cloned->methods.clear();
    for (const auto& [_, method] : methods) {
        const auto newField = new LgsFunc(*method);
        cloned->addMethod(newField);
    }
    return cloned;
}

std::string LgsObject::getName() {
    return name;
}

bool LgsObject::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    auto otherType = other;
    if (const auto nullable = other->asNullable()) {
        otherType = nullable->baseType;
    }
    if (const auto otherInterface = otherType->asInterface()) {
        for (const auto objInterface : implements) {
            if (objInterface->getName() == otherInterface->name) {
                return true;
            }
        }
        return false;
    }
    return name == otherType->getName();
}

void LgsObject::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "name", name, true);

    openJsonKeyArray(json, "fields");
    bool first = true;
    for (const auto field : fields) {
        if (!first) json << ',';
        first = false;
        field->parseAsJSON(json);
    }
    closeJsonArray(json, true);

    openJsonKeyArray(json, "methods");
    first = true;
    for (const auto& [funcName, methods] : methods) {
        if (!first) json << ',';
        first = false;
        methods->parseAsJSON(json);
    }
    closeJsonArray(json);

    closeJsonObject(json);
}

LgsObject::~LgsObject() {
    for (const auto interface : implements) {
        freeType(interface);
    }
    implements.clear();
    for (const auto enum_ : enums) {
        freeType(enum_);
    }
    enums.clear();
    for (const auto subtype : subtypes) {
        freeType(subtype);
    }
    subtypes.clear();
    for (const auto object : objects) {
        freeType(object);
    }
    objects.clear();
}

