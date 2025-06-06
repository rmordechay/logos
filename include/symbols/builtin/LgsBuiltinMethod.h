#ifndef LGSBUILTINFUNC_H
#define LGSBUILTINFUNC_H
#include "funcs/LgsFunc.h"


class LgsBuiltinMethod : public LgsFunc {
public:
    LgsBuiltinMethod(const string& name, const string& parentName, LgsType* rt, const vector<LgsParam*>& params = {}): LgsFunc(name, rt, params) {
        funcType.parentName = parentName;
        funcType.isBuiltin = true;
    }
    ~LgsBuiltinMethod() override = default;
};

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt, const vector<LgsParam*>& params = {}): LgsFunc(name, rt, params) {
        funcType.isBuiltin = true;
    }
    ~LgsBuiltinFunc() override = default;
};

#endif //LGSBUILTINFUNC_H
