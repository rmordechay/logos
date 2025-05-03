#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"

class LgsFuncImpl : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* funcType) : LgsFunc(name, funcType) {}
    explicit LgsFuncImpl(const string& name, LgsType* funcType, const vector<LgsParam>& params) : LgsFunc(name, funcType, params) {}
    bool equals(const LgsFuncCall* other) override;
    ~LgsFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
