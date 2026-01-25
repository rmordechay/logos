#include "LgsConfigs.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsVectorExpr.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsComplex.h"
#include "types/LgsPtr.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsEnum.h"
#include "types/LgsGenericType.h"
#include "types/LgsNullable.h"
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

static std::unordered_map<std::string, uint8_t> numberPrecedences = {
    {LgsBool::name, 1},
    {LgsByte::name, 2},
    // {LgsUByte::name, 3},
    {LgsShort::name, 4},
    // {LgsUShort::name, 5},
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
    return getName() == LgsAny::name || (asPtr() && asPtr()->baseType->isVoid());
}

bool LgsType::isVoid() {
    return dynamic_cast<LgsVoid*>(this);
}

bool LgsType::isNumber() {
    return isInt || isFloat || asComplex();
}

bool LgsType::isScalar() const {
    return isInt || isFloat;
}

bool LgsType::isBig() {
    return (asObject() || asDArray()) && sizeBytes() >= LGS_BIG_SIZE_THRESHOLD;
}

bool LgsType::isUnknown() {
    if (dynamic_cast<LgsUnknown*>(this)) return true;
    if (const auto iter = asIterable()) return dynamic_cast<LgsUnknown*>(iter->baseType);
    return false;
}

bool LgsType::isSliceable() {
    return asStr() || asDArray() || asSArray();
}

bool LgsType::hasGenericTypes() {
    if (asGenericType()) return true;
    if (const auto ft = asFuncType()) {
        if (ft->rt->hasGenericTypes()) return true;
        for (const auto& param : ft->params) {
            if (param.type->hasGenericTypes()) return true;
        }
        return false;
    }
    if (const auto iter = asIterable()) {
        if (iter->baseType->hasGenericTypes()) return true;
    }
    return false;
}

ConstantInt* LgsType::IRSize(LgsCodeGen& cg) {
    return cg.usize(cg.getAllocSize(getIRType(cg)));
}

Type* LgsType::getTypeOrPtr(LgsCodeGen& cg) {
    return passByRef ? cg.ptrTy() : getIRType(cg);
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.contains(method->funcType->name)) return false;
    methods[method->funcType->name] = method;
    return true;
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

Value* LgsType::hashValue(LgsCodeGen& cg, Value* value) {
    assert(0);
}

Value* LgsType::asIRStr(LgsCodeGen& cg, Value* v) {
    assert(0);
}

Constant* LgsType::getRTType(LgsCodeGen& cg) {
    assert(0);
}

LgsType* LgsType::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

void LgsType::hashNode(size_t& oldHash) {
    assert(0);
}

std::string LgsType::pname() {
    return getName();
}

bool LgsType::equals(LgsType* other) {
    return getName() == other->getName();
}

LgsType* LgsType::clone() {
    assert(0);
}

Value* LgsType::addIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::subIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::mulIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::divIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::modIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::powIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::bitAndIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::bitOrIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::bitXorIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::lshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::rshiftIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

Value* LgsType::crossIR(LgsCodeGen& cg, LgsBinaryExpr* binExpr) {
    assert(0);
}

LgsAny* LgsType::asAny() {
    return dynamic_cast<LgsAny*>(this);
}

LgsChar* LgsType::asChar() {
    return dynamic_cast<LgsChar*>(this);
}

LgsStr* LgsType::asStr() {
    return dynamic_cast<LgsStr*>(this);
}

LgsBool* LgsType::asBool() {
    return dynamic_cast<LgsBool*>(this);
}

LgsByte* LgsType::asByte() {
    return dynamic_cast<LgsByte*>(this);
}

LgsInt* LgsType::asInt() {
    return dynamic_cast<LgsInt*>(this);
}

LgsShort* LgsType::asShort() {
    return dynamic_cast<LgsShort*>(this);
}

LgsLong* LgsType::asLong() {
    return dynamic_cast<LgsLong*>(this);
}

