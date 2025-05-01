#ifndef LGSSYSCALL_H
#define LGSSYSCALL_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsSysExitFunc final : public LgsMethodImpl {
public:
    explicit LgsSysExitFunc(const string& parentName) : LgsMethodImpl("exit", &LGS_VOID, parentName, {LgsParam(&LGS_INT)}) {
        IRFuncType = FunctionType::get(voidTy, {i32Ty}, false);
        isStatic = true;
        isPublic = true;
    }

    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) override {
        const auto exitCode = args[1]->getIRValue(metadata);
        const auto exitFunc = metadata->module->getOrInsertFunction("exit", IRFuncType);
        return metadata->builder.CreateCall(exitFunc, {exitCode});
    }
};

class LgsSys final : public LgsObject {
public:
    static constexpr auto name = "Sys";
    LgsSysExitFunc exitFunc = LgsSysExitFunc(name);

    explicit LgsSys() : LgsObject(name) {
        addMethod(&exitFunc);
    }
};

#endif //LGSSYSCALL_H
