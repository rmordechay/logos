#pragma once
#include "exprs/constants/LgsStrConst.h"
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsVoid.h"

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {LgsParam(&LGS_ANY, "", new LgsStrConst("\n"))}, PUBLIC | BUILTIN) {}
    Value* call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) override;
};
