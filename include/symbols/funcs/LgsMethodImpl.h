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
    bool equals(const LgsFuncCall* other) override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
