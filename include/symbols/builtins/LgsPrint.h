#pragma once
#include "funcs/LgsFunc.h"
#include "types/LgsAny.h"
#include "types/LgsVoid.h"

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {&LGS_ANY}, PUBLIC) {}

    Value* call(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) override;
    Function* getIRFunc(LgsLLVM& codeGen) override;
    static Value* printFormat(LgsLLVM& codeGen, const LgsStrConst* const strConst);
};
