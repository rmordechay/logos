#pragma once
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

inline Value* LgsPrint::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto arg = args.front();
    const auto formatStr = arg->type->getStrFormatPart() + '\n';
    const auto IRArgs = {codeGen->getIRStr(formatStr), getIRArg(codeGen, arg)};
    return codeGen->callPrintf(IRArgs);
}

