#pragma once
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsVoid.h"

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {&LGS_ANY}, PUBLIC) {}

    Value* call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) override;
    static Value* printFormat(LgsLLVMGen& cg, const LgsStrConst* const strConst);
};
