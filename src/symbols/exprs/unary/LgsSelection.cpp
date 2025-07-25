#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

void LgsSelection::createIRStmt(LgsModule* module) {
    resolveSelection(module);
}

Value* LgsSelection::createIRValue(LgsModule* module) {
    resolveSelection(module);
    return lastExpr()->IRValue;
}

void LgsSelection::resolveSelection(LgsModule* module) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->getIRValue(module);
        } else {
            resolveFieldSelection(module, parentExpr, childExpr);
        }
    }
}

void LgsSelection::resolveFieldSelection(LgsModule* module, LgsExpr* parentExpr, LgsUnaryExpr* childExpr) {
    const auto field = parentExpr->type->getField(childExpr->getExprName());
    const auto fieldIRType = field->type->getIRType(module);
    Value* value = nullptr;
    if (field->type->asEnum()) {
        value = field->expr ? field->expr->getIRValue(module) : getIRStr(module, field->name);
    } else if (field->isVirtual) {
        const auto vtable = parentExpr->type->vtable;
        const auto vtableMap = vtable->type->asMap();
        const auto keyIR = getIRStr(module, field->name);
        const auto parentIRValue = parentExpr->getIRValue(module);
        const auto vtableIRType = vtable->type->getIRType(module);
        const auto mapPtr = module->builder.CreateGEP(vtableIRType, parentIRValue, {i64(module, 0)});
        auto rv = vtableMap->getFunc.callIR(module, {mapPtr, keyIR});
        rv = module->builder.CreateLoad(fieldIRType, rv);
        value = rv;
    } else {
        value = field->getGEP(module);
        // value = module->builder.CreateLoad(field->type->getIRType(module), value);
    }
    childExpr->setIRValue(value);
}

string LgsSelection::prettyName() {
    stringstream str;
    str << exprs[0]->prettyName();
    for (int i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->prettyName();
    }
    return str.str();
}

LgsExpr* LgsSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

Value* LgsSelection::hashValue(LgsModule* module) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(module);
}

Value* LgsSelection::eqIR(LgsModule* module, LgsExpr* other) {
    resolveSelection(module);
    const auto selection = lastExpr();
    if (const auto var = selection->asVariable()) {
        return var->eqIR(module, other);
    }
    return nullptr;
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
