#include "exprs/LgsVariable.h"
#include "exprs/LgsInstance.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsNullable.h"
#include <codegen/LgsCodeGen.h>
#include "types/LgsEnum.h"

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

LgsExpr* LgsVariable::cast(LgsType* toType, bool explicitly) {
    if (toType && type && type->canCastTo(toType)) {
        setType(toType);
    }
    return this;
}

std::string LgsVariable::asText() {
    return name;
}

void LgsVariable::setDebugValue(LgsCodeGen& cg) {
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

LgsVariable* LgsVariable::clone() {
    const auto newVar = new LgsVariable(*this);
    newVar->setType(type);
    return newVar;
}
