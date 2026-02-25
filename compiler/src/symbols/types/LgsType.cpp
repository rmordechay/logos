#include <llvm/ADT/ArrayRef.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <stdint.h>
#include <unordered_set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "LgsRTTIndices.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/primitives/LgsAny.h"
#include "types/LgsCPtr.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsEnum.h"
#include "types/LgsEnumField.h"
#include "types/LgsFieldType.h"
#include "types/LgsTypeParam.h"
#include "types/LgsNullable.h"
#include "types/LgsSelf.h"
#include "types/iterables/LgsMap.h"
#include "types/LgsSubType.h"
#include "types/LgsUnknown.h"
#include "types/iterables/LgsMatrix.h"
#include "types/primitives/LgsVoid.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsSet.h"
#include "types/iterables/LgsVariadic.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"
#include "types/primitives/LgsULong.h"
#include "LgsDefinitions.h"
#include "LgsType.h"
#include "Lgs_Types.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsFuncType.h"
#include "types/LgsTypePair.h"
#include "types/iterables/LgsIterable.h"
#include "types/iterables/LgsStr.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsFloat.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsUByte.h"
#include "types/primitives/LgsUShort.h"

class LgsBinaryExpr;
namespace llvm {
class BasicBlock;
class Constant;
}

static std::unordered_map<std::string, uint8_t> numberPrecedences = {
    {LgsBool::name, 1},
    {LgsByte::name, 2},
    {LgsUByte::name, 3},
    {LgsShort::name, 4},
    {LgsUShort::name, 5},
    {LgsChar::name, 6},
    {LgsInt::name, 7},
    {LgsUInt::name, 8},
    {LgsLong::name, 9},
    {LgsULong::name, 10},
    {LgsSize::name, 11},
    {LgsFloat::name, 12},
    {LgsDouble::name, 13},
};

bool LgsType::isAny() {
    return asAny() || (asCPtr() && asCPtr()->baseType->isVoid());
}

bool LgsType::isVoid() {
    return dynamic_cast<LgsVoid*>(this);
}

bool LgsType::isScalar() const {
    return isInt || isFloat;
}

bool LgsType::isUnknown() {
    if (dynamic_cast<LgsUnknown*>(this)) return true;
    if (const auto iter = asIterable()) return dynamic_cast<LgsUnknown*>(iter->baseType);
    return false;
}

bool LgsType::isSliceable() {
    return asStr() || asDArray() || asSArray();
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.contains(method->funcType->name)) return false;
    methods[method->funcType->name] = method;
    return true;
}

bool LgsType::hasRecursiveTypes() const {
    std::unordered_set<std::string> visited;
    const auto check = [&](const auto& self, const LgsType* type) -> bool {
        for (const auto field : type->fields) {
            if (const auto innerObj = field->type->asObject()) {
                if (visited.contains(innerObj->name)) return true;
                visited.insert(innerObj->name);
                if (self(self, innerObj)) return true;
            }
        }
        for (const auto& [_, method] : type->methods) {
            if (const auto innerObj = method->funcType->rt->asObject()) {
                if (visited.contains(innerObj->name)) return true;
                visited.insert(innerObj->name);
                if (self(self, innerObj)) return true;
            }
            for (size_t i = 1; i < method->funcType->params.size(); ++i) {
                if (const auto innerObj = method->funcType->params[i].type->asObject()) {
                    if (visited.contains(innerObj->name)) return true;
                    visited.insert(innerObj->name);
                    if (self(self, innerObj)) return true;
                }
            }
        }
        return false;
    };
    return check(check, this);
}

std::string LgsType::getRTTName() {
    return LGS_TYPEINFO_PREFIX + getName();
}

Constant* LgsType::getRTType(LgsCodeGen& cg) {
    assert(rttKind != RTT_UNKNOWN);
    const auto rttName = getRTTName();
    const auto baseStruct = cg.getRTTStruct();
    Constant* initializer = nullptr;
    if (cg.mode == CG_MODE_RTT) {
        const auto extra = getRTTypeExtra(cg);
        const std::vector<Constant*> args = {
            cg.getString(pname()),
            IRSize(cg),
            cg.i32(rttKind),
            cg.i1(isHeap),
            cg.i1(passByRef),
            extra
        };
        initializer = ConstantStruct::get(baseStruct, args);
    }
    return cg.createGlobal(rttName, baseStruct, initializer);
}

