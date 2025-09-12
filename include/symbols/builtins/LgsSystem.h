#pragma once
#include "exprs/LgsNull.h"
#include "funcs/LgsFunc.h"
#include "types/LgsNullable.h"
#include "types/LgsObject.h"
#include "../types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include <types/LgsVoid.h>

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsFunc* pidFunc = new LgsFunc{"pid", &LGS_LONG, {this}, PUBLIC | BUILTIN | METHOD};
    LgsFunc* sleepFunc = new LgsFunc{"sleep", &LGS_VOID, {this, &LGS_INT}, PUBLIC | BUILTIN | METHOD};
    LgsFunc* exitFunc = new LgsFunc{"exit", &LGS_VOID, {this, &LGS_INT}, PUBLIC | BUILTIN | METHOD | TERMINATOR};
    LgsFunc* cwdFunc = new LgsFunc{"cwd", new LgsStr(), {this}, PUBLIC | BUILTIN | METHOD};
    LgsFunc* getEnvFunc = new LgsFunc{"getEnv", new LgsStr(), {this, new LgsStr(), new LgsNullable(new LgsStr())}, PUBLIC | BUILTIN | METHOD | HAS_DEFAULTS};
    LgsFunc* coresNumFunc = new LgsFunc{"coresNumber", &LGS_LONG, {this}, PUBLIC | BUILTIN | METHOD};

    explicit LgsSystem() : LgsObject(name) {
        getEnvFunc->funcType->params[2].expr = new LgsNull();
        pidFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>&) {
            return cg.callGetPid();
        };
        sleepFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
            const auto arg = args[1]->loadIR(cg);
            return cg.callSleep(arg);
        };
        exitFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
            return cg.callExit(args[1]->IRValue);
        };
        cwdFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>&) {
            return cg.callCwd();
        };
        coresNumFunc->fn = [](LgsLLVMGen& cg, const std::vector<LgsExpr*>&) {
            return cg.callCoresNum();
        };
        addMethod(pidFunc);
        addMethod(sleepFunc);
        addMethod(exitFunc);
        addMethod(cwdFunc);
        addMethod(getEnvFunc);
        addMethod(coresNumFunc);
    }
};
