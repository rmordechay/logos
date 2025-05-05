#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsFunc.h"
#include "LgsParam.h"
#include "types/LgsFuncType.h"

class LgsFuncImpl : public LgsFunc {
public:
    LgsFuncType funcType;

    LgsFuncImpl() = default;
    explicit LgsFuncImpl(const string& name, LgsType* rt) {
        funcType.name = name;
        funcType.rt = rt;
    }
    bool equals(const LgsFuncCall* other) override;
    LgsFuncType* getFuncType() override;
    ~LgsFuncImpl() override = default;
};

#endif //LOGOSFUNCIMPL_H