ConstantInt* LgsType::IRSize(LgsCodeGen& cg) {
    return cg.getTypeSize(getIRType(cg));
}

Type* LgsType::getStorageType(LgsCodeGen& cg) {
    return passByRef ? cg.ptrTy() : getIRType(cg);
}

LgsField* LgsType::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    return nullptr;
}

LgsFunc* LgsType::getMethod(const std::string& methodName) {
    if (methods.contains(methodName)) return methods[methodName];
    return nullptr;
}

std::string LgsType::getBaseName() {
    return getName();
}

std::string LgsType::pname() {
    return getName();
}

bool LgsType::equals(LgsType* other) {
    return getName() == other->getName();
}

void LgsType::hashNode(size_t& oldHash) { assert(0);}

Value* LgsType::moveValue(LgsCodeGen& cg, Value* value, Value* toLevel) {
    return cg.moveValue(getBaseName(), value, toLevel);
}

void LgsType::asIRText(LgsStrBuilder& sb, Value* value) {
    assert(0);
}

Constant* LgsType::getRTTypeExtra(LgsCodeGen& cg) {
    return cg.null();
}

Value* LgsType::getIRZeroValue(LgsCodeGen& cg, Value* pointee, Value* level) {
    assert(0);
}

Value* LgsType::hashValue(LgsCodeGen& cg, Value* value) { assert(0);}
Value* LgsType::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::bitAndIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::bitOrIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::bitXorIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::lshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0);}
Value* LgsType::rshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) { assert(0); }

LgsAny* LgsType::asAny() { return dynamic_cast<LgsAny*>(this); }
LgsChar* LgsType::asChar() { return dynamic_cast<LgsChar*>(this); }
LgsStr* LgsType::asStr() { return dynamic_cast<LgsStr*>(this); }
LgsBool* LgsType::asBool() { return dynamic_cast<LgsBool*>(this); }
LgsByte* LgsType::asByte() { return dynamic_cast<LgsByte*>(this); }
LgsInt* LgsType::asInt() { return dynamic_cast<LgsInt*>(this); }
LgsShort* LgsType::asShort() { return dynamic_cast<LgsShort*>(this); }
LgsLong* LgsType::asLong() { return dynamic_cast<LgsLong*>(this); }
LgsSize* LgsType::asSize() { return dynamic_cast<LgsSize*>(this); }
LgsUByte* LgsType::asUByte() { return dynamic_cast<LgsUByte*>(this); }
LgsUShort* LgsType::asUShort() { return dynamic_cast<LgsUShort*>(this); }
LgsUInt* LgsType::asUInt() { return dynamic_cast<LgsUInt*>(this); }
LgsULong* LgsType::asULong() { return dynamic_cast<LgsULong*>(this); }
LgsFloat* LgsType::asFloat() { return dynamic_cast<LgsFloat*>(this); }
LgsDouble* LgsType::asDouble() { return dynamic_cast<LgsDouble*>(this); }
LgsFuncType* LgsType::asFuncType() { return dynamic_cast<LgsFuncType*>(this); }
LgsObject* LgsType::asObject() { return asSelf() ? dynamic_cast<LgsObject*>(asSelf()->baseType) : dynamic_cast<LgsObject*>(this); }
LgsInterface* LgsType::asInterface() { return dynamic_cast<LgsInterface*>(this); }
LgsEnum* LgsType::asEnum() { return dynamic_cast<LgsEnum*>(this); }
LgsEnumField* LgsType::asEnumField() { return dynamic_cast<LgsEnumField*>(this); }
LgsTypeParam* LgsType::asTypeParam() { return dynamic_cast<LgsTypeParam*>(this); }
LgsSelf* LgsType::asSelf() { return dynamic_cast<LgsSelf*>(this); }
LgsIterable* LgsType::asIterable() { return dynamic_cast<LgsIterable*>(this); }
LgsSArray* LgsType::asSArray() { return dynamic_cast<LgsSArray*>(this); }
LgsDArray* LgsType::asDArray() { return dynamic_cast<LgsDArray*>(this); }
LgsSet* LgsType::asSet() { return dynamic_cast<LgsSet*>(this); }
LgsVec* LgsType::asVec() { return dynamic_cast<LgsVec*>(this); }
LgsMatrix* LgsType::asMatrix() { return dynamic_cast<LgsMatrix*>(this); }
LgsCPtr* LgsType::asCPtr() { return dynamic_cast<LgsCPtr*>(this); }
LgsMap* LgsType::asMap() { return dynamic_cast<LgsMap*>(this); }
LgsTypePair* LgsType::asPair() { return dynamic_cast<LgsTypePair*>(this); }
LgsSubType* LgsType::asSubtype() { return dynamic_cast<LgsSubType*>(this); }
LgsVariadic* LgsType::asVariadic() { return dynamic_cast<LgsVariadic*>(this); }
LgsNullable* LgsType::asNullable() { return dynamic_cast<LgsNullable*>(this); }
LgsFieldType* LgsType::asFieldType() { return dynamic_cast<LgsFieldType*>(this); }

