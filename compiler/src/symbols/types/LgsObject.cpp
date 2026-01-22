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
    std::vector<Type*> types = {cg.sizeTy(), cg.ptrTy()}; // First field is level
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
    if (cg.mode != CG_MODE_RTTYPES) return cg.createGlobal(RTTName, cg.getRTTStructType(), nullptr);
    const auto numFields = fields.size();
    const auto ptrTypeArr = ArrayType::get(cg.ptrTy(), numFields);
    const auto sizeTypeArr = ArrayType::get(cg.sizeTy(), numFields);
    const auto intTypeArr = ArrayType::get(cg.i32Ty(), numFields);
    const auto objRTType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, RTTName);
    const auto sl = cg.IRModule->getDataLayout().getStructLayout(llvm::cast<StructType>(getIRType(cg)));

    std::vector<Constant*> fieldNames;
    std::vector<Constant*> fieldSizes;
    std::vector<Constant*> fieldOffsets;
    std::vector<Constant*> fieldKinds;
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        fieldNames.push_back(cg.getString(field->name));
        fieldSizes.push_back(field->type->IRSize(cg));
        fieldOffsets.push_back(cg.usize(sl->getElementOffset(i + 2)));
        assert(field->type->rtt);
        fieldKinds.push_back(cg.i32(field->type->rtt));
    }
    const auto namesArrGlobal = cg.createGlobal(RTTName + "_names", ptrTypeArr, ConstantArray::get(ptrTypeArr, fieldNames));
    const auto sizesArrGlobal = cg.createGlobal(RTTName + "_sizes", sizeTypeArr, ConstantArray::get(sizeTypeArr, fieldSizes));
    const auto offsetsArrGlobal = cg.createGlobal(RTTName + "_offsets", sizeTypeArr, ConstantArray::get(sizeTypeArr, fieldOffsets));
    const auto kindsArrGlobal = cg.createGlobal(RTTName + "_kinds", intTypeArr, ConstantArray::get(intTypeArr, fieldKinds));
    const std::vector<Constant*> args = {
        cg.getString(name), IRSize(cg), cg.usize(numFields), namesArrGlobal, sizesArrGlobal, offsetsArrGlobal, kindsArrGlobal
    };
    return cg.createGlobal(RTTName, objRTType, ConstantStruct::get(objRTType, args));
}

size_t LgsObject::sizeBytes() {
    auto sum = OBJ_MD_SIZE;
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
        str << field->name << " = " << (field->type->asObject() ? "%s" : field->type->fmtStr());
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
