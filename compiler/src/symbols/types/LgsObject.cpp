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
#include <unordered_set>
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
    std::vector<Type*> elementTypes = {cg.sizeTy()}; // First field is level
    elementTypes.reserve(fields.size());
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        const auto fieldType = field->type->getTypeOrPtr(cg);
        elementTypes.push_back(fieldType);
    }
    const auto IRType = StructType::create(cg.context, elementTypes, name);
    cg.typesRegistry[name] = IRType;
    return IRType;
}

Constant* LgsObject::getRTType(LgsCgModule& cg) {
    // TODO think about recursive fields in rtt types
    std::unordered_set<std::string> nestedObjectNames;
    checkRecursiveFields(nestedObjectNames);
    const auto objName = getName();
    std::vector<LgsValue*> fieldsAsValue;
    const auto dl = cg.IRModule->getDataLayout();
    const auto sl = dl.getStructLayout(llvm::cast<StructType>(getIRType(cg)));
    std::vector<Constant*> offsets;
    offsets.reserve(fields.size());
    const auto offsetsName = LGS_TYPEINFO_PREFIX + name + "_offsets";
    const auto offsetsArrType = ArrayType::get(cg.sizeTy(), fields.size());
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        offsets.emplace_back(cg.usize(sl->getElementOffset(i + 1))); // level is first element
        fieldsAsValue.push_back(field);
    }
    const auto [typesArr, hashesArr] = getRTValuesInfo(cg, name, fieldsAsValue);
    Constant* offsetsArr = nullptr;
    if (cg.mode == CG_MODE_RTTYPES) {
        offsetsArr = ConstantArray::get(offsetsArrType, offsets);
    }
    const auto offsetsArrGlobal = cg.createGlobal(offsetsName, offsetsArrType, offsetsArr);

    // name, fieldsCount, fieldOffsets, fieldNames, fieldTypes
    const std::vector<Type*> fieldTypes = {cg.ptrTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()};
    const auto objNameIR = llvm::dyn_cast<Constant>(cg.getString(objName));
    const std::vector<Constant*> args = {objNameIR, cg.usize(fields.size()), offsetsArrGlobal, hashesArr, typesArr};
    const auto sv = cg.getRTTExtraStruct(objName, fieldTypes, args);
    return cg.getRTTypeInfo(objName, dl.getTypeAllocSize(getIRType(cg)), RTT_OBJECT, sv, true);
}

size_t LgsObject::sizeBytes() {
    auto sum = sizeof(size_t); // level
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

Value* LgsObject::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    const auto ty = getIRType(cg);
    const auto zero = cg.heapAlloc(cg.usize(sizeBytes()));
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

void LgsObject::checkRecursiveFields(std::unordered_set<std::string>& nestedObjectNames) const {
    for (const auto field : fields) {
        if (const auto innerObj = field->type->asObject()) {
            assert(!nestedObjectNames.contains(innerObj->name));
            nestedObjectNames.insert(innerObj->name);
            innerObj->checkRecursiveFields(nestedObjectNames);
        }
    }
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