LgsSize* LgsType::asSize() {
    return dynamic_cast<LgsSize*>(this);
}

LgsUInt* LgsType::asUInt() {
    return dynamic_cast<LgsUInt*>(this);
}

LgsFloat* LgsType::asFloat() {
    return dynamic_cast<LgsFloat*>(this);
}

LgsDouble* LgsType::asDouble() {
    return dynamic_cast<LgsDouble*>(this);
}

LgsComplex* LgsType::asComplex() {
    return dynamic_cast<LgsComplex*>(this);
}

LgsFuncType* LgsType::asFuncType() {
    return dynamic_cast<LgsFuncType*>(this);
}

LgsObject* LgsType::asObject() {
    return dynamic_cast<LgsObject*>(this);
}

LgsInterface* LgsType::asInterface() {
    return dynamic_cast<LgsInterface*>(this);
}

LgsEnum* LgsType::asEnum() {
    return dynamic_cast<LgsEnum*>(this);
}

LgsGenericType* LgsType::asGenericType() {
    return dynamic_cast<LgsGenericType*>(this);
}

LgsIterable* LgsType::asIterable() {
    return dynamic_cast<LgsIterable*>(this);
}

LgsSArray* LgsType::asSArray() {
    return dynamic_cast<LgsSArray*>(this);
}

LgsDArray* LgsType::asDArray() {
    return dynamic_cast<LgsDArray*>(this);
}

LgsSet* LgsType::asSet() {
    return dynamic_cast<LgsSet*>(this);
}

LgsVec* LgsType::asVec() {
    return dynamic_cast<LgsVec*>(this);
}

LgsMatrix* LgsType::asMatrix() {
    return dynamic_cast<LgsMatrix*>(this);
}

LgsPtr* LgsType::asPtr() {
    return dynamic_cast<LgsPtr*>(this);
}

LgsMap* LgsType::asMap() {
    return dynamic_cast<LgsMap*>(this);
}

LgsTypePair* LgsType::asPair() {
    return dynamic_cast<LgsTypePair*>(this);
}

LgsSubType* LgsType::asSubtype() {
    return dynamic_cast<LgsSubType*>(this);
}

LgsVariadic* LgsType::asVariadic() {
    return dynamic_cast<LgsVariadic*>(this);
}

LgsNullable* LgsType::asNullable() {
    return dynamic_cast<LgsNullable*>(this);
}

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

Value* exprEqNull(LgsCodeGen& cg, Value* expr, LgsType* type) {
    if (type->passByRef) return cg.builder.CreateIsNull(expr);
    return cg.builder.CreateNot(type->asNullable()->getIsSet(cg, expr));
}

Value* exprNeNull(LgsCodeGen& cg, Value* expr, LgsType* type) {
    if (type->passByRef) return cg.builder.CreateIsNotNull(expr);
    return type->asNullable()->getIsSet(cg, expr);
}

Value* eqIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (isa<ConstantPointerNull>(left) && isa<ConstantPointerNull>(right)) return cg.true_();
    if (isa<ConstantPointerNull>(left)) return exprEqNull(cg, right, type);
    if (isa<ConstantPointerNull>(right)) return exprEqNull(cg, left, type);
    if (type->isInt) {
        if (left->getType()->isPointerTy()) {
            left = cg.load(type->getIRType(cg), left);
        }
        if (right->getType()->isPointerTy()) {
            right = cg.load(type->getIRType(cg), right);
        }
        return cg.builder.CreateICmpEQ(left, right);
    }
    if (type->isFloat) {
        const auto [l, r] = loadNumberPair(cg, left, right, cg.floatTy());
        return cg.builder.CreateFCmpOEQ(l, r);
    }
    if (type->asComplex()) {
        assert(0);
    }
    if (const auto dArr = type->asDArray()) {
        return cg.builder.CreateCall(dArr->generateArrEqFunc(cg), {left, right});
    }
    if (type->asStr()) {
        const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left, right});
        return cg.builder.CreateICmpEQ(rt, cg.i32Zero());
    }
    assert(0);
}

