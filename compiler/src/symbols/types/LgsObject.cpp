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
#include <unordered_set>
#include <llvm/IR/Module.h>
#include "LgsBinaryTokens.h"
#include "LgsRTTIndices.h"
#include "codegen/LgsCgFile.h"
#include "errors/LgsErrors.h"
#include "types/LgsFieldType.h"
#include "types/iterables/LgsVariadic.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsSize.h"

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
    if (methodName == OBJ_HASH_FUNC) {
        const auto func = new LgsFunc(methodName, &LGS_SIZE);
        func->fn = [&](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            return hashValue(cg, args[0].expr->IRValue);
        };
        metaFuncs[methodName] = func;
        return func;
    }
    if (methodName == OBJ_GET_METHOD_FUNC) {
        LgsParam param(new LgsVariadic(&LGS_ANY));
        param.isVariadic = true;
        const auto rt = new LgsFuncType("", &LGS_ANY, {param}, VARIADIC);
        const auto func = new LgsFunc(methodName, rt, {new LgsStr()});
        func->fn = [](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto objArg = args[0].expr;
            const auto methodNameArg = args[1].expr;
            const auto funcName = methodNameArg->type->asStr()->loadRTData(cg, methodNameArg->IRValue);
            const auto objType = loadRTTInfoExtra(cg, objArg->type->getRTType(cg));
            return cg.getVFunc(objType, funcName);
        };
        metaFuncs[methodName] = func;
        return func;
    }
    if (methodName == OBJ_GET_FIELD_FUNC) {
        const auto func = new LgsFunc(methodName, new LgsFieldType(), {new LgsStr()});
        func->fn = [&](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto self = args[0].expr;
            const auto fieldNameStr = args[1].expr;
            const auto fieldName = fieldNameStr->type->asStr()->loadRTData(cg, fieldNameStr->IRValue);
            return cg.builder.CreateCall(getGetFieldFunc(cg), {self->IRValue, fieldName});
        };
        metaFuncs[methodName] = func;
        return func;
    }
    if (methodName == OBJ_SET_FIELD_FUNC) {
        const auto func = new LgsFunc(methodName, &LGS_BOOL, {new LgsStr(), &LGS_ANY});
        func->fn = [&](LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto self = args[0].expr;
            const auto fieldNameStr = args[1].expr;
            const auto value = args[2].expr;
            const auto fieldName = fieldNameStr->type->asStr()->loadRTData(cg, fieldNameStr->IRValue);
            const auto ty = value->IRValue->getType();
            const auto v = ty->isPointerTy() ? value->IRValue : cg.allocaAndStore(ty, value->IRValue);
            return cg.builder.CreateCall(getSetFieldFunc(cg), {
                                         self->IRValue, fieldName, v, value->type->getRTType(cg)
                                         });
        };
        metaFuncs[methodName] = func;
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
        types.emplace_back(field->type->getIRTypeOrPtr(cg));
    }
    const auto IRType = StructType::create(cg.context, types, name);
    cg.typesRegistry[name] = IRType;
    return IRType;
}

