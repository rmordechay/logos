#ifndef LGSENVS_H
#define LGSENVS_H

#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsEnvGetFunc final : public LgsMethodImpl {
public:
    static constexpr auto name = "Env";

    explicit LgsEnvGetFunc(LgsType* parentType) : LgsMethodImpl("get", new LgsStr(), name, {new LgsParam(parentType), new LgsParam(new LgsStr())}) {
        IRFuncType = FunctionType::get(ptrTy, {ptrTy, ptrTy}, false);
        signature.isStatic = true;
    }

    void createIRValue(CodeGenMetadata* metadata) override {
        assert(false);
    }
};

class LgsEnv final : public LgsObject {
public:
    static constexpr auto name = "Env";
    LgsEnvGetFunc getFunc = LgsEnvGetFunc(this);

    explicit LgsEnv() : LgsObject(name) {
        setGetFunc();
    }

    void setGetFunc() {
        methods[getFunc.signature.name] = {&getFunc};
    }
};

#endif //LGSENVS_H
