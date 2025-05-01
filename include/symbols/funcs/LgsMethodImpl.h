#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsMethodImpl : public LgsFunc {
public:
    string parentName;
    int vtableKey = -1;
    bool isPublic = false;
    bool isStatic = false;
    LgsMethodImpl* implements = nullptr;

    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName) : LgsFunc(name, funcType), parentName(parentName) {}
    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam>& params) : LgsFunc(name, funcType, params), parentName(parentName) {}
    void setIRName() override;
    void setIRFuncType(const CodeGenMetadata* metadata) override;
    void setIRFuncParams(Argument* args) override;
    bool equals(const LgsFuncCall* other) override;
    bool equals(const LgsFunc* other) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
