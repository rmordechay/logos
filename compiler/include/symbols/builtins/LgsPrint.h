#pragma once
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/primitives/LgsVoid.h"

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {LgsParam(&LGS_ANY, "", new LgsStrConst("\n"))}, PUBLIC | BUILTIN | HAS_DEFAULTS) {}
    Value* call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) override;
};
