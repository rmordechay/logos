#pragma once
#include "funcs/LgsFunc.h"
#include "types/LgsNullable.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"
#include "../types/primitives/LgsVoid.h"

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsFunc* pidFunc = new LgsFunc{"pid", &LGS_SIZE, PUBLIC | BUILTIN | SYSCALL};
    LgsFunc* sleepFunc = new LgsFunc{"sleep", &LGS_VOID, {&LGS_INT}, PUBLIC | BUILTIN | SYSCALL};
    LgsFunc* exitFunc = new LgsFunc{"exit", &LGS_VOID, {&LGS_INT}, PUBLIC | BUILTIN | SYSCALL | TERMINATOR};
    LgsFunc* cwdFunc = new LgsFunc{"cwd", new LgsStr(), PUBLIC | BUILTIN | SYSCALL};
    LgsFunc* getEnvFunc = new LgsFunc{"getEnv", new LgsStr(), {LgsParam(new LgsStr(), ""), LgsParam(new LgsStr(), "fallback", new LgsStrConst(""))}, PUBLIC | BUILTIN};
    LgsFunc* coresNumFunc = new LgsFunc{"coresNumber", &LGS_LONG, PUBLIC | BUILTIN | SYSCALL};

    explicit LgsSystem() : LgsObject(name) {
        pidFunc->funcType->IRName = "getpid";
        sleepFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args) {
            return cg.callLgsFunc("System_sleep", cg.i32Ty(), {cg.i32Ty()}, {args.front().expr->IRValue});
        };
        cwdFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsFuncArg>&) {
            const auto value = cg.builder.CreateAlloca(ArrayType::get(cg.i8Ty(), STRING_BUFFER_SIZE));
            // TODO os?
            cg.callFunc("getcwd", cg.ptrTy(), {cg.ptrTy(), cg.sizeTy()}, {value, cg.usize(STRING_BUFFER_SIZE)});
            return value;
        };
        coresNumFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsFuncArg>&) {
            // TODO os?
            return cg.callFunc("sysconf", cg.i64Ty(), {cg.i32Ty()}, {cg.i32(58)});
        };
        getEnvFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsFuncArg>& args) {
            const auto fallback = args.size() == 2 ? args.back().expr->IRValue : cg.null();
            return cg.callLgsFunc("System_getEnv", cg.ptrTy(), {cg.ptrTy(), cg.ptrTy()}, {args.front().expr->IRValue, fallback});
        };
        addMethod(pidFunc);
        addMethod(sleepFunc);
        addMethod(exitFunc);
        addMethod(cwdFunc);
        addMethod(getEnvFunc);
        addMethod(coresNumFunc);
    }
};