Constant* LgsObject::getRTTypeExtra(LgsCodeGen& cg) {
    const auto rttName = getRTTName();
    const auto numFields = fields.size();
    const auto numMethods = methods.size();
    const auto ty = llvm::cast<StructType>(getIRType(cg));
    const auto sl = cg.IRModule->getDataLayout().getStructLayout(ty);

    const auto objRTType = getObjRTTStruct(cg);
    const auto fieldRTType = LgsFieldType::getFieldRTTStruct(cg);
    const auto methodRTType = getMethodRTTStruct(cg);
    const auto fieldTypeArr = ArrayType::get(fieldRTType, numFields);
    const auto methodsTypeArr = ArrayType::get(methodRTType, numMethods);

    std::vector<Constant*> rttFields;
    for (size_t i = 0; i < fields.size(); ++i) {
        const auto field = fields[i];
        assert(field->type->rttKind != RTT_UNKNOWN);
        const auto fieldName = cg.getString(field->name);
        rttFields.emplace_back(ConstantStruct::get(fieldRTType, {
            fieldName,
            field->type->IRSize(cg),
            cg.usize(sl->getElementOffset(i + 2)), // offset level and type
            cg.i32(field->type->rttKind),
            field->type->asObject() ? cg.null() : field->type->getRTType(cg),
        }));
    }

    std::vector<Constant*> rttMethods;
    for (auto& [_, method] : methods) {
        if (method->funcType->isVirtual) continue;
        const std::vector<Constant*> args = {cg.getString(method->funcType->name), method->getIRFunc(cg)};
        rttMethods.emplace_back(ConstantStruct::get(methodRTType, args));
    }

    const auto initializerFields = ConstantArray::get(fieldTypeArr, rttFields);
    const auto initializerMethods = ConstantArray::get(methodsTypeArr, rttMethods);
    const auto rttFieldsGlobal = cg.createGlobal(rttName + "_fields", fieldTypeArr, initializerFields);
    const auto rttMethodsGlobal = cg.createGlobal(rttName + "_funcs", methodsTypeArr, initializerMethods);
    const auto objName = cg.getString(name);
    objName->setName(rttName + "_name");
    return cg.createGlobal(rttName + "_extra", objRTType, ConstantStruct::get(objRTType, {
        cg.usize(id),
        objName,
        IRSize(cg),
        cg.usize(numFields),
        cg.usize(numMethods),
        rttFieldsGlobal,
        rttMethodsGlobal,
    }));
}

size_t LgsObject::sizeBytes() {
    auto sum = LGS_OBJ_MD_SIZE;
    for (const auto& field : fields) {
        if (field->type->asObject() || field->type->asFuncType() || field->type->asInterface()) {
            sum += sizeof(void*);
        }
        else {
            sum += field->type->sizeBytes();
        }
    }
    return sum;
}

