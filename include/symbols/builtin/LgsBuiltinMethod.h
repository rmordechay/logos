#ifndef LGSBUILTINFUNC_H
#define LGSBUILTINFUNC_H
#include "funcs/LgsFunc.h"
#include "funcs/LgsFuncImpl.h"
#include "funcs/LgsMethodImpl.h"

class LgsBuiltinMethod : public LgsMethodImpl {
public:
    LgsBuiltinMethod(const string& name, const string& parentName, LgsType* rt, const vector<LgsParam*>& params = {}): LgsMethodImpl(name, parentName, rt, params) {
        IRGenerated = true;
        funcType.isBuiltin = true;
    }
    ~LgsBuiltinMethod() override = default;
};

class LgsBuiltinFunc : public LgsFuncImpl {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt, const vector<LgsParam*>& params = {}): LgsFuncImpl(name, rt, params) {
        IRGenerated = true;
        funcType.isBuiltin = true;
    }
    ~LgsBuiltinFunc() override = default;
};

#endif //LGSBUILTINFUNC_H
