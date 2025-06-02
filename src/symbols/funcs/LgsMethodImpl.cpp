#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

FunctionType* LgsMethodImpl::getIRFuncType(const Module* module) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        auto paramIRType = funcType.params[i]->type->getIRType();
        if (i == 0 && !funcType.isStatic) {
            IRParamsTypes.emplace_back(ptrTy);
        } else {
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    IRFuncType = FunctionType::get(funcType.rt->getIRType(), IRParamsTypes, funcType.isVariadic);
    return IRFuncType;
}

Function* LgsMethodImpl::getIRFunc(Module* module) {
    const auto funcIRType = getIRFuncType(module);
    auto func = module->getOrInsertFunction(funcType.getIRName(), funcIRType);
    const auto IRFunc = dyn_cast<Function>(func.getCallee());
    auto args = IRFunc->arg_begin();
    for (int i = 0; i < funcType.params.size(); ++i) {
        const auto param = funcType.params[i];
        if (param->isVariadic) {
            args++->setName("argc");
        } else {
            param->setIRValue(args);
        }
        if (param->expr) param->expr->setIRValue(args);
        args->setName(param->name);
        args++;
    }
    return IRFunc;
}