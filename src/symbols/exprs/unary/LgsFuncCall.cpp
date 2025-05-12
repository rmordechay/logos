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
        func->setIRValue(ref->getIRValue());
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
    const auto type = parent->type;
    const auto interface = type->asInterface();
    const auto parentIRValue = parent->getIRValue(metadata);

    const auto keyIR = getIRStr(metadata->module, func->funcType.getIRName());
    const auto mapPtr = builder.CreateLoad(ptrTy, parentIRValue);
    const auto rv = interface->vtable.mapType.get.callIR(metadata, {mapPtr, keyIR});
    const auto getValuePtr = builder.CreateAlloca(ptrTy);
    builder.CreateStore(rv, getValuePtr);
    return builder.CreateLoad(ptrTy, builder.CreateLoad(ptrTy, getValuePtr));
}

string LgsFuncCall::getAsStr() const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < args.size(); ++i) {
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
