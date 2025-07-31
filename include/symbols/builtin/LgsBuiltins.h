#pragma once
#include "funcs/LgsBuiltinFunc.h"
#include <types/LgsVoid.h>
#include <types/primitives/LgsLong.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(): LgsBuiltinFunc(name, &LGS_VOID, "", {&LGS_ANY, &LGS_ANY}, true, true) {
        funcType->IRName = "printf";
    }

    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        const auto arg = args.front();
        const auto formatStr = arg->type->getStrFormatPart() + '\n';
        const auto IRArgs = {codeGen->getIRStr(formatStr), getIRArg(codeGen, arg)};
        return codeGen->callPrintf(IRArgs);
    }

    ~LgsPrint() override = default;
};

class LgsSizeOf final : public LgsBuiltinFunc {
public:
    static constexpr auto name = "sizeof";

    LgsSizeOf(): LgsBuiltinFunc(name, &LGS_LONG, "", {&LGS_ANY}) {}
    Value* call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) override {
        return codeGen->i64(args.front()->type->getSizeBytes());
    }
};

inline LgsPrint lgsPrint;
inline LgsSizeOf lgsSizeof;
