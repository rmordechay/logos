#pragma once
#include "funcs/LgsFunc.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsVoid.h"

class LgsSys final : public LgsObject {
public:
    static constexpr auto name = "Sys";
    LgsFunc* pidFunc = new LgsFunc{"pid", &LGS_SIZE, PUBLIC | BUILTIN | SYSCALL};
    LgsFunc* sleepFunc = new LgsFunc{"sleep", &LGS_VOID, {&LGS_INT}, PUBLIC | BUILTIN | SYSCALL};
    LgsFunc* exitFunc = new LgsFunc{"exit", &LGS_VOID, {&LGS_INT}, PUBLIC | BUILTIN | SYSCALL | TERMINATOR};
    LgsFunc* cwdFunc = new LgsFunc{"cwd", new LgsStr(), PUBLIC | BUILTIN | SYSCALL};
    LgsFunc* getEnvFunc = new LgsFunc{"getEnv", new LgsStr(), {LgsParam(new LgsStr(), ""), LgsParam(new LgsStr(), "fallback", new LgsStrConst(""))}, PUBLIC | BUILTIN};
    LgsFunc* coresNumFunc = new LgsFunc{"coresNumber", &LGS_LONG, PUBLIC | BUILTIN | SYSCALL};

    explicit LgsSys() : LgsObject(name) {
        addMethod(pidFunc);
        addMethod(sleepFunc);
        addMethod(exitFunc);
        addMethod(cwdFunc);
        addMethod(getEnvFunc);
        addMethod(coresNumFunc);
    }
};
