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
#include "LgsConfigs.h"

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

Type* LgsObject::getIRType(LgsCodeGen& cg) {
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

Constant* LgsObject::getRTType(LgsCodeGen& cg) {
    const auto RTTName = LGS_TYPEINFO_PREFIX + name;
    if (const auto v = cg.IRModule->getGlobalVariable(RTTName)) return v;
    if (cg.mode != CG_MODE_RTTYPES) return cg.createGlobal(RTTName, cg.getRTTStruct(), nullptr);
    const auto numFields = fields.size();
    constexpr auto RTTFieldName = std::string(LGS_TYPEINFO_PREFIX) + "field";
    const auto objRTType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, RTTName);
    const auto fieldRTType = cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.sizeTy(), cg.i32Ty()}, RTTFieldName);
    const auto fieldTypeArr = ArrayType::get(fieldRTType, numFields);
    const auto sl = cg.IRModule->getDataLayout().getStructLayout(llvm::cast<StructType>(getIRType(cg)));

    std::vector<Constant*> rttFields;
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        assert(field->type->rtt != RTT_UNKNOWN);
        rttFields.emplace_back(ConstantStruct::get(fieldRTType, {
            cg.getString(field->name),
            field->type->IRSize(cg),
            cg.usize(sl->getElementOffset(i + 2)),
            cg.i32(field->type->rtt),
            field->type->asObject() ? cg.null() : field->type->getRTType(cg),
        }));
    }

    const auto rttFieldsGlobal = cg.createGlobal(LGS_TYPEINFO_PREFIX + name + "_fields", fieldTypeArr, ConstantArray::get(fieldTypeArr, rttFields));
    const auto rttFuncsGlobal = cg.null();
    const std::vector<Constant*> args = {
        cg.getString(name), // name
        IRSize(cg), // size
        cg.usize(numFields), // fieldsCount
        cg.usize(methods.size()),  // funcsCount
        rttFieldsGlobal, // fields
        rttFuncsGlobal, // funcs
    };
    return cg.createGlobal(RTTName, objRTType, ConstantStruct::get(objRTType, args));
}

size_t LgsObject::sizeBytes() {
    auto sum = LGS_OBJ_MD_SIZE;
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

DIType* LgsObject::getDebugType(LgsCodeGen& cg) {
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
