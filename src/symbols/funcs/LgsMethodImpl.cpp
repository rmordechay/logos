#include "funcs/LgsMethodImpl.h"
#include "funcs/LgsParam.h"
#include <types/LgsObject.h>

void LgsMethodImpl::setIRFunc(CodeGenMetadata* metadata) {
    // IRParamsTypes.emplace_back(ptrTy);
    for (int i = 0; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }

    const auto functionType = FunctionType::get(signature.type->getIRType(), IRParamsTypes, false);
    auto func = metadata->currentModule->getOrInsertFunction(signature.composedName, functionType);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (params.empty()) return;

    auto args = IRFunc->arg_begin();
    for (const auto& param : params) {
        param->setIRValue(args);
        args++->setName(param->name);
    }
}