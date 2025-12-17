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

bool LgsType::addField(LgsField* field) {
    fields.push_back(field);
    return true;
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
    const auto method = methods.find(methodName);
    if (method != methods.end()) {
        if (method->second) {
            return method->second;
        }
    }
    return nullptr;
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

bool LgsType::isVoid() {
    return dynamic_cast<LgsVoid*>(this);
}

bool LgsType::isNumber() {
    return isInt || isFloat || asComplex();
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

LgsType* LgsType::extendInt() {
    if (asBool()) {
        return &LGS_BYTE;
    }
    if (asByte()) {
        return &LGS_SHORT;
    }
    if (asShort()) {
        return &LGS_INT;
    }
    if (asInt()) {
        return &LGS_LONG;
    }
    return this;
}

void LgsType::cloneFields(LgsType* newType) const {
    newType->fields.clear();
    for (const auto& field : fields) {
        const auto newField = new LgsField(*field);
        newField->type = field->type;
        if (field->expr) {
            newField->expr = field->expr;
        }
        newType->addField(newField);
    }
}

void LgsType::cloneMethods(LgsType* newType) const {
    newType->methods.clear();
    for (const auto& [_, method] : methods) {
        const auto newMethod = new LgsFunc(*method);
        if (method->stmtsBlock) newMethod->stmtsBlock = method->stmtsBlock;
        newMethod->funcType = method->funcType;
        newType->addMethod(newMethod);
    }
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

Value* LgsType::lshiftIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* other) {
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

Value* eqNull(LgsCgModule& cg, const LgsExpr* expr) {
    const auto nullable = expr->type->asNullable();
    if (expr->type->passByRef) return cg.builder.CreateIsNull(expr->IRValue);
    return cg.builder.CreateNot(nullable->getIsSet(cg, expr->IRValue));
}

Value* neNull(LgsCgModule& cg, const LgsExpr* expr) {
    const auto nullable = expr->type->asNullable();
    if (expr->type->passByRef) return cg.builder.CreateIsNotNull(expr->IRValue);
    return nullable->getIsSet(cg, expr->IRValue);
}

Value* eqComplex(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto l = cg.builder.CreateLoad(left->type->getIRType(cg), left->IRValue);
    const auto r = cg.builder.CreateLoad(right->type->getIRType(cg), right->IRValue);
    const auto lReal = cg.builder.CreateExtractValue(l, 0);
    const auto lImag = cg.builder.CreateExtractValue(l, 1);
    const auto rReal = cg.builder.CreateExtractValue(r, 0);
    const auto rImag = cg.builder.CreateExtractValue(r, 1);
    const auto realEq = cg.builder.CreateICmpEQ(lReal, rReal);
    const auto imagEq = cg.builder.CreateICmpEQ(lImag, rImag);
    return cg.builder.CreateAnd(realEq, imagEq);
}

Value* neComplex(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto l = cg.builder.CreateLoad(left->type->getIRType(cg), left->IRValue);
    const auto r = cg.builder.CreateLoad(right->type->getIRType(cg), right->IRValue);
    const auto lReal = cg.builder.CreateExtractValue(l, 0);
    const auto lImag = cg.builder.CreateExtractValue(l, 1);
    const auto rReal = cg.builder.CreateExtractValue(r, 0);
    const auto rImag = cg.builder.CreateExtractValue(r, 1);
    const auto realNe = cg.builder.CreateICmpNE(lReal, rReal);
    const auto imagNe = cg.builder.CreateICmpNE(lImag, rImag);
    return cg.builder.CreateOr(realNe, imagNe);
}

Value* eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->isNull && right->isNull) return cg.true_();
    if (left->isNull) return eqNull(cg, right);
    if (right->isNull) return eqNull(cg, left);
    if (left->type->isInt && right->type->isInt) {
        return cg.builder.CreateICmpEQ(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isFloat || right->type->isFloat) {
        const auto [l, r] = loadPairAsFloat(cg, left, right);
        return cg.builder.CreateFCmpOEQ(l, r);
    }
    if (left->type->asComplex() && right->type->asComplex()) {
        return eqComplex(cg, left, right);
    }
    if (left->type->asStr() && right->type->asStr()) {
        const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left->IRValue, right->IRValue});
        return cg.builder.CreateICmpEQ(rt, cg.i32Zero());
    }
    assert(0);
}

