#include "LgsConfigs.h"
#include "exprs/LgsVectorExpr.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "types/LgsAny.h"
#include "types/LgsPtr.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsEnum.h"
#include "types/LgsGenericType.h"
#include "types/iterables/LgsMap.h"
#include "types/LgsNullable.h"
#include "types/LgsSubType.h"
#include "types/LgsUnknown.h"
#include "types/iterables/LgsMatrix.h"
#include "types/primitives/LgsVoid.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsSet.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsChar.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"
#include <iostream>

bool LgsType::addField(LgsField* field) {
    fields.push_back(field);
    return true;
}

bool LgsType::addMethod(LgsFunc* method) {
    if (methods.contains(method->funcType->name)) return false;
    methods[method->funcType->name] = method;
    return true;
}

bool LgsType::addEmptyMethod(const std::string& name) {
    if (methods.contains(name)) return false;
    methods[name] = nullptr;
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

Constant* LgsType::getRTType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsType::applyBinOp(LgsType* toType, LgsBinOp& op) {
    assert(0);
}

void LgsType::hashNode(size_t& oldHash) {
    assert(0);
}

std::string LgsType::pname() {
    return getName();
}

std::string LgsType::getGenericName() {
    return getName();
}

bool LgsType::equals(LgsType* other) {
    return getName() == other->getName();
}

bool LgsType::isVoid() {
    return dynamic_cast<LgsVoid*>(this);
}

bool LgsType::isNumber() const {
    return isInt || isFloatingPoint;
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

LgsType* LgsType::applyIntBinOp(LgsType* toType, const LgsBinOpType op) {
    switch (op) {
    case POW:
        if (toType->canCastTo(this)) return &LGS_DOUBLE;
        break;
    case ADD:
    case SUB:
    case MUL:
    case MODULO:
    case BIT_AND:
    case BIT_OR:
    case BIT_XOR:
    case LSHIFT:
    case RSHIFT:
        if (toType->asFloat()) return toType;
        if (toType->canCastTo(this)) return this;
        break;
    case DIV:
        if (toType->isNumber()) return &LGS_FLOAT;
        break;
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE: {
        if (toType->canCastTo(this)) return &LGS_BOOL;
        break;
    }
    case IN: {
        const auto iter = toType->asIterable();
        if (!iter) break;
        if (iter->getDimension() == 1 && canCastTo(iter->baseType)) {
            return &LGS_BOOL;
        }
        break;
    }
    default:
        break;
    }
    return nullptr;
}

void LgsType::cloneFields(LgsType* newType) const {
    newType->fields.clear();
    for (const auto& field : fields) {
        const auto newField = new LgsField(*field);
        newField->type = field->type->clone();
        if (field->expr) {
            newField->expr = field->expr->clone();
        }
        newType->addField(newField);
    }
}

void LgsType::cloneMethods(LgsType* newType) const {
    newType->methods.clear();
    for (const auto& [_, method] : methods) {
        const auto newMethod = new LgsFunc(*method);
        if (method->stmtsBlock) newMethod->stmtsBlock = method->stmtsBlock->clone();
        newMethod->funcType = method->funcType->clone();
        newType->addMethod(newMethod);
    }
}

Value* LgsType::orInt(LgsLLVMGen& cg, const LgsExpr* self, const LgsExpr* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("or_right", func);
    const auto endBlock = cg.createBlock("or_end", func);
    cg.builder.CreateCondBr(self->IRValue, endBlock, rightBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.true_(), currentBlock);
    phi->addIncoming(other->IRValue, rightBlock);
    return phi;
}

Value* LgsType::andInt(LgsLLVMGen& cg, LgsExpr* self, const LgsExpr* other) {
    const auto currentBlock = cg.builder.GetInsertBlock();
    const auto func = currentBlock->getParent();
    const auto rightBlock = cg.createBlock("and_right", func);
    const auto endBlock = cg.createBlock("and_end", func);
    cg.builder.CreateCondBr(self->IRValue, rightBlock, endBlock);
    cg.builder.SetInsertPoint(rightBlock);
    cg.builder.CreateBr(endBlock);
    cg.builder.SetInsertPoint(endBlock);
    auto* phi = cg.builder.CreatePHI(cg.builder.getInt1Ty(), 2);
    phi->addIncoming(cg.false_(), currentBlock);
    phi->addIncoming(other->IRValue, rightBlock);
    return phi;
}

Value* LgsType::addIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::subIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::mulIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::divIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::modIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::powIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::bitAndIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::bitOrIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::bitXorIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::lshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* other) {
    assert(0);
}

Value* LgsType::rshiftIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::eqIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::neIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::ltIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::gtIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::geIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::leIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::andIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
    assert(0);
}

Value* LgsType::orIR(LgsLLVMGen& cg, LgsExpr* left, LgsExpr* right) {
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

LgsGenericType* LgsType::asGeneric() {
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

void freeType(const LgsType* type) {
    if (!type) return;
    if (type->isPrimitive) return;
    delete type;
}
