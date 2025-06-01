#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

FunctionType* LgsMethodImpl::getIRFuncType(const CodegenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < funcType.params.size(); ++i) {
        auto paramIRType = funcType.params[i]->type->getIRType();
        if (i == 0 && !funcType.isStatic) {
            IRParamsTypes.emplace_back(PointerType::get(paramIRType, 0));
        } else {
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    if (const auto obj = funcType.rt->asObject()) {
        IRParamsTypes.insert(IRParamsTypes.begin(), PointerType::get(obj->getIRType(), 0));
        IRFuncType = FunctionType::get(voidTy, IRParamsTypes, funcType.isVariadic);
    } else {
        IRFuncType = FunctionType::get(funcType.rt->getIRType(), IRParamsTypes, funcType.isVariadic);
    }
    return IRFuncType;
}
