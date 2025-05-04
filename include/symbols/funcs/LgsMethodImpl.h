#ifndef LOGOSMETHODIMPL_H
#define LOGOSMETHODIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"
#include "types/LgsMethodType.h"

class LgsMethodImpl : public LgsFunc {
public:
    string parentName;
    int vtableKey = -1;
    bool isPublic = false;
    bool isStatic = false;
    LgsMethodType methodType;
    LgsMethodImpl* implements = nullptr;

    LgsMethodImpl(const string& name, LgsType* funcType, const string& parentName, const vector<LgsParam>& params = {}) : parentName(parentName), methodType(LgsMethodType(name, funcType, params)) {}
    bool equals(const LgsFuncCall* other) override;
    LgsFuncType* getFuncType() override;
    ~LgsMethodImpl() override = default;
};

#endif //LOGOSMETHODIMPL_H
