#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsArrayIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsMethodImpl.h"
#include "stmts/LgsField.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"

string LgsSelection::getName() {
    return "";
}

Value* LgsSelection::createIRValue(CodeGenMetadata* metadata) {
    return resolveSelection(metadata)->IRValue;
}

LgsExpr* LgsSelection::resolveSelection(CodeGenMetadata* metadata) const {
    for (int i = 0; i < exprs.size() - 1; ++i) {
        const auto parentExpr = exprs[i];
        const auto childExpr = exprs[i + 1];
        const auto field = parentExpr->type->getField(childExpr->getName());
        const auto parentIRValue = parentExpr->getIRValue(metadata);
        if (field) {
            const auto value = field->getGEP(metadata, parentIRValue);
            const auto valueLoad = metadata->builder.CreateLoad(field->type->getIRType(), value);
            childExpr->setIRValue(valueLoad);
            continue;
        }

        if (const auto methodCall = childExpr->asFuncCall()) {
            if (const auto interface = parentExpr->type->asInterface()) {
                dispatchInterfaceFunc(metadata, parentIRValue, methodCall, interface);
            } else {
                methodCall->initIRValue(metadata);
            }
        }
    }
    return lastExpr();
}

Value* LgsSelection::dispatchInterfaceFunc(CodeGenMetadata* metadata, Value* parentIRValue, const LgsFuncCall* methodCall, LgsInterface* interface) const {
    auto& builder = metadata->builder;
    const auto interfaceIRType = interface->getIRType();
    const auto interfaceGEP = builder.CreateStructGEP(interfaceIRType, parentIRValue, 0);
    const auto interfacePtr = builder.CreateLoad(ptrTy, interfaceGEP);
    if (!methodCall->func->IRFuncType) methodCall->func->setIRFuncType(metadata);
    return builder.CreateCall(methodCall->func->IRFuncType, interfacePtr, {parentIRValue});
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

uint32_t LgsSelection::hashValue(CodeGenMetadata* metadata) {
    const auto lgsExpr = lastExpr();
    return lgsExpr->hashValue(metadata);
}

Value* LgsSelection::eqIR(CodeGenMetadata* metadata, LgsExpr* other) {
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
