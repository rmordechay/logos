#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"

string LgsSelection::getName() {
    return "";
}

void LgsSelection::createIRStmt(CodegenMetadata* metadata) {
    resolveSelection(metadata);
}

Value* LgsSelection::createIRValue(CodegenMetadata* metadata) {
    return resolveSelection(metadata)->IRValue;
}

LgsExpr* LgsSelection::resolveSelection(CodegenMetadata* metadata) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        const auto field = parentExpr->type->getField(childExpr->getName());
        if (field) {
            if (const auto iterIndex = parentExpr->asIterIndex()) {
                const auto gep = iterIndex->getGEP(metadata);
                auto valueLoad = metadata->builder.CreateLoad(ptrTy, gep);
                const auto value = field->getGEP(metadata, valueLoad);
                valueLoad = metadata->builder.CreateLoad(field->type->getIRType(), value);
                childExpr->setIRValue(valueLoad);
            } else {
                const auto parentIRValue = parentExpr->getIRValue(metadata);
                const auto value = field->getGEP(metadata, parentIRValue);
                const auto valueLoad = metadata->builder.CreateLoad(field->type->getIRType(), value);
                childExpr->setIRValue(valueLoad);
            }
        } else if (const auto methodCall = childExpr->asFuncCall()) {
            methodCall->IRValue = methodCall->createIRValue(metadata);
        }
    }
    return lastExpr();
}

json LgsSelection::asJSON() {
    json tree;
    tree["exprs"] = {};
    tree["exprType"] = "SELECTION";
    for (const auto& expr : exprs) {
        tree["exprs"].emplace_back(expr->asJSON());
    }
    return tree;
}

LgsExpr* LgsSelection::lastExpr() const {
    if (exprs.empty()) return nullptr;
    return exprs[exprs.size() - 1];
}

uint32_t LgsSelection::hashValue(CodegenMetadata* metadata) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(metadata);
}

Value* LgsSelection::eqIR(CodegenMetadata* metadata, LgsExpr* other) {
    const auto selection = resolveSelection(metadata);
    if (const auto var = selection->asVariable()) {
        return var->eqIR(metadata, other);
    }
    return nullptr;
}

LgsSelection::~LgsSelection() {
    for (const auto& expr : exprs) {
        delete expr;
    }
}
