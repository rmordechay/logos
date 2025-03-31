#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsMethodImpl final : public LgsFunc {
public:
    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params) {
        signature.parentName = parentName;
        setComposedName();
    }
    void setIRFuncType() override;
    ~LgsMethodImpl() override = default;
};

inline void LgsMethodImpl::setIRFuncType() {
    IRParamsTypes.emplace_back(ptrTy);
    for (int i = 1; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    IRFuncType = FunctionType::get(signature.rt->getIRType(), IRParamsTypes, false);
}

#endif //LOGOSMETHODIMPL_H
