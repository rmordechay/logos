#ifndef LGSSYSCALL_H
#define LGSSYSCALL_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsInt.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsSysExitFunc final : public LgsMethodImpl {
public:
    explicit LgsSysExitFunc(const string& parentName) : LgsMethodImpl("exit", &LGS_VOID, parentName, {LgsParam(&LGS_INT)}) {
        IRFuncType = FunctionType::get(voidTy, {i32Ty}, false);
        isStatic = true;
        isPublic = true;
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
