#include "LgsUtils.h"

#include "LgsDefinitions.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsField.h"
#include "stmts/LgsVarDec.h"

string getBaseStr(LgsExpr* baseExpr) {
    if (const auto strConst = baseExpr->asStrConst()) {
        return strConst->value;
    }
    if (const auto var = baseExpr->asVariable()) {
        switch (var->ref->type) {
        case VAR_DEC:
            return var->ref->varDec->expr->asStrConst()->value;
        default:
            break;
        }
    }
    assert(false);
}

int getExprConstNumber(LgsExpr* expr) {
    if (const auto asInt = expr->asIntConst()) {
        return asInt->value;
    }
    if (const auto var = expr->asVariable()) {
        switch (var->ref->type) {
        case VAR_DEC:
            return getExprConstNumber(var->ref->varDec->expr);
        case FIELD:
            return getExprConstNumber(var->ref->field->expr);
        default:
            break;
        }
    }
    return -1;
}

void replaceNextPlaceholder(string& str, const LgsExpr* expr) {
    const auto pos = str.find(LOGOS_STR_FORMAT_PART);
    if (pos == string::npos) return;
    if (expr->type->asBool()) {

    }
    str.replace(pos, 2, expr->getStrFormatPart());
}