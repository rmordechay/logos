#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

Value* LgsSelection::createIRValue(LgsCodeGen* codeGen) {
    return resolveSelection(codeGen);
}

void LgsSelection::createIRStmt(LgsCodeGen* codeGen) {
    resolveSelection(codeGen);
}

Value* LgsSelection::resolveSelection(LgsCodeGen* codeGen) {
    auto startIndex = 0;
    const auto parentAsVar = exprs.front()->asVariable();
    if (parentAsVar && parentAsVar->ref.symbolType == OBJECT) {
        exprs.front() = parentAsVar->ref.object->singleton;
        startIndex = 1;
    }
    for (int i = startIndex; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            const auto field = parentExpr->type->getField(var->name);
            Value* v;
            if (i == 0) {
                v = parentExpr->getIRValue(codeGen);
            } else {
                v = codeGen->builder.CreateLoad(codeGen->ptrTy(), parentExpr->getIRValue(codeGen));
            }
            childExpr->setIRValue(field->getGEP(codeGen, v));
        } else {
            childExpr->getIRValue(codeGen);
        }
    }
    IRValue = lastExpr()->getIRValue(codeGen);
    return IRValue;
}

std::string LgsSelection::prettyName() {
    std::stringstream str;
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
