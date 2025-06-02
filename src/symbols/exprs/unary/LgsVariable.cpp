#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
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

Value* LgsVariable::createIRValue(Module* module) {
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->IRValue;
    case PARAM:
        return ref->param->getIRValue(module);
    case ENUM_FIELD:
        return ref->enumField->getGEP(module);
    case FUNC:
        return ref->func->getIRFunc(module);
    default:
        assert(false);
    }
}

Value* LgsVariable::eqIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->eqIR(module, other);
    }
    return LgsUnaryExpr::eqIR(module, other);
}

Value* LgsVariable::neIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->neIR(module, other);
    }
    return LgsUnaryExpr::neIR(module, other);
}

Value* LgsVariable::gtIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->gtIR(module, other);
    }
    return LgsUnaryExpr::gtIR(module, other);
}

Value* LgsVariable::ltIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->ltIR(module, other);
    }
    return LgsUnaryExpr::gtIR(module, other);
}

Value* LgsVariable::geIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->geIR(module, other);
    }
    return LgsUnaryExpr::geIR(module, other);
}

Value* LgsVariable::leIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->leIR(module, other);
    }
    return LgsUnaryExpr::leIR(module, other);
}

Value* LgsVariable::bitAndIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitAndIR(module, other);
    }
    return LgsUnaryExpr::bitAndIR(module, other);
}

Value* LgsVariable::bitOrIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitOrIR(module, other);
    }
    return LgsUnaryExpr::bitOrIR(module, other);
}

Value* LgsVariable::bitXorIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->bitXorIR(module, other);
    }
    return LgsUnaryExpr::bitXorIR(module, other);
}

Value* LgsVariable::rshiftIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->rshiftIR(module, other);
    }
    return LgsUnaryExpr::rshiftIR(module, other);
}

Value* LgsVariable::lshiftIR(Module* module, LgsExpr* other) {
    if (ref->type == VAR_DEC) {
        return ref->varDec->expr->lshiftIR(module, other);
    }
    return LgsUnaryExpr::lshiftIR(module, other);
}

json LgsVariable::asJSON() {
    json tree;
    tree["name"] = name;
    tree["exprType"] = "VARIABLE";
    tree["type"] = type->prettyName();
    return tree;
}

uint32_t LgsVariable::hashValue(Module* module) {
    string text;
    switch (ref->type) {
    case FIELD:
        return ref->field->expr->hashValue(module);
    case ENUM_FIELD:
        return LgsStr::hashString(ref->enumField->name);
    default:
        assert(false);
    }
}

Value* LgsVariable::getLength(Module* module) {
    switch (ref->type) {
    case VAR_DEC:
        return type->asIterable()->getLength(module, ref->varDec->IRValue);
    case PARAM: {
        return type->asIterable()->getLength(module, ref->param->IRValue);
    }
    default:
        assert(false);
    }
}
