#pragma once
#include "configs/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include <types/LgsVoid.h>
#include <types/primitives/LgsLong.h>
#include <types/LgsAny.h>

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_VOID) {
        funcType->IRName = "printf";
        funcType->isPublic = true;
        funcType->isVariadic = true;
        funcType->params.emplace_back(LgsParam(&LGS_ANY));
        funcType->params.emplace_back(LgsParam(&LGS_ANY));
    }

    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
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
        return codeGen->getFunc("printf", ft);
    }

    static Value* printFormat(LgsCodeGen* codeGen, const LgsStrConst* const strConst) {
        auto formated = strConst->formatedStr;
        std::vector<Value*> values;
        for (const auto part : strConst->templateParts) {
            auto partIR = getIRArg(codeGen, part);
            values.push_back(partIR);
            const auto pos = formated.find(LGS_STR_FMT_PLACEHOLDER);
            if (pos != std::string::npos) {
                formated.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->strFormatPart());
            }
        }
        std::vector IRArgs = {codeGen->getIRStr(formated)};
        IRArgs.insert(IRArgs.end(), values.begin(), values.end());
        return codeGen->callPrintf(IRArgs);
    }

    ~LgsPrint() override = default;
};


