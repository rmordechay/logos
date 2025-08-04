#pragma once
#include "exprs/unary/LgsInstance.h"
#include "funcs/LgsBuiltinFunc.h"
#include "types/primitives/LgsInt.h"
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

class LgsOSPid final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "pid";
    explicit LgsOSPid(LgsType* parent): LgsBuiltinFunc(name, &LGS_LONG, parent->getName(), {parent}, true) {
        funcType->isStatic = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsOSPid() override = default;
};

class LgsOSExit final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "exit";
    explicit LgsOSExit(LgsType* parent): LgsBuiltinFunc(name, &LGS_VOID, parent->getName(), {parent, &LGS_INT}, true) {
        funcType->isStatic = true;
        funcType->isTerminator = true;
    }
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override;
    ~LgsOSExit() override = default;
};

class LgsOS final : public LgsObject {
public:
    static constexpr auto name = "System";
    LgsOSPid pidFunc{this};
    LgsOSExit pidExit{this};

    explicit LgsOS() : LgsObject(name) {
        addMethod(&pidFunc);
        addMethod(&pidExit);
    }
    ~LgsOS() override = default;
};
