#ifndef LGSSYSCALL_H
#define LGSSYSCALL_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsSys final : public LgsObject {
public:
    static constexpr auto name = "Sys";
    LgsMethodImpl exitFunc = LgsMethodImpl("exit", new LgsVoid(), name, {LgsParam(this), LgsParam(new LgsInt())});

    explicit LgsSys() : LgsObject(name) {
        setExitFunc();
    }

    void setExitFunc() {
        exitFunc.IRFuncType = FunctionType::get(voidTy, {i32Ty}, false);
        methods[exitFunc.signature.name] = {&exitFunc};
    }
};

#endif //LGSSYSCALL_H
