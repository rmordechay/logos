#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/LgsEnumField.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsStr.h"
#include <LgsStack.h>

string LgsVariable::getName() {
    return name;
}

Value* LgsVariable::createIRValue(CodeGenMetadata* metadata) {
    assert(ref);
    switch (ref->type) {
    case VAR_DEC:
        return ref->varDec->expr->getIRValue(metadata);
    case PARAM:
        return ref->param->IRValue;
    case ENUM_FIELD:
        return ref->enumField->getGEP(metadata);
    case FUNC:
        // TODO incorrect call, should return function ptr
        return ref->func[0]->call(metadata);
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

json LgsVariable::asJSON() {
    json tree;
    tree["name"] = name;
    tree["exprType"] = "VARIABLE";
    tree["type"] = type->getName();
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
