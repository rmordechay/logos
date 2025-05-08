#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsData.h"
#include "LgsFunc.h"
#include "LgsParam.h"
#include "types/LgsFuncType.h"
#include "types/LgsInt.h"

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

class LgsMainFunc final : public LgsFuncImpl {
public:
    vector<char*> args;

    explicit LgsMainFunc() {
        funcType.name = LOGOS_MAIN_FUNC;
        funcType.rt = &LGS_INT;
    }
    void setArgs(const vector<char*>& args);
    ~LgsMainFunc() override = default;
};

#endif //LOGOSFUNCIMPL_H
