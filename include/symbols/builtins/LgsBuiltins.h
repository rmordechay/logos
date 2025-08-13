#pragma once
#include "configs/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "funcs/LgsBuiltinFunc.h"

#include <llvm/IR/Module.h>
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
        const auto strConst = arg->asStrConst();
        if (strConst && !strConst->templateParts.empty()) {
            return printFormat(codeGen, strConst);
        }
        const auto formatStr = arg->type->strFormatPart() + '\n';
        const auto IRArgs = {codeGen->getIRStr(formatStr), getIRArg(codeGen, arg)};
        return codeGen->callPrintf(IRArgs);
    }

    Function* getIRFunc(LgsCodeGen* codeGen) override {
        const auto ft = FunctionType::get(codeGen->i32Ty(), {codeGen->ptrTy()}, true);
        auto func = codeGen->IRModule->getOrInsertFunction("printf", ft);
        return dyn_cast<Function>(func.getCallee());
    }

    static Value* printFormat(LgsCodeGen* codeGen, const LgsStrConst* const strConst) {
        auto formated = strConst->formatedStr;
        vector<Value*> values;
        for (const auto part : strConst->templateParts) {
            auto partIR = getIRArg(codeGen, part);
            values.push_back(partIR);
            const auto pos = formated.find(LGS_STR_FMT_PLACEHOLDER);
            if (pos != std::string::npos) {
                formated.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->strFormatPart());
            }
        }
        vector IRArgs = {codeGen->getIRStr(formated)};
        IRArgs.insert(IRArgs.end(), values.begin(), values.end());
        return codeGen->callPrintf(IRArgs);
    }

    ~LgsPrint() override = default;
};


