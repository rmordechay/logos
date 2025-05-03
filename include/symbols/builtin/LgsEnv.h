#ifndef LGSENVS_H
#define LGSENVS_H
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"

class LgsEnvGetFunc final : public LgsMethodImpl {
public:
    explicit LgsEnvGetFunc(const string& parentName) : LgsMethodImpl("get", &LGS_STR, parentName, {LgsParam(&LGS_STR), LgsParam(&LGS_STR)}) {
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
