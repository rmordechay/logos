#pragma once
#include "exprs/LgsNull.h"
#include "funcs/LgsFunc.h"
#include "types/LgsNullable.h"
#include "types/LgsObject.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include <types/LgsVoid.h>

class LgsSystemPid final : public LgsFunc {
public:
    static constexpr auto name = "pid";
    explicit LgsSystemPid(LgsType* parent): LgsFunc(name, &LGS_INT, {parent}, PUBLIC | STATIC | INTERNAL | METHOD ) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        return codeGen->callGetPid();
    }
};

class LgsSystemSleep final : public LgsFunc {
public:
    static constexpr auto name = "sleep";
    explicit LgsSystemSleep(LgsType* parent): LgsFunc(name, &LGS_VOID, {parent, &LGS_INT}, PUBLIC | STATIC | INTERNAL | METHOD ) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        return codeGen->callSleep(args[1]->getIRValue(codeGen));
    }
};

class LgsSystemExit final : public LgsFunc {
public:
    static constexpr auto name = "exit";
    explicit LgsSystemExit(LgsType* parent): LgsFunc(name, &LGS_VOID, {parent, &LGS_INT}, PUBLIC | STATIC | INTERNAL | METHOD | TERMINATOR) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        return codeGen->callExit(args[1]->getIRValue(codeGen));
    }
};

class LgsSystemCwd final : public LgsFunc {
public:
    static constexpr auto name = "cwd";
    explicit LgsSystemCwd(LgsType* parent): LgsFunc(name, new LgsStr(), {parent}, PUBLIC | STATIC | INTERNAL | METHOD ) {}
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        return codeGen->callCwd();
    }
};

class LgsSystemGetEnv final : public LgsFunc {
public:
    static constexpr auto name = "getEnv";
    explicit LgsSystemGetEnv(LgsType* parent): LgsFunc(name, new LgsStr(), {parent, new LgsStr(), new LgsNullable(new LgsStr())}, PUBLIC | STATIC | INTERNAL | METHOD | HAS_DEFAULTS) {
        funcType->params[2].expr = new LgsNull();
    }
};

class LgsSystemCoresNum final : public LgsFunc {
public:
    static constexpr auto name = "coresNum";
    explicit LgsSystemCoresNum(LgsType* parent): LgsFunc(name, &LGS_LONG, {parent}, PUBLIC | STATIC | INTERNAL | METHOD ) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        return codeGen->callCoresNum();
    }
};

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsSystemPid* pidFunc = new LgsSystemPid{this};
    LgsSystemSleep* sleepFunc = new LgsSystemSleep{this};
    LgsSystemExit* exitFunc = new LgsSystemExit{this};
    LgsSystemCwd* cwdFunc = new LgsSystemCwd{this};
    LgsSystemGetEnv* getEnvFunc = new LgsSystemGetEnv{this};
    LgsSystemCoresNum* coresNumFunc = new LgsSystemCoresNum{this};

    explicit LgsSystem() : LgsObject(name) {
        addMethod(pidFunc);
        addMethod(sleepFunc);
        addMethod(exitFunc);
        addMethod(cwdFunc);
        addMethod(getEnvFunc);
        addMethod(coresNumFunc);
    }
};
