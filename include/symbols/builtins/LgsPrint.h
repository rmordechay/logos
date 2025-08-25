#pragma once
#include "configs/LgsDefinitions.h"
#include "stmts/LgsField.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include <types/LgsAny.h>

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {&LGS_ANY, &LGS_ANY}, PUBLIC | VARIADIC) {}

    Value* call(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) override {
        std::vector<Value*> IRArgs;
        const auto firstArg = args.front();
        const auto formatStr = firstArg->type->strFormatPart() + '\n';
        if (const auto strConst = firstArg->asStrConst()) {
            if (!strConst->templateParts.empty()) {
                return printFormat(codeGen, strConst);
            }
            LgsStrConst withNewLine(strConst->value + '\n');
            withNewLine.IRValue = codeGen.getIRStr(strConst->value);
            IRArgs.emplace_back(withNewLine.IRValue);
        } else if (const auto obj = firstArg->type->asObject()) {
            IRArgs.emplace_back(codeGen.getIRStr(formatStr));
            for (const auto& field : obj->fields) {
                auto loadIrArg = field->loadIR(codeGen);
                IRArgs.emplace_back(loadIrArg);
            }
        } else {
            IRArgs.emplace_back(codeGen.getIRStr(formatStr));
            for (int i = 0; i < args.size(); ++i) {
                const auto arg = args[i];
                const auto ir = arg->loadIR(codeGen);
                IRArgs.emplace_back(ir);
            }
        }
        return codeGen.callLgsFunc(name, codeGen.getFT(codeGen.voidTy(), {codeGen.ptrTy()}, true), IRArgs);
    }

    Function* getIRFunc(LgsLLVM& codeGen) override {
        const auto ft = codeGen.getFT(codeGen.i32Ty(), {codeGen.ptrTy()}, true);
        return codeGen.getFunc("printf", ft);
    }

    static Value* printFormat(LgsLLVM& codeGen, const LgsStrConst* const strConst) {
        auto formated = strConst->formatedStr;
        std::vector<Value*> values;
        for (const auto part : strConst->templateParts) {
            auto partIR = part->loadIR(codeGen);
            values.push_back(partIR);
            const auto pos = formated.find(LGS_STR_FMT_PLACEHOLDER);
            if (pos != std::string::npos) {
                formated.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->strFormatPart());
            }
        }
        std::vector IRArgs = {codeGen.getIRStr(formated)};
        IRArgs.insert(IRArgs.end(), values.begin(), values.end());
        return codeGen.callPrintf(IRArgs);
    }
};
