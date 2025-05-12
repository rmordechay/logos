#include "exprs/unary/LgsFuncCall.h"

#include "builtin/LgsPrint.h"
#include "exprs/unary/LgsVariable.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"


Value* LgsFuncCall::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) const {
    if (func->funcType.isVirtual) {
        const auto virtualFunc = resolveVirtualFunc(metadata, args);
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

Value* LgsFuncCall::resolveVirtualFunc(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) const {
    auto& builder = metadata->builder;
    const auto parent = args[0];
    const auto type = getParentIRType(parent);
    const auto interface = type->asInterface();
    const auto parentIRValue = parent->getIRValue(metadata);

    const auto keyIR = createIRStr(metadata->module, name);
    const auto mapPtr = builder.CreateLoad(ptrTy, parentIRValue);
    const auto rv = interface->vtable.mapType.get.makeCall(metadata, {mapPtr, keyIR});
    const auto getValuePtr = builder.CreateAlloca(ptrTy);
    builder.CreateStore(rv, getValuePtr);
    return builder.CreateLoad(ptrTy, builder.CreateLoad(ptrTy, getValuePtr));
}

LgsType* LgsFuncCall::getParentIRType(LgsExpr* parent) const {
    LgsType* type = nullptr;
    if (const auto var = parent->asVariable()) {
        switch (var->ref->type) {
        case VAR_DEC:
            assert(false);
        case PARAM:
            type = var->ref->param->type;
            break;
        default:
            assert(false);
        }
    }
    return type;
}

string LgsFuncCall::getIRName() const {
    vector<string> paramTypeNames;
    for (const auto& arg : args) {
        paramTypeNames.emplace_back(arg->type->getIRName());
    }
    return LgsFuncType::getComposedName(name, "", paramTypeNames);
}

string LgsFuncCall::getName() {
    return name;
}

string LgsFuncCall::format(string& indentStr) {
    return indentStr + name + "()";
}

void LgsFuncCall::createIRStmt(CodeGenMetadata* metadata) {
    call(metadata, args);
}

Value* LgsFuncCall::createIRValue(CodeGenMetadata* metadata) {
    return call(metadata, args);
}

string LgsFuncCall::getText() const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = isMethodCall; i < args.size(); ++i) {
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
