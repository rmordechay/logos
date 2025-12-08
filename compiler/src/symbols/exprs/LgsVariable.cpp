#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsNullable.h"

#include <codegen/LgsCgModule.h>

Value* LgsVariable::loadIR(LgsCgModule& cg) {
    switch (ref.symbolType) {
    case PARAM:
        return ref.param->loadIR(cg);
    case VAR_DEC:
        return ref.varDec->loadIR(cg);
    case FIELD:
        return ref.field->loadIR(cg);
    default:
        assert(0);
    }
}

bool LgsVariable::equals(LgsExpr* other) {
    const auto otherVar = other->asVariable();
    if (!otherVar) return false;
    switch (ref.symbolType) {
    case VAR_DEC:
        return ref.varDec->name == otherVar->name;
    case PARAM:
        return ref.param->name == otherVar->name;
    default:
        break;
    }
    assert(0);
}

LgsExpr* LgsVariable::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsVariable::assign(LgsCgModule& cg, LgsExpr* expr) {
    if (const auto nullable = type->asNullable()) {
        if (!nullable->passByRef) {
            const auto isSet = cg.builder.CreateIsNotNull(expr->IRValue);
            nullable->setNullableFields(cg, IRValue, expr->IRValue, isSet);
            return;
        }
    }
    cg.builder.CreateStore(expr->IRValue, IRValue);
}

Value* LgsVariable::hashValue(LgsCgModule& cg) {
    switch (ref.symbolType) {
    case PARAM:
        return cg.callHash(ref.param->IRValue);
    case VAR_DEC:
        return ref.varDec->expr->hashValue(cg);
    case FIELD:
        if (ref.field->isEnumField) return cg.usize(ref.field->position);
        if (ref.field->type->asEnum()) return ref.field->loadIR(cg);
        return cg.callHash(ref.field->IRValue);
    default:
        assert(0);
    }
}

std::string LgsVariable::asText() {
    return name;
}

void LgsVariable::setDebugValue(LgsCgModule& cg) {
    setDebugLoc(cg);
    const auto var = cg.debugger.diBuilder->createAutoVariable(
        cg.debugger.subprogram->getScope(),
        name,
        cg.debugger.diFile,
        location.lineStart,
        type->getDebugType(cg)
    );
    cg.debugger.diBuilder->insertDeclare(
        IRValue,
        var,
        cg.debugger.diBuilder->createExpression(),
        cg.getDebugLoc(location),
        cg.builder.GetInsertBlock()
    );
}

LgsExpr* LgsVariable::clone() {
    const auto newVar = new LgsVariable(*this);
    if (type) newVar->type = type;
    return newVar;
}
