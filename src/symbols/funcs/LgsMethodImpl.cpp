#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

FunctionType* LgsMethodImpl::getIRFuncType(const CodeGenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        auto paramIRType = funcType.params[i]->type->getIRType();
        if (i == 0 && !funcType.isStatic) {
            IRParamsTypes.emplace_back(paramIRType->getPointerTo());
        } else {
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    if (const auto obj = funcType.rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), obj->getIRType()->getPointerTo());
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, false);
    } else {
        IRFuncType = FunctionType::get(funcType.rt->getIRType(), IRParamsTypes, false);
    }
    return IRFuncType;
}