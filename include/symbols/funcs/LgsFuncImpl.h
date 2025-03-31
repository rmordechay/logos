#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsFuncImpl final : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* funcType, const vector<LgsParam*>& params = {}) : LgsFunc(name, funcType, params) {
        setComposedName();
    }
    void setIRFuncType() override;
    ~LgsFuncImpl() override = default;
};

inline void LgsFuncImpl::setIRFuncType() {
    for (int i = 0; i < params.size(); ++i) {
        auto paramIRType = params[i]->type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    IRFuncType = FunctionType::get(signature.rt->getIRType(), IRParamsTypes, false);
}

#endif //LOGOSFUNCIMPL_H
