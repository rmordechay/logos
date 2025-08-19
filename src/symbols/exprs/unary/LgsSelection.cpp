#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsVariable.h"
#include "stmts/LgsField.h"
#include "types/LgsInterface.h"

LgsExpr* LgsSelection::lastExpr() const {
    assert(exprs.size() > 1);
    return exprs[exprs.size() - 1];
}

LgsExpr* LgsSelection::lastExprParent() const {
    return exprs[exprs.size() - 2];
}

std::string LgsSelection::pname() {
    std::stringstream str;
    str << exprs[0]->pname();
    for (int i = 1; i < exprs.size(); ++i) {
        str << '.' << exprs[i]->pname();
    }
    return str.str();
}

Value* LgsSelection::hash(LgsCodeGen* codeGen) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hash(codeGen);
}

void LgsSelection::createIRValue(LgsCodeGen* codeGen) {
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
            field->parentIRType = parentExpr->type->getIRType(codeGen);
            field->parentIRValue = parentExpr->getIRValue(codeGen);
            if (i > 0) {
                field->parentIRValue = codeGen->builder.CreateLoad(codeGen->ptrTy(), field->parentIRValue);
            }
            const auto fieldIR = field->getIRValue(codeGen);
            childExpr->setIRValue(fieldIR);
        } else {
            childExpr->createIRValue(codeGen);
        }
    }
    IRValue = lastExpr()->getIRValue(codeGen);
}

json::value_ref LgsSelection::asJSON() {
    json::object obj;
    auto parts = json::array();
    for (const auto& expr : exprs) {
        parts.emplace_back(expr->asJSON());
    }
    obj["parts"] = parts;
    obj["type"] = type->asJSON();
    return obj;
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        // TODO delete
        // delete expr;
    }
    exprs.clear();
}