Value* neIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->isNull && right->isNull) return cg.false_();
    if (left->isNull) return neNull(cg, right);
    if (right->isNull) return neNull(cg, left);
    if (left->type->isInt && left->type->isInt) {
        return cg.builder.CreateICmpEQ(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isFloat && left->type->isFloat) {
        return cg.builder.CreateFCmpOEQ(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->asComplex() && right->type->asComplex()) {
        return neComplex(cg, left, right);
    }
    if (left->type->asStr() && right->type->asStr()) {
        const auto rt = cg.callFunc("strcmp", cg.i32Ty(), {cg.ptrTy(), cg.ptrTy()}, {left->IRValue, right->IRValue});
        return cg.builder.CreateICmpNE(rt, cg.i32Zero());
    }
    assert(0);
}

Value* ltIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->isUnsinged && right->type->isUnsinged) {
        return cg.builder.CreateICmpULT(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isInt && right->type->isInt) {
        return cg.builder.CreateICmpSLT(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isFloat || right->type->isFloat) {
        const auto [l, r] = loadPairAsFloat(cg, left, right);
        return cg.builder.CreateFCmpOLT(l, r);
    }
    assert(0);
}

Value* gtIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->isUnsinged && right->type->isUnsinged) {
        return cg.builder.CreateICmpUGT(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isInt && right->type->isInt) {
        return cg.builder.CreateICmpSGT(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isFloat || right->type->isFloat) {
        const auto [l, r] = loadPairAsFloat(cg, left, right);
        return cg.builder.CreateFCmpOGT(l, r);
    }
    assert(0);
}

Value* geIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->isUnsinged && right->type->isUnsinged) {
        return cg.builder.CreateICmpUGE(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isInt && right->type->isInt) {
        return cg.builder.CreateICmpSGE(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isFloat || right->type->isFloat) {
        const auto [l, r] = loadPairAsFloat(cg, left, right);
        return cg.builder.CreateFCmpOGE(l, r);
    }
    assert(0);
}

Value* leIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    if (left->type->isUnsinged && right->type->isUnsinged) {
        return cg.builder.CreateICmpULE(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isInt && right->type->isInt) {
        return cg.builder.CreateICmpSLE(left->loadIR(cg), right->loadIR(cg));
    }
    if (left->type->isFloat || right->type->isFloat) {
        const auto [l, r] = loadPairAsFloat(cg, left, right);
        return cg.builder.CreateFCmpOLE(l, r);
    }
    assert(0);
}

Value* andIR(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(left->IRValue, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(right->IRValue, rightBlock);
    return phi;
}

Value* orIR(LgsCgModule& cg, const LgsExpr* left, const LgsExpr* right) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(left->IRValue, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(right->IRValue, rightBlock);
    return phi;
}

std::pair<Value*, Value*> loadPairAsFloat(LgsCgModule& cg, LgsExpr* self, LgsExpr* other) {
    auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.floatTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.floatTy());
    }
    return {l, r};
}

std::pair<Value*, Value*> loadPairAsDouble(LgsCgModule& cg, LgsExpr* self, LgsExpr* other) {
    auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isIntegerTy()) {
        l = cg.builder.CreateSIToFP(l, cg.doubleTy());
    }
    if (r->getType()->isIntegerTy()) {
        r = cg.builder.CreateSIToFP(r, cg.doubleTy());
    }
    return {l, r};
}

std::pair<Value*, Value*> loadPairAsInt(LgsCgModule& cg, LgsExpr* self, LgsExpr* other) {
    auto l = self->loadIR(cg);
    auto r = other->loadIR(cg);
    if (l->getType()->isFloatTy()) {
        l = cg.builder.CreateFPToSI(l, cg.i32Ty());
    }
    if (r->getType()->isFloatTy()) {
        r = cg.builder.CreateFPToSI(r, cg.i32Ty());
    }
    return {l, r};
}

std::pair<Constant*, Constant*> getRTFieldsInfo(LgsCgModule& cg, const std::string& name, const std::vector<LgsOwner*>& values) {
    std::vector<Constant*> fieldTypes;
    std::vector<Constant*> fieldNames;
    fieldTypes.reserve(values.size());
    fieldNames.reserve(values.size());
    for (size_t i = 0; i < values.size(); ++i) {
        fieldTypes.push_back(values[i]->getType()->getRTType(cg));
        fieldNames.push_back(cg.getString(values[i]->getName()));
    }

    Constant* fieldTypesArr = nullptr;
    Constant* fieldNamesArr = nullptr;
    if (values.empty()) {
        fieldTypesArr = cg.null();
        fieldNamesArr = cg.null();
    } else {
        const auto types = LGS_TYPEINFO_PREFIX + name + "_fields";
        const auto names = LGS_TYPEINFO_PREFIX + name + "_names";
        const auto fieldsArrType = ArrayType::get(cg.getRTTBaseStruct(), values.size());
        const auto namesArrType = ArrayType::get(cg.ptrTy(), values.size());
        if (cg.isRTTModule) {
            fieldTypesArr = cg.createGlobal(types, fieldsArrType, ConstantArray::get(fieldsArrType, fieldTypes));
            fieldNamesArr = cg.createGlobal(names, namesArrType, ConstantArray::get(namesArrType, fieldNames));
        } else {
            fieldTypesArr = cg.createGlobal(types, fieldsArrType, nullptr);
            fieldNamesArr = cg.createGlobal(names, namesArrType, nullptr);
        }
    }
    return {fieldTypesArr, fieldNamesArr};
}
