#ifndef LOGOSBUILTINFUNC_H
#define LOGOSBUILTINFUNC_H
#include "LgsFunc.h"

class LgsBuiltinFunc : public LgsFunc {
public:
    LgsBuiltinFunc(const string& name, LgsType* funcType) : LgsFunc(name, funcType) {}
    ~LgsBuiltinFunc() override = default;
};

#endif //LOGOSBUILTINFUNC_H
