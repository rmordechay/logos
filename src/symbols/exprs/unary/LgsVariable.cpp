#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsStr.h"
#include <logos/LgsRuntime.h>

string LgsVariable::getName() {
    return name;
}

string LgsVariable::prettyName() {
    return name;
}

Value* LgsVariable::createIRValue(LgsRuntime* runtime) {
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->IRValue;
    case PARAM:
        return ref->param->getIRValue(runtime);
    case ENUM_FIELD:
        return ref->enumField->getGEP(runtime);
    case FUNC:
        return ref->func->getIRFunc(runtime);
    default:
        assert(false);
    }
}

bool LgsVariable::equals(LgsExpr* other) {
    if (const auto otherVar = other->asVariable()) {
        return ref->getPtr() == otherVar->ref->getPtr();
    }
    assert(false);
}

LgsExpr* LgsVariable::convertExpr(LgsType* type) {
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->expr->convertExpr(type);
    case PARAM:
    case ENUM_FIELD:
    case FIELD:
    case FUNC:
    case OBJECT:
    case INTERFACE:
    case GROUP:
    case ENUM:
    case UNKNOWN:
        break;
    }
    assert(false);
}

Value* LgsVariable::eqIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->eqIR(runtime, other);
    }
    return LgsUnaryExpr::eqIR(runtime, other);
}

Value* LgsVariable::neIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->neIR(runtime, other);
    }
    return LgsUnaryExpr::neIR(runtime, other);
}

Value* LgsVariable::gtIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->gtIR(runtime, other);
    }
    return LgsUnaryExpr::gtIR(runtime, other);
}

Value* LgsVariable::ltIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->ltIR(runtime, other);
    }
    return LgsUnaryExpr::gtIR(runtime, other);
}

Value* LgsVariable::geIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->geIR(runtime, other);
    }
    return LgsUnaryExpr::geIR(runtime, other);
}

Value* LgsVariable::leIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->leIR(runtime, other);
    }
    return LgsUnaryExpr::leIR(runtime, other);
}

Value* LgsVariable::bitAndIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitAndIR(runtime, other);
    }
    return LgsUnaryExpr::bitAndIR(runtime, other);
}

Value* LgsVariable::bitOrIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitOrIR(runtime, other);
    }
    return LgsUnaryExpr::bitOrIR(runtime, other);
}

Value* LgsVariable::bitXorIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitXorIR(runtime, other);
    }
    return LgsUnaryExpr::bitXorIR(runtime, other);
}

Value* LgsVariable::rshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->rshiftIR(runtime, other);
    }
    return LgsUnaryExpr::rshiftIR(runtime, other);
}

Value* LgsVariable::lshiftIR(LgsRuntime* runtime, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->lshiftIR(runtime, other);
    }
    return LgsUnaryExpr::lshiftIR(runtime, other);
}

json LgsVariable::asJSON() {
    json tree;
    tree["name"] = name;
    tree["exprType"] = "VARIABLE";
    tree["type"] = type->prettyName();
    return tree;
}

uint32_t LgsVariable::hashValue(LgsRuntime* runtime) {
    string text;
    switch (ref->type) {
    case FIELD:
        return ref->field->expr->hashValue(runtime);
    case ENUM_FIELD:
        return LgsStr::hashString(ref->enumField->name);
    default:
        assert(false);
    }
}