LgsExpr* LgsObject::getZeroValue() {
    const auto instance = new LgsInstance(this);
    cloneFields(instance);
    return instance;
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

Value* LgsObject::hashValue(LgsCodeGen& cg, Value* value) {
    return cg.builder.CreateCall(getObjsHashFunc(cg), {value});
}

void LgsObject::hashNode(size_t& oldHash) {
    assert(0);
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

void LgsObject::cloneFields(LgsInstance* instance) const {
    for (const auto field : fields) {
        auto newField = new LgsField(*field);
        if (newField->expr) {
            newField->expr = newField->expr->clone();
        }
        instance->fields.emplace_back(newField);
    }
}

DIType* LgsObject::getDebugType(LgsCodeGen& cg) {
    assert(0);
}

Function* LgsObject::getObjsEqFunc(LgsCodeGen& cg) const {
    const auto funcName = LGS_PREFIX + name + "_" + EQUAL_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);

    const auto func = cg.getFunc(funcName, ft);
    cg.savedIP = cg.builder.saveIP();
    const auto obj1 = func->getArg(0);
    const auto obj2 = func->getArg(1);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    for (const auto field : fields) {
        const auto ty = field->type->getIRTypeOrPtr(cg);
        const auto gep1 = field->getGEP(cg, obj1);
        const auto gep2 = field->getGEP(cg, obj2);
        const auto ne = neIR(cg, cg.load(ty, gep1), cg.load(ty, gep2), field->type);
        cg.ifStmt(ne, [&cg] {
            cg.builder.CreateRet(cg.false_());
        });
    }

    cg.builder.CreateRet(cg.true_());
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Function* LgsObject::getObjsHashFunc(LgsCodeGen& cg) const {
    const auto funcName = LGS_PREFIX + name + "_" + OBJ_HASH_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.sizeTy(), {cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);

    const auto func = cg.getFunc(funcName, ft);
    cg.savedIP = cg.builder.saveIP();
    const auto instance = func->getArg(0);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    Value* hash = cg.usize(0);
    for (const auto field : fields) {
        const auto gep = field->getGEP(cg, instance);
        const auto v = cg.load(field->type->getIRTypeOrPtr(cg), gep);
        const auto fieldHash = field->type->hashValue(cg, v);
        hash = cg.builder.CreateXor(hash, fieldHash);
        hash = cg.builder.CreateMul(hash, cg.usize(31));
    }

    cg.builder.CreateRet(hash);
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Function* LgsObject::getSetFieldFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + metaName + "_" + OBJ_SET_FIELD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.i1Ty(), {cg.ptrTy(), cg.ptrTy(), cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);

    const auto func = cg.getFunc(funcName, ft);
    cg.savedIP = cg.builder.saveIP();
    const auto self = func->getArg(0);
    const auto fieldNameArg = func->getArg(1);
    const auto value = func->getArg(2);
    const auto valueTy = func->getArg(3);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    const auto fieldTy = cg.builder.CreateCall(getGetFieldFunc(cg), {self, fieldNameArg});
    cg.ifStmt(cg.isNull(fieldTy), [&cg] { cg.builder.CreateRet(cg.false_()); });
    const auto fieldKind1 = LgsFieldType::loadRTKind(cg, fieldTy);
    const auto fieldKind2 = loadRTTInfoKind(cg, valueTy);
    const auto canCast = cg.callRuntimeFunc("canCast", cg.i1Ty(), {cg.i32Ty(), cg.i32Ty()}, {fieldKind1, fieldKind2});
    cg.ifStmt(cg.builder.CreateNot(canCast), [&] {
        auto fieldTypeName1 = loadRTTInfoName(cg, LgsFieldType::loadRTType(cg, fieldTy));
        auto fieldTypeName2 = loadRTTInfoName(cg, valueTy);
        cg.throwError(E10018, {fieldTypeName2, fieldTypeName1});
    });

    const auto offset = LgsFieldType::loadRTOffset(cg, fieldTy);
    const auto fieldSize = LgsFieldType::loadRTSize(cg, fieldTy);
    const auto fieldPtr = cg.builder.CreatePtrAdd(self, offset);
    cg.callMemcpy(fieldPtr, value, fieldSize);

    cg.builder.CreateRet(cg.true_());
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Function* LgsObject::getGetFieldFunc(LgsCodeGen& cg) {
    const auto funcName = LGS_PREFIX + metaName + "_" + OBJ_GET_FIELD_FUNC;
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);

    const auto func = cg.getFunc(funcName, ft);
    cg.savedIP = cg.builder.saveIP();
    const auto self = func->getArg(0);
    const auto arg = func->getArg(1);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);

    const auto fieldRTTStruct = LgsFieldType::getFieldRTTStruct(cg);
    const auto instanceType = loadRTTInfoExtra(cg, getInstanceRTType(cg, self));
    const auto fieldTypesPtr = loadRTFields(cg, instanceType);
    const auto fieldsCount = loadRTFieldsCount(cg, instanceType);

    cg.loop(fieldsCount, [&](Value* iValue, BasicBlock*) {
        const auto fieldTypePtr = cg.builder.CreateInBoundsGEP(fieldRTTStruct, fieldTypesPtr, {iValue});
        const auto fieldName = LgsFieldType::loadRTName(cg, fieldTypePtr);
        cg.ifStmt(eqIR(cg, fieldName, arg, &LGS_STR), [&cg, &fieldTypePtr] {
            cg.builder.CreateRet(fieldTypePtr);
        });
    });

    cg.builder.CreateRet(cg.null());
    cg.builder.restoreIP(cg.savedIP);
    return func;
}

Value* LgsObject::getInstanceRTType(LgsCodeGen& cg, Value* instance) {
    return cg.loadPtr(cg.builder.CreatePtrAdd(instance, cg.getTypeSize(cg.sizeTy())));
}

StructType* LgsObject::getObjRTTStruct(LgsCodeGen& cg) {
    const auto rttName = LGS_TYPEINFO_PREFIX + metaName;
    return cg.getStructType({cg.sizeTy(), cg.ptrTy(), cg.sizeTy(), cg.sizeTy(), cg.sizeTy(), cg.ptrTy(), cg.ptrTy()},
                            rttName);
}

StructType* LgsObject::getMethodRTTStruct(LgsCodeGen& cg) {
    constexpr auto rttName = std::string(LGS_TYPEINFO_PREFIX) + "method";
    return cg.getStructType({cg.ptrTy(), cg.ptrTy()}, rttName);
}

Value* LgsObject::loadRTFieldsCount(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getObjRTTStruct(cg), ptr, LgsObjIndices::fieldsCount, cg.sizeTy());
}

Value* LgsObject::loadRTFields(LgsCodeGen& cg, Value* ptr) {
    return cg.loadStructField(getObjRTTStruct(cg), ptr, LgsObjIndices::fields, cg.ptrTy());
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
