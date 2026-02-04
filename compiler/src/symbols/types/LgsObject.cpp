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

#include "LgsBinaryTokens.h"
#include "errors/LgsErrors.h"
#include "types/primitives/LgsBool.h"

std::string LgsObject::getName() {
    return name;
}

std::string LgsObject::getBaseName() {
    return metaName;
}

LgsFunc* LgsObject::getMethod(const std::string& methodName) {
    if (methods.contains(methodName)) return methods[methodName];
    for (const auto* f : fields) {
        if (f->name != methodName) continue;
        if (f->expr && f->expr->asFunc()) return f->expr->asFunc();
    }
    for (const auto interface : implements) {
        const auto interfaceMethod = interface->getMethod(methodName);
        if (interfaceMethod) return interfaceMethod;
    }
    return nullptr;
}

LgsFunc* LgsObject::getMetaFunc(const std::string& methodName) {
    if (methods.contains(methodName)) return methods[methodName];
    if (methodName == OBJ_GET_METHOD) {
        // TODO figure out how to pass rt and params correctly
        const auto rt = new LgsFuncType("", &LGS_STR, {});
        const auto func = new LgsFunc(methodName, rt, {new LgsStr()});
        metaFuncs[methodName] = func;
        metaFuncs[methodName]->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto objRTT = args[0].expr->type->getRTType(cg);
            const auto arg = args[1].expr;
            const auto funcName = arg->type->asStr()->loadStrPtr(cg, arg->IRValue);
            const auto vfunc = cg.getVFunc(objRTT, funcName);
            cg.ifStmt(cg.builder.CreateIsNull(vfunc), [funcName, &cg] {cg.throwError(E10006, {funcName});});
            return vfunc;
        };
        return func;
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

Constant* LgsObject::getRTTypeExtra(LgsCodeGen& cg) {
    const auto rttName = getRTTName();
    const auto numFields = fields.size();
    const auto numMethods = methods.size();
    const auto sl = cg.IRModule->getDataLayout().getStructLayout(llvm::cast<StructType>(getIRType(cg)));

    const auto objRTType = getObjRTT(cg);
    const auto fieldRTType = getFieldRTT(cg);
    const auto methodRTType = getMethodRTT(cg);
    const auto fieldTypeArr = ArrayType::get(fieldRTType, numFields);
    const auto methodsTypeArr = ArrayType::get(methodRTType, numMethods);

    std::vector<Constant*> rttFields;
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        assert(field->type->rttKind != RTT_UNKNOWN);
        const auto fieldName = cg.getString(field->name);
        fieldName->setName(std::format("{}_field{}_name", rttName, std::to_string(i)));
        rttFields.emplace_back(ConstantStruct::get(fieldRTType, {
            fieldName,
            field->type->IRSize(cg),
            cg.usize(sl->getElementOffset(i + 2)), // offset (1) level and (2) type
            cg.i32(field->type->rttKind),
            field->type->asObject() ? cg.null() : field->type->getRTType(cg),
        }));
    }

    std::vector<Constant*> rttMethods;
    for (auto& [_, method] : methods) {
        rttMethods.emplace_back(ConstantStruct::get(methodRTType, {
            cg.getString(method->funcType->name),
            method->getIRFunc(cg),
        }));
    }

    const auto rttFieldsGlobal = cg.createGlobal(rttName + "_fields", fieldTypeArr, ConstantArray::get(fieldTypeArr, rttFields));
    const auto rttMethodsGlobal = cg.createGlobal(rttName + "_funcs", methodsTypeArr, ConstantArray::get(methodsTypeArr, rttMethods));
    const auto objName = cg.getString(name);
    objName->setName(rttName + "_name");
    const std::vector<Constant*> args = {
        cg.usize(id),
        objName,
        IRSize(cg),
        cg.usize(numFields),
        cg.usize(numMethods),
        rttFieldsGlobal,
        rttMethodsGlobal,
    };
    return cg.createGlobal(rttName + "_extra", objRTType, ConstantStruct::get(objRTType, args));
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

Value* LgsObject::getIRZeroValue(LgsCodeGen& cg, Value* pointee) {
    return cg.callRuntimeFunc("allocObject", cg.ptrTy(), {cg.ptrTy()}, {getRTType(cg)});
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

Value* LgsObject::objsEqual(LgsCodeGen& cg, Value* left, Value* right) {
    return cg.builder.CreateCall(generateObjsEqFunc(cg), {left, right});
}

LgsType* LgsObject::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    if (op.opType != EQ && op.opType != NE) return nullptr;
    return canCastTo(rightType) ? &LGS_BOOL : nullptr;
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

Function* LgsObject::generateObjsEqFunc(LgsCodeGen& cg) const {
    const auto funcName = LGS_PREFIX + name + "_" + EQUAL_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);
    const auto func = cg.getFunc(funcName, ft);
    const auto obj1 = func->getArg(0);
    const auto obj2 = func->getArg(1);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    for (const auto field : fields) {
        const auto gep1 = field->getGEP(cg, obj1);
        const auto gep2 = field->getGEP(cg, obj2);
        const auto v1 = cg.load(field->type->getTypeOrPtr(cg), gep1);
        const auto v2 = cg.load(field->type->getTypeOrPtr(cg), gep2);
        const auto eq = neIR(cg, v1, v2, field->type);
        cg.ifStmt(eq, [&cg]{cg.builder.CreateRet(cg.false_());});
    }
    cg.builder.CreateRet(cg.true_());
    return func;
}

StructType* LgsObject::getObjRTT(LgsCodeGen& cg) {
    const auto rttName = LGS_TYPEINFO_PREFIX + metaName;
    return cg.getStructType({cg.sizeTy(), cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()}, rttName);
}

StructType* LgsObject::getFieldRTT(LgsCodeGen& cg) {
    constexpr auto rttName = std::string(LGS_TYPEINFO_PREFIX) + "field";
    return cg.getStructType({cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.sizeTy(), cg.i32Ty()}, rttName);
}

StructType* LgsObject::getMethodRTT(LgsCodeGen& cg) {
    constexpr auto rttName = std::string(LGS_TYPEINFO_PREFIX) + "method";
    return cg.getStructType({cg.ptrTy(), cg.ptrTy()}, rttName);
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
