#ifndef LGSENVS_H
#define LGSENVS_H
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

class LgsEnvGetFunc final : public LgsMethodImpl {
public:
    LgsStr rt;

    explicit LgsEnvGetFunc(const string& parentName) : LgsMethodImpl("get", &rt, parentName, {LgsParam(new LgsStr()), LgsParam(new LgsStr())}) {
        IRFuncType = FunctionType::get(ptrTy, {ptrTy, ptrTy}, false);
        isStatic = true;
        isPublic = true;
    }
};

class LgsEnv final : public LgsObject {
public:
    static constexpr auto name = "Env";
    LgsEnvGetFunc getFunc = LgsEnvGetFunc(name);

    explicit LgsEnv(): LgsObject(name) {
        addMethod(&getFunc);
    }
};


#endif //LGSENVS_H