LgsType::~LgsType() {
    for (const auto [_, method] : methods) {
        if (!method) continue;
        delete method;
    }
    methods.clear();
    for (const auto field : fields) {
        field->type = nullptr;
        delete field;
    }
    fields.clear();
}

void freeType(LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    if (type->asEnum() || type->asSubtype() || type->asTypeParam() || type->asObject()) return;
    delete type;
}

Value* loadRTTInfoName(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(cg.getRTTStruct(), ptr, LgsTypeInfoIndices::name, cg.ptrTy());
}

Value* loadRTTInfoSize(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(cg.getRTTStruct(), ptr, LgsTypeInfoIndices::size, cg.sizeTy());
}

Value* loadRTTInfoKind(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(cg.getRTTStruct(), ptr, LgsTypeInfoIndices::kind, cg.i32Ty());
}

Value* loadRTTInfoIsHeap(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(cg.getRTTStruct(), ptr, LgsTypeInfoIndices::isHeap, cg.i1Ty());
}

Value* loadRTTInfoExtra(LgsCodeGen& cg, Value* ptr) {
    return cg.loadField(cg.getRTTStruct(), ptr, LgsTypeInfoIndices::extra, cg.ptrTy());
}

Value* exprEqNull(LgsCodeGen& cg, Value* expr, LgsType* type) {
    if (type->passByRef) return cg.builder.CreateIsNull(expr);
    return cg.builder.CreateNot(type->asNullable()->loadIsSet(cg, expr));
}

Value* eqIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (isa<ConstantPointerNull>(left) && isa<ConstantPointerNull>(right)) {
        return cg.true_();
    }
    if (isa<ConstantPointerNull>(left)) {
        return exprEqNull(cg, right, type);
    }
    if (isa<ConstantPointerNull>(right)) {
        return exprEqNull(cg, left, type);
    }
    if (type->isInt || type->asChar()) {
        const auto [l, r] = loadNumberPair(cg, left, right, type);
        return cg.builder.CreateICmpEQ(l, r);
    }
    if (type->isFloat) {
        const auto [l, r] = loadNumberPair(cg, left, right, type);
        return cg.builder.CreateFCmpOEQ(l, r);
    }
    if (type->asStr()) {
        return cg.strsEqual(LgsStr::loadIRData(cg, left), LgsStr::loadIRData(cg, right));
    }
    if (const auto dArr = type->asDArray()) {
        return cg.builder.CreateCall(dArr->getEqFunc(cg), {left, right});
    }
    if (const auto sArr = type->asSArray()) {
        return cg.builder.CreateCall(sArr->getEqFunc(cg), {left, right});
    }
    if (const auto obj = type->asObject()) {
        return cg.builder.CreateCall(obj->getObjsEqFunc(cg), {left, right});
    }
    if (type->asNullable()) {
        assert(0);
    }
    assert(0);
}

