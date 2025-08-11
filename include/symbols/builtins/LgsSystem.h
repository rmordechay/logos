#pragma once
#include "exprs/LgsNull.h"
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsNullable.h"
#include "types/LgsObject.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include <types/LgsVoid.h>

class LgsSystemPid final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "pid";
    explicit LgsSystemPid(LgsType* parent): LgsBuiltinFunc(name, &LGS_INT, parent->getName(), {parent}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->callGetPid();
    }
    ~LgsSystemPid() override = default;
};

class LgsSystemSleep final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sleep";
    explicit LgsSystemSleep(LgsType* parent): LgsBuiltinFunc(name, &LGS_VOID, parent->getName(), {parent, &LGS_INT}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->callSleep(args[1]->getIRValue(codeGen));
    }
    ~LgsSystemSleep() override = default;
};

class LgsSystemExit final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "exit";
    explicit LgsSystemExit(LgsType* parent): LgsBuiltinFunc(name, &LGS_VOID, parent->getName(), {parent, &LGS_INT}, true) {
        funcType->isStatic = true;
        funcType->isTerminator = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->callExit(args[1]->getIRValue(codeGen));
    }
    ~LgsSystemExit() override = default;
};

class LgsSystemCwd final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "cwd";
    explicit LgsSystemCwd(LgsType* parent): LgsBuiltinFunc(name, new LgsStr(), parent->getName(), {parent}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->callCwd();
    }
    ~LgsSystemCwd() override = default;
};

class LgsSystemGetEnv final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "getEnv";
    explicit LgsSystemGetEnv(LgsType* parent): LgsBuiltinFunc(name, new LgsStr(), parent->getName(), {parent, new LgsStr(), new LgsNullable(new LgsStr())}, true) {
        funcType->isStatic = true;
        funcType->hasDefaults = true;
        funcType->params[2].expr = new LgsNull();
    }
    ~LgsSystemGetEnv() override = default;
};

class LgsSystemCoresNum final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "coresNum";
    explicit LgsSystemCoresNum(LgsType* parent): LgsBuiltinFunc(name, &LGS_LONG, parent->getName(), {parent}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->callCoresNum();
    }
    ~LgsSystemCoresNum() override = default;
};

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsSystemPid pidFunc{this};
    LgsSystemSleep sleepFunc{this};
    LgsSystemExit exitFunc{this};
    LgsSystemCwd cwdFunc{this};
    LgsSystemGetEnv getEnvFunc{this};
    LgsSystemCoresNum coresNumFunc{this};

    explicit LgsSystem() : LgsObject(name) {
        addMethod(&pidFunc);
        addMethod(&sleepFunc);
        addMethod(&exitFunc);
        addMethod(&cwdFunc);
        addMethod(&getEnvFunc);
        addMethod(&coresNumFunc);
    }
    ~LgsSystem() override = default;
};
