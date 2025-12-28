#include "types/LgsObject.h"

#include "LgsDefinitions.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsSubType.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "LgsUtils.h"
#include "types/LgsAny.h"

#include <ranges>
#include <sstream>
#include <llvm/IR/Module.h>

std::string LgsObject::getName() {
    return name;
}

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

Type* LgsObject::getIRType(LgsCgModule& cg) {
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
    const auto IRType = StructType::create(cg.context, elementTypes, name);
    cg.typesRegistry[name] = IRType;
    return IRType;
}

Constant* LgsObject::getRTType(LgsCgModule& cg) {
    const auto objName = getName();
    std::vector<LgsOwner*> fieldsAsOwners;
    for (const auto field : fields) fieldsAsOwners.push_back(field);
    const auto [typesArr, hashesArr] = getRTFieldsInfo(cg, name, fieldsAsOwners);
    // name, fieldsCount, fieldNames, fieldTypes
    const std::vector<Type*> params = {cg.ptrTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Constant*> args = {cg.getString(objName), cg.usize(fields.size()), hashesArr, typesArr};
    const auto sv = cg.getRTTExtraStruct(objName, params, args);
    return cg.getRTTypeInfo(objName, sizeBytes(), RTT_OBJECT, sv);
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
    return new LgsInstance(this);
}

Value* LgsObject::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto zero = cg.heapAllocate(cg.usize(sizeBytes()), getRTType(cg));
    for (const auto field : fields) {
        const auto fieldZero = field->type->getIRZeroValue(cg);
        cg.storeStructField(ty, zero, field->position, fieldZero);
    }
    return zero;
}

bool LgsObject::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherType = other;
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

LgsType* LgsObject::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

std::string LgsObject::fmtStr() const {
    std::stringstream str;
    str << '{';
    bool first = true;
    for (const auto& field : fields) {
        if (!first) str << ", ";
        str << field->name << " = " << field->type->fmtStr();
        first = false;
    }
    str << '}';
    return str.str();
}

DIType* LgsObject::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsObject::~LgsObject() {
    freeTypes(enums);
    freeTypes(objects);
    // freeTypes(generics);
    freeTypes(subtypes);
    if (singleton) {
        singleton->setType(nullptr);
        singleton->obj = nullptr;
        freeExpr(singleton);
    }
    for (const auto ioPair : ioPairs) {
        delete ioPair;
    }
    delete getFieldFunc;
    getFieldFunc = nullptr;
}