Value* neIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    return cg.builder.CreateNot(eqIR(cg, left, right, type));
}

Value* ltIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    auto [l, r] = loadNumberPair(cg, left, right, type);
    if (type->isUnsinged) return cg.builder.CreateICmpULT(l, r);
    if (type->isInt) return cg.builder.CreateICmpSLT(l, r);
    if (type->isFloat) return cg.builder.CreateFCmpOLT(l, r);
    assert(0);
}

Value* gtIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    auto [l, r] = loadNumberPair(cg, left, right, type);
    if (type->isUnsinged) return cg.builder.CreateICmpUGT(l, r);
    if (type->isInt) return cg.builder.CreateICmpSGT(l, r);
    if (type->isFloat) return cg.builder.CreateFCmpOGT(l, r);
    assert(0);
}

Value* geIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    auto [l, r] = loadNumberPair(cg, left, right, type);
    if (type->isUnsinged) return cg.builder.CreateICmpUGE(l, r);
    if (type->isInt) return cg.builder.CreateICmpSGE(l, r);
    if (type->isFloat) return cg.builder.CreateFCmpOGE(l, r);
    assert(0);
}

Value* leIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    auto [l, r] = loadNumberPair(cg, left, right, type);
    if (type->isUnsinged) return cg.builder.CreateICmpULE(l, r);
    if (type->isInt) return cg.builder.CreateICmpSLE(l, r);
    if (type->isFloat) return cg.builder.CreateFCmpOLE(l, r);
    assert(0);
}

Value* andIR(LgsCodeGen& cg, const std::vector<Value*>& values) {
    const auto endBlock = cg.createBlock("and_end");
    std::vector<std::pair<Value*, BasicBlock*>> incoming;
    for (const auto value : values) {
        const auto nextBlock = cg.createBlock("and_next");
        cg.builder.CreateCondBr(value, nextBlock, endBlock);
        incoming.emplace_back(cg.false_(), cg.builder.GetInsertBlock());
        cg.startBlock(nextBlock);
    }
    cg.builder.CreateBr(endBlock);
    incoming.emplace_back(values.back(), cg.builder.GetInsertBlock());
    cg.startBlock(endBlock);
    const auto phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), incoming.size());
    for (const auto& [val, block] : incoming) {
        phi->addIncoming(val, block);
    }
    return phi;
}

Value* orIR(LgsCodeGen& cg, const std::vector<Value*>& values) {
    const auto endBlock = cg.createBlock("or_end");
    std::vector<std::pair<Value*, BasicBlock*>> incoming;
    for (const auto value : values) {
        const auto nextBlock = cg.createBlock("or_next");
        cg.builder.CreateCondBr(value, nextBlock, endBlock);
        incoming.emplace_back(cg.true_(), cg.builder.GetInsertBlock());
        cg.startBlock(nextBlock);
    }
    cg.builder.CreateBr(endBlock);
    incoming.emplace_back(values.back(), cg.builder.GetInsertBlock());
    cg.startBlock(endBlock);
    const auto phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), incoming.size());
    for (const auto& [val, block] : incoming) {
        phi->addIncoming(val, block);
    }
    return phi;
}

Value* crossIR(LgsCodeGen& cg, Value* left, Value* right, LgsVec* vec) {
    const auto results = vec->getIRZeroValue(cg, nullptr, cg.currentLevel);
    const auto [l, r] = loadVecPair(cg, left, right, vec);
    cg.builder.CreateCall(getCrossProductFunc(cg, vec), {results, l, r});
    return results;
}

