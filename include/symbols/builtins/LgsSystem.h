#pragma once
#include "exprs/LgsNull.h"
#include "funcs/LgsFunc.h"
#include "types/LgsNullable.h"
#include "types/LgsObject.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include <types/LgsVoid.h>

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsFunc* pidFunc = new LgsFunc{"pid", &LGS_LONG, {this}, PUBLIC | STATIC | INTERNAL | METHOD};
    LgsFunc* sleepFunc = new LgsFunc{"sleep", &LGS_VOID, {this, &LGS_INT}, PUBLIC | STATIC | INTERNAL | METHOD};
    LgsFunc* exitFunc = new LgsFunc{"exit", &LGS_VOID, {this, &LGS_INT}, PUBLIC | STATIC | INTERNAL | METHOD | TERMINATOR};
    LgsFunc* cwdFunc = new LgsFunc{"cwd", new LgsStr(), {this}, PUBLIC | STATIC | INTERNAL | METHOD};
    LgsFunc* getEnvFunc = new LgsFunc{"getEnv", new LgsStr(), {this, new LgsStr(), new LgsNullable(new LgsStr())}, PUBLIC | STATIC | INTERNAL | METHOD | HAS_DEFAULTS};
    LgsFunc* coresNumFunc = new LgsFunc{"coresNumber", &LGS_LONG, {this}, PUBLIC | STATIC | INTERNAL | METHOD};

    explicit LgsSystem() : LgsObject(name) {
        getEnvFunc->funcType->params[2].expr = new LgsNull();
        pidFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>&) {
            return codeGen.callGetPid();
        };
        sleepFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) {
            const auto arg = LgsFunc::loadIRArg(&codeGen, args[1]->IRValue, args[1]->type);
            return codeGen.callSleep(arg);
        };
        exitFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>& args) {
            return codeGen.callExit(args[1]->IRValue);
        };
        cwdFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>&) {
            return codeGen.callCwd();
        };
        coresNumFunc->fn = [](LgsCodeGen& codeGen, const std::vector<LgsExpr*>&) {
            return codeGen.callCoresNum();
        };
        addMethod(pidFunc);
        addMethod(sleepFunc);
        addMethod(exitFunc);
        addMethod(cwdFunc);
        addMethod(getEnvFunc);
        addMethod(coresNumFunc);
    }
};
