#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include "utils/LgsIRUtils.h"
#include <types/LgsVoid.h>
#include <types/primitives/LgsLong.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(): LgsBuiltinFunc(name, &LGS_VOID, "", {&LGS_ANY, &LGS_ANY}, true, true) {
        funcType->IRName = "printf";
    }

    Value* call(LgsModule* module, const vector<LgsExpr*>& args) override {
        const auto arg = args.front();
        const auto formatStr = arg->type->getStrFormatPart();
        const auto IRArgs = {getIRArg(module, arg), getIRStr(module, formatStr)};
        return module->builder.CreateCall(getPrintf(module), IRArgs);
    }

    ~LgsPrint() override = default;
};

class LgsSizeOf final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sizeof";

    LgsSizeOf(): LgsBuiltinFunc(name, &LGS_LONG, "", {&LGS_ANY}) {}
    Value* call(LgsModule* module, const vector<LgsExpr*>& args) override {
        return i64(module, args.front()->type->getSizeBytes());
    }
};

inline LgsPrint lgsPrint;
inline LgsSizeOf lgsSizeof;
