#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

LgsInstance* getSingleton(LgsExpr* expr) {
    const auto parentAsVar = expr->asVariable();
    if (parentAsVar->ref.symbolType == OBJECT && parentAsVar->ref.object->singleton) {
        return parentAsVar->ref.object->singleton;
    }
    return nullptr;
}

Value* LgsSelection::createIRValue(LgsCodeGen* codeGen) {
    return resolveSelection(codeGen);
}

void LgsSelection::createIRStmt(LgsCodeGen* codeGen) {
    resolveSelection(codeGen);
}

Value* LgsSelection::resolveSelection(LgsCodeGen* codeGen) {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        const auto singleton = getSingleton(parentExpr);
        if (i == 0 && singleton) {
            parentExpr = singleton;
        }
        if (childExpr->asFuncCall()) {
            childExpr->getIRValue(codeGen);
        } else if (const auto fieldVar = childExpr->asVariable()){
            const auto v = fieldVar->ref.field->getIRValue(codeGen, parentExpr->type->vtable);
            childExpr->setIRValue(v);
        } else {
            assert(0);
        }
    }
    IRValue = lastExpr()->getIRValue(codeGen);
    return IRValue;
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
    assert(exprs.size() > 1);
    return exprs[exprs.size() - 1];
}

Value* LgsSelection::hashValue(LgsCodeGen* codeGen) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(codeGen);
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
