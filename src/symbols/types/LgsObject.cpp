#include "types/LgsObject.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsSubType.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "types/LgsGenericParam.h"
#include "utils/LgsUtils.h"
#include <sstream>
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

std::string LgsObject::getName() {
    return name;
}

Type* LgsObject::getIRType(LgsLLVMGen& cg) {
    const auto type = cg.typesRegistry.find(name);
    if (type != cg.typesRegistry.end()) return type->second;
    std::vector<Type*> elementTypes;
    elementTypes.reserve(fields.size());
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
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
    cg.typesRegistry[name] = IRType;
    return IRType;
}

size_t LgsObject::sizeBytes() {
    size_t sum = 0;
    for (const auto& field : fields) {
        if (field->type->asObject() || field->type->asFuncType() || field->type->asInterface() || field->type->asDArray()) {
            sum += sizeof(void*);
        } else {
            sum += field->type->sizeBytes();
        }
    }
    return sum;
}

LgsExpr* LgsObject::getZeroValue() {
    return new LgsInstance(clone());
}

Lgs_TypeKind LgsObject::getRTTypeKind() {
    return RTT_OBJECT;
}

Constant* LgsObject::getRTType(LgsLLVMGen& cg) {
    const auto objRTStruct = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.ptrTy()}, LGS_RT_OBJECT);
    const auto fieldCount = fields.size();
    std::vector<Constant*> fieldTypeValues;
    for (const auto field : fields) {
        fieldTypeValues.push_back(cg.i32(field->type->getRTTypeKind()));
    }
    const auto fieldTypesArrayType = ArrayType::get(cg.i32Ty(), fieldCount);
    const auto fieldTypesArray = llvm::ConstantArray::get(fieldTypesArrayType, fieldTypeValues);
    const auto fieldTypesGlobal = cg.createGlobal(fieldTypesArrayType, fieldTypesArray, name + "_field_types");
    const std::vector<Constant*> structFields = {
        cg.getIRStr(name), cg.usize(fieldCount), fieldTypesGlobal
    };
    return llvm::ConstantStruct::get(objRTStruct, structFields);
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

LgsObject* LgsObject::clone() {
    assert(!singleton);
    const auto newObj = new LgsObject(*this);
    newObj->fields.clear();
    newObj->generics.clear();
    for (const auto& generic : generics) {
        newObj->generics.emplace_back(new LgsGenericParam(*generic));
    }
    for (const auto& enum_ : enums) {
        newObj->enums.emplace_back(new LgsEnum(*enum_));
    }
    cloneFields(newObj);
    cloneMethods(newObj);
    return newObj;
}

LgsObject::~LgsObject() {
    freeTypes(enums);
    freeTypes(objects);
    freeTypes(generics);
    freeTypes(subtypes);
    if (singleton) {
        singleton->setType(nullptr);
        singleton->obj = nullptr;
        freeExpr(singleton);
    }
    for (const auto ioPair : ioPairs) {
        delete ioPair;
    }
}

