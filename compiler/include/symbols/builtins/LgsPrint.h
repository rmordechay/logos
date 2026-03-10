#pragma once
#include <string>
#include <vector>

#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "../types/primitives/LgsAny.h"
#include "types/primitives/LgsVoid.h"
#include "LgsValue.h"
#include "funcs/LgsParam.h"
#include "types/LgsFuncType.h"

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";

    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {LgsParam(&LGS_ANY, "", new LgsStrConst("\n"))}, PUBLIC | BUILTIN | HAS_DEFAULTS) {}
    Value* call(LgsCodeGen& cg, const std::vector<LgsVarDec>& args) override;
};
