#ifndef LOGOSFUNCIMPL_H
#define LOGOSFUNCIMPL_H
#include "LgsDefinitions.h"
#include "LgsFunc.h"
#include "types/LgsFuncType.h"
#include "types/primitives/LgsInt.h"

class LgsFuncImpl : public LgsFunc {
public:
    explicit LgsFuncImpl(const string& name, LgsType* rt) {
        funcType.name = name;
        funcType.rt = rt;
    }

    explicit LgsFuncImpl(const LgsFuncType* funcType) {
        this->funcType.name = funcType->name;
        this->funcType.rt = funcType->rt;
        this->funcType.params = funcType->params;
    }
    ~LgsFuncImpl() override = default;
};

class LgsMainFunc final : public LgsFuncImpl {
public:
    vector<char*> args;

    explicit LgsMainFunc() : LgsFuncImpl(LOGOS_MAIN_FUNC, &LGS_INT) {}
    void setArgs(const vector<char*>& args);
    ~LgsMainFunc() override = default;
};

#endif //LOGOSFUNCIMPL_H
