#pragma once
#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsBuiltinFunc.h"
#include "types/primitives/LgsInt.h"
#include "types/primitives/LgsSize.h"

#include <types/LgsVoid.h>
#include <types/primitives/LgsLong.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsBuiltinFunc(name, &LGS_VOID, "", {&LGS_ANY, &LGS_ANY}, true, true) {
        funcType->IRName = "printf";
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsPrint() override = default;
};

class LgsSizeOf final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sizeof";
    LgsSizeOf(): LgsBuiltinFunc(name, &LGS_LONG, "", {&LGS_ANY}) {}
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
};

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
    explicit LgsSystemSleep(LgsType* parent): LgsBuiltinFunc(name, &LGS_SIZE, parent->getName(), {parent, &LGS_SIZE}, true) {
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

class LgsSystem final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsSystemPid pidFunc{this};
    LgsSystemExit pidExit{this};

    explicit LgsSystem() : LgsObject(name) {
        addMethod(&pidFunc);
        addMethod(&pidExit);
    }
    ~LgsSystem() override = default;
};
