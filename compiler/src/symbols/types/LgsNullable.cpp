#include "types/LgsNullable.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsNullableExpr.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsBool.h"

LgsField* LgsNullable::getField(const std::string& fieldName) {
    return baseType->getField(fieldName);
}

LgsFunc* LgsNullable::getMethod(const std::string& methodName) {
    return baseType->getMethod(methodName);
}

Type* LgsNullable::getIRType(LgsCgModule& cg) {
    if (!baseType || baseType->passByRef) return cg.ptrTy();
    return cg.getStructType({baseType->getIRType(cg), cg.i1Ty()}, "nullable_" + baseType->getName());
}

void LgsNullable::setIRValue(LgsCgModule& cg, Value* nullablePtr, Value* value) {
    if (baseType->passByRef) {
        cg.builder.CreateStore(value, nullablePtr);
    } else {
        const auto ty = getIRType(cg);
        const auto valueField = cg.builder.CreateStructGEP(ty, nullablePtr, 0);
        const auto isSetField = cg.builder.CreateStructGEP(ty, nullablePtr, 1);
        cg.builder.CreateStore(cg.builder.CreateIsNotNull(value), isSetField);
        cg.builder.CreateStore(value, valueField);
    }
}

Constant* LgsNullable::getRTType(LgsCgModule& cg) {
    const auto genericName = getGenericName();
    if (!baseType) {
        return cg.getRTTypeInfo(genericName, 0, 0, RTT_ANY, cg.null());
    }
    const auto st = cg.getStructType({cg.ptrTy(), cg.i1Ty()}, genericName);
    const auto baseRTType = baseType->getRTType(cg);
    const auto sv = ConstantStruct::get(st, {baseRTType, cg.i1(baseType->passByRef)});
    return cg.getRTTypeInfo(genericName, sizeBytes(), sizeBytes(), RTT_NULLABLE, sv);
}

LgsExpr* LgsNullable::getZeroValue() {
    return new LgsNullableExpr(true);
}

std::string LgsNullable::getName() {
    return baseType ? baseType->getName() + name : name;
}

std::string LgsNullable::pname() {
    return baseType ? baseType->getName() + '?' : name;
}

Value* LgsNullable::eqIR(LgsCgModule& cg, LgsExpr* left, LgsExpr* right) {
    const auto l = left->asNullableExpr();
    const auto r = right->asNullableExpr();
    if (l && r) {
        if (l->isNull && r->isNull) return cg.true_();
        if (r->isNull) return cg.builder.CreateIsNull(left->IRValue);
        if (l->isNull) return cg.builder.CreateIsNull(right->IRValue);
    } else if (l && l->isNull) {
        return cg.builder.CreateIsNull(right->IRValue);
    } else if (r && r->isNull) {
        return cg.builder.CreateIsNull(left->IRValue);
    }
    return cg.builder.CreateICmpEQ(left->loadIR(cg), right->loadIR(cg));
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (baseType->isVoid() && !other->isVoid()) return false;
    if (other->getName() == LgsAny::name) return true;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    if (!otherNullable->baseType) return true; // meaning null
    if (!baseType) return true;
    return baseType->canCastTo(otherNullable->baseType);
}

LgsType* LgsNullable::applyBinOp(LgsType* toType, LgsBinOp& op) {
    switch (op.opType) {
    case ADD:
        break;
    case SUB:
        break;
    case MUL:
        break;
    case DIV:
        break;
    case MODULO:
        break;
    case POW:
        break;
    case BIT_AND:
        break;
    case BIT_OR:
        break;
    case BIT_XOR:
        break;
    case LSHIFT:
        break;
    case RSHIFT:
        break;
    case EQ:
    case NE:
    case LT:
    case GT:
    case GE:
    case LE: {
        if (!baseType || baseType->canCastTo(toType)) return &LGS_BOOL;
        break;
    }
    case AND:
        break;
    case OR:
        break;
    case IN:
        break;
    case CROSS:
        break;
    case NOOP:
        break;
    }
    return nullptr;
}

size_t LgsNullable::sizeBytes() {
    return !baseType ? 0 : baseType->sizeBytes() + sizeof(bool);
}

std::string LgsNullable::fmtStr() const {
    return baseType->fmtStr();
}

DIType* LgsNullable::getDebugType(LgsCgModule& cg) {
    assert(0);
}

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
