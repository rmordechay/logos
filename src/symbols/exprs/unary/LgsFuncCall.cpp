#include "exprs/unary/LgsFuncCall.h"
#include "builtin/LgsPrint.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

Value* LgsFuncCall::call(CodeGenMetadata* metadata) const {
    if (func->funcType.isVirtual) {
        const auto virtualFunc = resolveVirtualFunc(metadata);
        func->setIRValue(virtualFunc);
    } else if (ref) {
        if (ref->type == PARAM) {
            func->setIRValue(ref->param->IRValue);
        } else if (ref->type == VAR_DEC) {
            func->setIRValue(ref->varDec->IRValue);
        } else if (ref->type == FUNC) {
            assert(false);
        }
    }
    return func->call(metadata, args);
}

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

void LgsFuncCall::createIRStmt(CodeGenMetadata* metadata) {
    call(metadata);
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return call(metadata);
}

Value* LgsFuncCall::resolveVirtualFunc(CodeGenMetadata* metadata) const {
    auto& builder = metadata->builder;
    const auto parent = args[0];
    const auto type = getParentIRType(parent);
    const auto interface = type->asInterface();
    const auto parentIRValue = parent->getIRValue(metadata);

    const auto keyIR = getIRStr(metadata->module, func->funcType.getIRName());
    const auto mapPtr = builder.CreateLoad(ptrTy, parentIRValue);
    const auto rv = interface->vtable.mapType.get.makeCall(metadata, {mapPtr, keyIR});
    const auto getValuePtr = builder.CreateAlloca(ptrTy);
    builder.CreateStore(rv, getValuePtr);
    return builder.CreateLoad(ptrTy, builder.CreateLoad(ptrTy, getValuePtr));
}

LgsType* LgsFuncCall::getParentIRType(LgsExpr* parent) const {
    if (const auto var = parent->asVariable()) {
        switch (var->ref->type) {
        case PARAM:
            return var->ref->param->type;
        default:
            break;
        }
    }
    assert(false);
}

string LgsFuncCall::getAsStr() const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = func->funcType.isMethod; i < args.size(); ++i) {
        strStream << args[i]->type->prettyName();
        if (i != args.size() - 1) strStream << ", ";
    }
    strStream << ")";
    return strStream.str();
}

LgsFuncCall::~LgsFuncCall() {
    // First arg of method is not freed here
    const auto indexStart = !!dynamic_cast<LgsMethodImpl*>(func);
    for (int i = indexStart; i < args.size(); ++i) {
        delete args[i];
    }
}
