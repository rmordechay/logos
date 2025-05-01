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

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        const auto key = args[1]->asStrConst()->value;
        string value;
        const auto envVar = activeEnv.envVars.find(key);
        if (envVar != activeEnv.envVars.end()) {
            value = envVar->second;
        } else {
            value = args[2]->asStrConst()->value;
        }
        return createIRStr(metadata->module, value);
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
