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

bool LgsType::addField(LgsField* field) {
    fields.push_back(field);
    return true;
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.contains(method->funcType->name)) return false;
    methods[method->funcType->name] = method;
    return true;
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
    return (asObject() || asDArray()) && sizeBytes() >= BIG_SIZE_THRESHOLD;
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

LgsField* LgsType::getField(const std::string& fieldName) {
    for (auto* f : fields) {
        if (f->name == fieldName) return f;
    }
    return nullptr;
}

LgsFunc* LgsType::getMethod(const std::string& methodName) {
    const auto method = methods.find(methodName);
    if (method != methods.end()) {
        if (method->second) {
            return method->second;
        }
    }
    return nullptr;
}

LgsType* LgsType::replaceGenerics(LgsType* replacement, std::unordered_map<std::string, LgsType*>& replacements) {
    return this;
}

Value* LgsType::getIRZeroValue(LgsCgModule& cg, Value* pointee) {
    assert(0);
}

Type* LgsType::getTypeOrPtr(LgsCgModule& cg) {
    return passByRef ? cg.ptrTy() : getIRType(cg);
}

Constant* LgsType::getRTType(LgsCgModule& cg) {
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

Value* LgsType::addIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::subIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::mulIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::divIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::modIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::powIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::bitAndIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::bitOrIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::bitXorIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::rshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::crossIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
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
        delete field;
    }
    fields.clear();
}

Value* exprEqNull(LgsCgModule& cg, Value* expr, LgsType* type) {
    if (type->passByRef) return cg.builder.CreateIsNull(expr);
    return cg.builder.CreateNot(type->asNullable()->getIsSet(cg, expr));
}

Value* exprNeNull(LgsCgModule& cg, Value* expr, LgsType* type) {
    if (type->passByRef) return cg.builder.CreateIsNotNull(expr);
    return type->asNullable()->getIsSet(cg, expr);
}

Value* eqIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (isa<ConstantPointerNull>(left) && isa<ConstantPointerNull>(right)) return cg.true_();
    if (isa<ConstantPointerNull>(left)) return exprEqNull(cg, right, rightType);
    if (isa<ConstantPointerNull>(right)) return exprEqNull(cg, left, leftType);
    if (leftType->isInt && rightType->isInt) {
        const auto type = getBiggestIntType({leftType, rightType})->getIRType(cg);
        left = left->getType()->isPointerTy() ? cg.load(leftType->getIRType(cg), left) : left;
        right = right->getType()->isPointerTy() ? cg.load(rightType->getIRType(cg), right) : right;
        const auto l = cg.builder.CreateZExt(left, type);
        const auto r = cg.builder.CreateZExt(right, type);
        return cg.builder.CreateICmpEQ(l, r);
    }
    if (leftType->isFloat || rightType->isFloat) {
        const auto [l, r] = loadPairAsFloat(cg, left, right, leftType, rightType);
        return cg.builder.CreateFCmpOEQ(l, r);
    }
    if (leftType->asComplex() && rightType->asComplex()) {
        assert(0);
    }
    if (leftType->asStr() && rightType->asStr()) {
        const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left, right});
        return cg.builder.CreateICmpEQ(rt, cg.i32Zero());
    }
    assert(0);
}

Value* neIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (isa<ConstantPointerNull>(left) && isa<ConstantPointerNull>(right)) return cg.false_();
    if (isa<ConstantPointerNull>(left)) return exprNeNull(cg, right, rightType);
    if (isa<ConstantPointerNull>(right)) return exprNeNull(cg, left, leftType);
    if (leftType->isInt && rightType->isInt) {
        const auto type = getBiggestIntType({leftType, rightType})->getIRType(cg);
        left = left->getType()->isPointerTy() ? cg.load(leftType->getIRType(cg), left) : left;
        right = right->getType()->isPointerTy() ? cg.load(rightType->getIRType(cg), right) : right;
        const auto l = cg.builder.CreateZExt(left, type);
        const auto r = cg.builder.CreateZExt(right, type);
        return cg.builder.CreateICmpNE(l, r);
    }
    if (leftType->isFloat && rightType->isFloat) {
        return cg.builder.CreateFCmpONE(left, right);
    }
    if (leftType->asComplex() && rightType->asComplex()) {
        assert(0);
    }
    if (leftType->asStr() && rightType->asStr()) {
        const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left, right});
        return cg.builder.CreateICmpNE(rt, cg.i32Zero());
    }
    assert(0);
}

Value* ltIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (leftType->isUnsinged && rightType->isUnsinged) {
        return cg.builder.CreateICmpULT(left, right);
    }
    if (leftType->isInt && rightType->isInt) {
        return cg.builder.CreateICmpSLT(left, right);
    }
    if (leftType->isFloat || rightType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left, right, leftType, rightType);
        return cg.builder.CreateFCmpOLT(l, r);
    }
    assert(0);
}

