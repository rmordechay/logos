#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "types/LgsObject.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"
#include <types/LgsVoid.h>
#include <types/primitives/LgsLong.h>

class LgsSystemPid final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "pid";
    explicit LgsSystemPid(LgsType* parent): LgsBuiltinFunc(name, &LGS_LONG, parent->getName(), {parent}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsSystemPid() override = default;
};

class LgsSystemSleep final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sleep";
    explicit LgsSystemSleep(LgsType* parent): LgsBuiltinFunc(name, &LGS_VOID, parent->getName(), {parent, &LGS_INT}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsSystemSleep() override = default;
};

class LgsSystemExit final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "exit";
    explicit LgsSystemExit(LgsType* parent): LgsBuiltinFunc(name, &LGS_VOID, parent->getName(), {parent, &LGS_INT}, true) {
        funcType->isStatic = true;
        funcType->isTerminator = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsSystemExit() override = default;
};

class LgsSystemCwd final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "cwd";
    explicit LgsSystemCwd(LgsType* parent): LgsBuiltinFunc(name, new LgsStr(), parent->getName(), {parent}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsSystemCwd() override = default;
};

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsSystemPid pidFunc{this};
    LgsSystemSleep sleepFunc{this};
    LgsSystemExit exitFunc{this};
    LgsSystemCwd cwdFunc{this};

    explicit LgsSystem() : LgsObject(name) {
        addMethod(&pidFunc);
        addMethod(&sleepFunc);
        addMethod(&exitFunc);
        addMethod(&cwdFunc);
    }
    ~LgsSystem() override = default;
};
