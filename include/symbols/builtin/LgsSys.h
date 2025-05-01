#ifndef LGSSYSCALL_H
#define LGSSYSCALL_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsSys final : public LgsObject {
public:
    static constexpr auto name = "Sys";
    LgsMethodImpl exitFunc = LgsMethodImpl("exit", &LGS_VOID, name, {LgsParam(this), LgsParam(&LGS_INT)});

    explicit LgsSys() : LgsObject(name) {
        exitFunc.IRFuncType = FunctionType::get(voidTy, {i32Ty}, false);
        addMethod(&exitFunc);
    }
};

#endif //LGSSYSCALL_H