Value* neIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (isa<ConstantPointerNull>(left) && isa<ConstantPointerNull>(right)) return cg.false_();
    if (isa<ConstantPointerNull>(left)) return exprNeNull(cg, right, type);
    if (isa<ConstantPointerNull>(right)) return exprNeNull(cg, left, type);
    if (type->isInt) {
        return cg.builder.CreateICmpNE(left, right);
    }
    if (type->isFloat) {
        return cg.builder.CreateFCmpONE(left, right);
    }
    if (type->asComplex()) {
        assert(0);
    }
    if (const auto dArr = type->asDArray()) {
        return cg.builder.CreateNot(cg.builder.CreateCall(dArr->generateArrEqFunc(cg), {left, right}));
    }
    if (type->asStr()) {
        const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left, right});
        return cg.builder.CreateICmpNE(rt, cg.i32Zero());
    }
    assert(0);
}

Value* ltIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (type->isUnsinged) {
        return cg.builder.CreateICmpULT(left, right);
    }
    if (type->isInt) {
        return cg.builder.CreateICmpSLT(left, right);
    }
    if (type->isFloat) {
        auto [l, r] = loadNumberPair(cg, left, right, cg.floatTy());
        return cg.builder.CreateFCmpOLT(l, r);
    }
    assert(0);
}

Value* gtIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (type->isUnsinged) {
        return cg.builder.CreateICmpUGT(left, right);
    }
    if (type->isInt) {
        return cg.builder.CreateICmpSGT(left, right);
    }
    if (type->isFloat) {
        auto [l, r] = loadNumberPair(cg, left, right, cg.floatTy());
        return cg.builder.CreateFCmpOGT(l, r);
    }
    assert(0);
}

Value* geIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (type->isUnsinged) {
        return cg.builder.CreateICmpUGE(left, right);
    }
    if (type->isInt) {
        return cg.builder.CreateICmpSGE(left, right);
    }
    if (type->isFloat) {
        auto [l, r] = loadNumberPair(cg, left, right, cg.floatTy());
        return cg.builder.CreateFCmpOGE(l, r);
    }
    assert(0);
}

Value* leIR(LgsCodeGen& cg, Value* left, Value* right, LgsType* type) {
    if (type->isUnsinged) {
        return cg.builder.CreateICmpULE(left, right);
    }
    if (type->isInt) {
        return cg.builder.CreateICmpSLE(left, right);
    }
    if (type->isFloat) {
        auto [l, r] = loadNumberPair(cg, left, right, cg.floatTy());
        return cg.builder.CreateFCmpOLE(l, r);
    }
    assert(0);
}

Value* andIR(LgsCodeGen& cg, Value* left, Value* right) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(left, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(right, rightBlock);
    return phi;
}

Value* orIR(LgsCodeGen& cg, Value* left, Value* right) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(left, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(right, rightBlock);
    return phi;
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

std::pair<Value*, Value*> loadNumberPair(LgsCodeGen& cg, Value* left, Value* right, Type* type) {
    const auto leftType = left->getType();
    const auto rightType = right->getType();
    if (leftType->isIntegerTy()) {
        left = cg.builder.CreateSIToFP(left, type);
    } else if (const auto lVec = dyn_cast<FixedVectorType>(leftType)) {
        if (lVec->getElementType()->isIntegerTy()) {
            left = cg.builder.CreateSIToFP(left, FixedVectorType::get(type, lVec->getNumElements()));
        }
    }
    if (rightType->isIntegerTy()) {
        right = cg.builder.CreateSIToFP(right, type);
    } else if (const auto rVec = dyn_cast<FixedVectorType>(rightType)) {
        if (rVec->getElementType()->isIntegerTy()) {
            right = cg.builder.CreateSIToFP(right, FixedVectorType::get(type, rVec->getNumElements()));
        }
    }
    return {left, right};
}
