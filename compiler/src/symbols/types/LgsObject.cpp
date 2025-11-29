#include "types/LgsObject.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIOPair.h"
#include "types/LgsSubType.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "LgsUtils.h"
#include "types/LgsAny.h"

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
    IRType = StructType::create(cg.context, elementTypes, name);
    cg.typesRegistry[name] = IRType;
    return IRType;
}

Constant* LgsObject::getRTType(LgsCgModule& cg) {
    std::vector<Constant*> fieldRTTs;
    std::vector<Constant*> fieldNameHashes;
    fieldRTTs.reserve(fields.size());
    fieldNameHashes.reserve(fields.size());
    for (const auto field : fields) {
        fieldRTTs.push_back(field->type->getRTType(cg));
        fieldNameHashes.push_back(cg.hashConst(field->name));
    }

    const auto genericName = getGenericName();
    const auto fieldsArrType = ArrayType::get(cg.getRTBaseType(), fields.size());
    Constant* fieldsArr = cg.null();
    Constant* hashesArr = cg.null();
    if (!fields.empty()) {
        const auto fieldsName = LGS_TYPEINFO_PREFIX + genericName + "_fields";
        if (cg.isRTTModule) {
            const auto args = llvm::ConstantArray::get(fieldsArrType, fieldRTTs);
            fieldsArr = cg.createGlobal(fieldsName, fieldsArrType, args);
        } else {
            fieldsArr = cg.createGlobal(fieldsName, fieldsArrType, nullptr);
        }

        const auto hashesArrType = ArrayType::get(cg.i64Ty(), fields.size());
        const auto hashesName = LGS_TYPEINFO_PREFIX + genericName + "_hashes";
        if (cg.isRTTModule) {
            const auto hashes = llvm::ConstantArray::get(hashesArrType, fieldNameHashes);
            hashesArr = cg.createGlobal(hashesName, hashesArrType, hashes);
        } else {
            hashesArr = cg.createGlobal(hashesName, hashesArrType, nullptr);
        }
    }
    const auto st = cg.getStructType({cg.sizeTy(), cg.ptrTy(), cg.ptrTy()}, LGS_TYPEINFO_PREFIX + genericName);
    const auto sv = llvm::ConstantStruct::get(st, {cg.usize(fields.size()), hashesArr, fieldsArr});
    return cg.getRTTypeInfo(genericName, sizeBytes(), sizeof(void*), RTT_OBJECT, sv);
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

llvm::DIType* LgsObject::getDebugType(LgsCgModule& cg) {
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

