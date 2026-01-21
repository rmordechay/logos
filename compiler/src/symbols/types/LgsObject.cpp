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

#include <ranges>
#include <sstream>
#include <unordered_set>
#include <llvm/IR/Module.h>

#include "LgsConfigs.h"

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
    std::vector<Type*> types = {cg.sizeTy()}; // First field is level
    types.reserve(fields.size());
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        types.emplace_back(field->type->getTypeOrPtr(cg));
    }
    const auto IRType = StructType::create(cg.context, types, name);
    cg.typesRegistry[name] = IRType;
    return IRType;
}

Constant* LgsObject::getRTType(LgsCgModule& cg) {
    const auto RTTName = LGS_TYPEINFO_PREFIX + name;
    if (const auto v = cg.IRModule->getGlobalVariable(RTTName)) return v;
    if (cg.mode != CG_MODE_RTTYPES) return cg.createGlobal(RTTName, cg.getRTTBaseStruct(), nullptr);
    const auto rttType = cg.createGlobal(RTTName, cg.getRTTBaseStruct(), nullptr);
    const auto numFields = fields.size();
    const auto ptrTypeArr = ArrayType::get(cg.ptrTy(), numFields);

    std::vector<Constant*> fieldNames;
    std::vector<Constant*> fieldTypes;
    for (const auto field : fields) {
        fieldNames.push_back(cg.getString(field->name));
        fieldTypes.push_back(field->type->getRTType(cg));
    }

    const auto namesArr = ConstantArray::get(ptrTypeArr, fieldNames);
    const auto namesArrGlobal = cg.createGlobal(RTTName + "_names", ptrTypeArr, namesArr);
    const auto typesArr = ConstantArray::get(ptrTypeArr, fieldTypes);
    const auto typesArrGlobal = cg.createGlobal(RTTName + "_types", ptrTypeArr, typesArr);

    const std::vector<Constant*> args = {cg.getString(RTTName), cg.usize(numFields), namesArrGlobal, typesArrGlobal};
    const std::vector<Type*> types = {cg.ptrTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy()};
    const auto sv = cg.getRTTExtraStruct(name, types, args);
    const std::vector<Constant*> rttFields = {cg.usize(IRSize(cg)), cg.i1(isHeapAlloc), cg.i32(RTT_OBJECT), sv};
    rttType->setInitializer(ConstantStruct::get(cg.getRTTBaseStruct(), rttFields));
    return rttType;
}

size_t LgsObject::sizeBytes() {
    auto sum = LEVEL_SIZE;
    for (const auto& field : fields) {
        if (field->type->asObject() || field->type->asFuncType() || field->type->asInterface()) {
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
    if (other->isAny()) return true;
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
}
