#ifndef LGSENVS_H
#define LGSENVS_H

#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsEnvGetFunc final : public LgsMethodImpl {
public:
    static constexpr auto name = "Env";

    explicit LgsEnvGetFunc(LgsType* parentType) : LgsMethodImpl("get", new LgsStr(), name, {LgsParam(parentType), LgsParam(new LgsStr()), LgsParam(new LgsStr())}) {
        IRFuncType = FunctionType::get(ptrTy, {ptrTy, ptrTy}, false);
        signature.isStatic = true;
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
    LgsEnvGetFunc getFunc = LgsEnvGetFunc(this);

    explicit LgsEnv() : LgsObject(name) {
        methods[getFunc.signature.name] = {&getFunc};
    }
};

#endif //LGSENVS_H
