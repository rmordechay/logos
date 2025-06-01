#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "types/LgsFuncType.h"

class LgsFuncImpl : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* rt, const vector<LgsParam*>& params = {}) {
        funcType.name = name;
        funcType.rt = rt;
        funcType.params = params;
    }

    explicit LgsFuncImpl(const LgsFuncType* funcType) {
        this->funcType.name = funcType->name;
        this->funcType.rt = funcType->rt;
        this->funcType.params = funcType->params;
    }
    ~LgsFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
