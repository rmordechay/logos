#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"
#include "types/LgsObject.h"

class LgsFuncImpl final : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* funcType, const vector<LgsParam>& params = {}) : LgsFunc(name, funcType, params) {}
    vector<Type*> getIRParamTypes(const CodeGenMetadata* metadata) override;
    ~LgsFuncImpl() override = default;
};

inline vector<Type*> LgsFuncImpl::getIRParamTypes(const CodeGenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
    for (int i = 0; i < signature.params.size(); ++i) {
        const auto param = signature.params[i];
        if (param.func) {
            const auto rty = param.func->signature.type->getIRType();
            const auto funcType = FunctionType::get(rty, param.func->getIRParamTypes(metadata), false);
            IRParamsTypes.emplace_back(funcType->getPointerTo());
        } else {
            const auto type = param.type;
            auto paramIRType = type->getIRType();
            if (dynamic_cast<LgsObject*>(type)) {
                paramIRType = paramIRType->getPointerTo();
            }
            IRParamsTypes.emplace_back(paramIRType);
        }
    }
    return IRParamsTypes;
}

#endif //LOGOSFUNCIMPL_H
