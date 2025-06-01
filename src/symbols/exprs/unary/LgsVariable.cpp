#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "types/str/LgsStr.h"
#include <logos/LgsRuntime.h>

string LgsVariable::getName() {
    return name;
}

string LgsVariable::prettyName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->IRValue;
    case PARAM:
        return ref->param->getIRValue(metadata);
    case ENUM_FIELD:
        return ref->enumField->getGEP(metadata);
    case FUNC:
        return ref->func->getIRFunc(metadata);
    default:
        assert(false);
    }
}

Value* LgsVariable::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->eqIR(metadata, other);
    }
    return LgsUnaryExpr::eqIR(metadata, other);
}

Value* LgsVariable::neIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->neIR(metadata, other);
    }
    return LgsUnaryExpr::neIR(metadata, other);
}

Value* LgsVariable::gtIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->gtIR(metadata, other);
    }
    return LgsUnaryExpr::gtIR(metadata, other);
}

Value* LgsVariable::ltIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->ltIR(metadata, other);
    }
    return LgsUnaryExpr::gtIR(metadata, other);
}

Value* LgsVariable::geIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->geIR(metadata, other);
    }
    return LgsUnaryExpr::geIR(metadata, other);
}

Value* LgsVariable::leIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->leIR(metadata, other);
    }
    return LgsUnaryExpr::leIR(metadata, other);
}

Value* LgsVariable::bitAndIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitAndIR(metadata, other);
    }
    return LgsUnaryExpr::bitAndIR(metadata, other);
}

Value* LgsVariable::bitOrIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitOrIR(metadata, other);
    }
    return LgsUnaryExpr::bitOrIR(metadata, other);
}

Value* LgsVariable::bitXorIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitXorIR(metadata, other);
    }
    return LgsUnaryExpr::bitXorIR(metadata, other);
}

Value* LgsVariable::rshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->rshiftIR(metadata, other);
    }
    return LgsUnaryExpr::rshiftIR(metadata, other);
}

Value* LgsVariable::lshiftIR(CodeGenMetadata* metadata, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->lshiftIR(metadata, other);
    }
    return LgsUnaryExpr::lshiftIR(metadata, other);
}

json LgsVariable::asJSON() {
    json tree;
    tree["name"] = name;
    tree["exprType"] = "VARIABLE";
    tree["type"] = type->prettyName();
    return tree;
}

uint32_t LgsVariable::hashValue(CodeGenMetadata* metadata) {
    string text;
    switch (ref->type) {
    case FIELD:
        return ref->field->expr->hashValue(metadata);
    case ENUM_FIELD:
        return LgsStr::hashString(ref->enumField->name);
    default:
        assert(false);
    }
}

Value* LgsVariable::getLength(CodeGenMetadata* metadata) {
    switch (ref->type) {
    case VAR_DEC:
        return type->asIterable()->getLength(metadata, ref->varDec->IRValue);
    case PARAM: {
        return type->asIterable()->getLength(metadata, ref->param->IRValue);
    }
    default:
        assert(false);
    }
}