Value* gtIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (leftType->isUnsinged && rightType->isUnsinged) {
        return cg.builder.CreateICmpUGT(left, right);
    }
    if (leftType->isInt && rightType->isInt) {
        return cg.builder.CreateICmpSGT(left, right);
    }
    if (leftType->isFloat || rightType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left, right, leftType, rightType);
        return cg.builder.CreateFCmpOGT(l, r);
    }
    assert(0);
}

Value* geIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (leftType->isUnsinged && rightType->isUnsinged) {
        return cg.builder.CreateICmpUGE(left, right);
    }
    if (leftType->isInt && rightType->isInt) {
        return cg.builder.CreateICmpSGE(left, right);
    }
    if (leftType->isFloat || rightType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left, right, leftType, rightType);
        return cg.builder.CreateFCmpOGE(l, r);
    }
    assert(0);
}

Value* leIR(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (leftType->isUnsinged && rightType->isUnsinged) {
        return cg.builder.CreateICmpULE(left, right);
    }
    if (leftType->isInt && rightType->isInt) {
        return cg.builder.CreateICmpSLE(left, right);
    }
    if (leftType->isFloat || rightType->isFloat) {
        auto [l, r] = loadPairAsFloat(cg, left, right, leftType, rightType);
        return cg.builder.CreateFCmpOLE(l, r);
    }
    assert(0);
}

Value* andIR(LgsCgModule& cg, Value* left, Value* right) {
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

Value* orIR(LgsCgModule& cg, Value* left, Value* right) {
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

std::pair<Value*, Value*> loadPairAsFloat(LgsCgModule& cg, Value* left, Value* right, LgsType* leftType, LgsType* rightType) {
    if (leftType->isInt) {
        left = cg.builder.CreateSIToFP(left, cg.floatTy());
    } else if (const auto lVec = leftType->asVec()) {
        if (leftType->asVec()->baseType->isInt) {
            left = cg.builder.CreateSIToFP(left, FixedVectorType::get(cg.floatTy(), lVec->dimVec));
        }
    }
    if (rightType->isInt) {
        right = cg.builder.CreateSIToFP(right, cg.floatTy());
    } else if (const auto rVec = rightType->asVec()) {
        if (rightType->asVec()->baseType->isInt) {
            right = cg.builder.CreateSIToFP(right, FixedVectorType::get(cg.floatTy(), rVec->dimVec));
        }
    }
    return {left, right};
}

std::pair<Value*, Value*> loadPairAsDouble(LgsCgModule& cg, Value* left, Value* right) {
    if (left->getType()->isIntegerTy()) {
        left = cg.builder.CreateSIToFP(left, cg.doubleTy());
    }
    if (right->getType()->isIntegerTy()) {
        right = cg.builder.CreateSIToFP(right, cg.doubleTy());
    }
    return {left, right};
}

/**
 * @return typesArr, hashesArr
 */
std::pair<Constant*, Constant*> getRTValuesInfo(LgsCgModule& cg, const std::string& name, const std::vector<LgsValue*>& values) {
    std::vector<Constant*> fieldTypes;
    std::vector<Constant*> fieldNames;
    fieldTypes.reserve(values.size());
    fieldNames.reserve(values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        const auto value = values[i];
        fieldTypes.push_back(value->getType()->getRTType(cg));
        fieldNames.push_back(llvm::dyn_cast<Constant>(cg.getString(value->getName())));
    }

    Constant* typesArrGlobal = nullptr;
    Constant* namesArrGlobal = nullptr;
    if (values.empty()) {
        typesArrGlobal = cg.null();
        namesArrGlobal = cg.null();
    } else {
        const auto types = LGS_TYPEINFO_PREFIX + name + "_fields";
        const auto names = LGS_TYPEINFO_PREFIX + name + "_names";
        const auto fieldsArrType = ArrayType::get(cg.getRTTBaseStruct(), values.size());
        const auto namesArrType = ArrayType::get(cg.ptrTy(), values.size());
        Constant* typesArr = nullptr;
        Constant* namesArr = nullptr;
        if (cg.mode == CG_MODE_RTTYPES) {
            typesArr = ConstantArray::get(fieldsArrType, fieldTypes);
            namesArr = ConstantArray::get(namesArrType, fieldNames);
        }
        typesArrGlobal = cg.createGlobal(types, fieldsArrType, typesArr);
        namesArrGlobal = cg.createGlobal(names, namesArrType, namesArr);
    }
    return {typesArrGlobal, namesArrGlobal};
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
