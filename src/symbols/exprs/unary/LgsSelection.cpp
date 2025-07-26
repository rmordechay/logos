#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"
#include "utils/LgsIRUtils.h"

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
        if (i == 0) {

        }
        if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->getIRValue(module);
        } else {
            resolveFieldSelection(module, parentExpr, childExpr->asVariable());
        }
    }
}

void LgsSelection::resolveFieldSelection(LgsModule* module, LgsExpr* parentExpr, LgsVariable* fieldVar) {
    const auto field = parentExpr->type->getField(fieldVar->name);
    Value* value = nullptr;
    if (field->type->asEnum()) {
        value = field->expr ? field->expr->getIRValue(module) : getIRStr(module, field->name);
    } else if (field->isVirtual) {
        value = resolveVirtualField(module, parentExpr, field);
    } else {
        value = field->getGEP(module);
    }
    fieldVar->setIRValue(value);
}

Value* LgsSelection::resolveVirtualField(LgsModule* module, LgsExpr* parentExpr, const LgsField* field) {
    const auto vtable = parentExpr->type->vtable;
    const auto fieldIRType = field->type->getIRType(module);
    const auto vtableMap = vtable->type->asMap();
    const auto keyIR = getIRStr(module, field->name);
    const auto parentIRValue = parentExpr->getIRValue(module);
    const auto vtableIRType = vtable->type->getIRType(module);
    const auto mapPtr = module->builder.CreateGEP(vtableIRType, parentIRValue, {i64(module, 0)});
    const auto rv = vtableMap->getFunc.callIR(module, {mapPtr, keyIR});
    return module->builder.CreateLoad(fieldIRType, rv);
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