LgsType* getBiggestIntType(const std::vector<LgsType*>& types) {
    if (types.empty()) return nullptr;
    LgsType* inferredType = nullptr;
    uint8_t highestPrecedence = 0;
    for (size_t i = 0; i < types.size(); ++i) {
        const auto& arg = types[i];
        if (!arg) return nullptr;
        LgsType* currentType = nullptr;
        if (arg->isScalar()) {
            currentType = arg;
        } else if (const auto iter = arg->asIterable()) {
            currentType = iter->baseType;
        }
        if (!currentType || !currentType->isScalar()) return nullptr;
        const auto precedence = numberPrecedences[currentType->getName()];
        if (highestPrecedence >= precedence) continue;
        inferredType = currentType;
        highestPrecedence = precedence;
    }
    assert(inferredType);
    return inferredType;
}

Type* getBiggestIntType(const std::vector<Type*>& types) {
    if (types.empty()) return nullptr;
    Type* inferredType = nullptr;
    uint8_t highestPrecedence = 0;
    for (const auto type : types) {
        uint8_t precedence = 0;
        if (type->isIntegerTy()) {
            precedence = type->getIntegerBitWidth();
        } else if (type->isFloatTy()) {
            precedence = 64;
        } else if (type->isDoubleTy()) {
            precedence = 128;
        } else {
            return nullptr;
        }
        if (highestPrecedence >= precedence) continue;
        inferredType = type;
        highestPrecedence = precedence;
    }
    assert(inferredType);
    return inferredType;
}

Value* loadAsInt(LgsCodeGen& cg, Value* v, Type* intType) {
    const auto ty = v->getType();
    if (ty->isPointerTy()) return cg.load(intType, v);
    if (ty->isIntegerTy()) return cg.builder.CreateSExt(v, intType);
    if (ty->isFloatingPointTy()) return cg.builder.CreateFPToSI(v, intType);
    return v;
}

Value* loadAsFloat(LgsCodeGen& cg, Value* v, Type* floatType) {
    const auto ty = v->getType();
    if (ty->isPointerTy()) return cg.load(floatType, v);
    if (ty->isFloatingPointTy()) return cg.builder.CreateFPExt(v, floatType);
    if (ty->isIntegerTy()) return cg.builder.CreateSIToFP(v, floatType);
    return v;
}

Value* loadAsVec(LgsCodeGen& cg, Value* v, Type* vecType) {
    if (v->getType()->isVectorTy()) return v;
    return cg.load(vecType, v);
}

bool inRange(const uint64_t value, LgsType* toType) {
    if (toType->asBool()) return value == 0 || value == 1;
    if (toType->asChar() || toType->asByte()) return inRangeGeneric<int8_t>(value);
    if (toType->asShort()) return inRangeGeneric<int16_t>(value);
    if (toType->asInt()) return inRangeGeneric<int32_t>(value);
    if (toType->asLong()) return inRangeGeneric<int64_t>(value);
    if (toType->asSize()) return inRangeGeneric<size_t>(value);
    if (toType->asUByte()) return inRangeGeneric<uint8_t>(value);
    if (toType->asUShort()) return inRangeGeneric<uint16_t>(value);
    if (toType->asUInt()) return inRangeGeneric<uint32_t>(value);
    if (toType->asULong()) return inRangeGeneric<uint64_t>(value);
    if (toType->asFloat()) return inRangeGeneric<float>(value);
    if (toType->asDouble()) return inRangeGeneric<double>(value);
    return false;
}

LgsType* inferType(const std::vector<LgsExpr*>& elements) {
    LgsType* result = nullptr;
    for (const auto element : elements) {
        const auto elemType = element->type;
        if (!result) {
            result = elemType;
            continue;
        }
        if (result->canCastTo(elemType)) {
            result = elemType;
        } else {
            return nullptr;
        }
    }
    return result;
}

std::pair<Value*, Value*> loadNumberPair(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    const auto ty = type->getIRType(cg);
    if (type->isInt) return {loadAsInt(cg, left, ty), loadAsInt(cg, right, ty)};
    if (type->isFloat) return {loadAsFloat(cg, left, ty), loadAsFloat(cg, right, ty)};
    assert(0);
}

std::pair<Value*, Value*> loadVecPair(LgsCodeGen& cg, Value* left, Value* right, LgsType* vec) {
    const auto ty = vec->getIRType(cg);
    return {loadAsVec(cg, left, ty), loadAsVec(cg, right, ty)};
}
