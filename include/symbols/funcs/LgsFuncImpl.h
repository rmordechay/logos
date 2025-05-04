#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsFuncImpl : public LgsFunc {
public:
    LgsFuncType funcType;

    explicit LgsFuncImpl(const string& name, LgsType* rt, const vector<LgsParam>& params = {}) : funcType(LgsFuncType(name, rt, params)) {}
    bool equals(const LgsFuncCall* other) override;
    LgsFuncType* getFuncType() override;
    ~LgsFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
