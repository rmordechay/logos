#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsMethodImpl : public LgsFunc {
public:
    bool isPublic = false;
    string filePath;

    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam>& params = {}) : LgsFunc(name, funcType, params, parentName) {}
    vector<Type*> getIRParamTypes(const CodeGenMetadata* metadata) override;
    ~LgsMethodImpl() override = default;
};

inline vector<Type*> LgsMethodImpl::getIRParamTypes(const CodeGenMetadata* metadata) {
    vector<Type*> IRParamsTypes;
    for (int i = 1; i < signature.params.size(); ++i) {
        auto paramIRType = signature.params[i].type->getIRType();
        IRParamsTypes.emplace_back(paramIRType);
    }
    return IRParamsTypes;
}

#endif //LOGOSMETHODIMPL_H
