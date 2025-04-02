#ifndef LGSSYSCALL_H
#define LGSSYSCALL_H
#include "funcs/LgsMethodImpl.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

class LgsSys final : public LgsObject {
public:
    static constexpr auto name = "Sys";
    LgsMethodImpl exitFunc = LgsMethodImpl("exit", new LgsVoid, name, {new LgsParam(this), new LgsParam(new LgsInt)});
    FunctionType* const exitIRFuncType = FunctionType::get(voidTy, {i32Ty}, false);

    explicit LgsSys() : LgsObject(name) {
        exitFunc.signature.isStatic = true;
        methods[exitFunc.signature.name] = {&exitFunc};
    }

    Value* getExitFunc();
};

#endif //LGSSYSCALL_H
