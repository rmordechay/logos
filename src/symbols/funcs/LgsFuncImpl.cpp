#include "funcs/LgsFuncImpl.h"

#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"

#include <LgsStack.h>
#include <types/LgsInt.h>

void LgsFuncImpl::setIRFunc(CodeGenMetadata* metadata) {
    for (int i = 0; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto rt = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    IRFunc = Function::Create(rt, Function::ExternalLinkage, signature.composedName, metadata->currentModule);
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
    }
}
