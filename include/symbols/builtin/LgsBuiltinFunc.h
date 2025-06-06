#ifndef LGSBUILTINFUNC_H
#define LGSBUILTINFUNC_H
#include "funcs/LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* rt, const string& parentName, const vector<LgsParam*>& params = {}): LgsFunc(name, rt, params) {
        funcType.isBuiltin = true;
        if (parentName != "") {
            funcType.parentName = parentName;
            funcType.isMethod = true;
        }
    }
    ~LgsBuiltinFunc() override = default;
};

#endif //LGSBUILTINFUNC_H
