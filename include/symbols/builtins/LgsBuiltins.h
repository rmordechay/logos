#pragma once
#include "configs/LgsDefinitions.h"
#include "stmts/LgsField.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include <types/LgsAny.h>

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_INT, {&LGS_ANY, &LGS_ANY}, PUBLIC | VARIADIC) {
        funcType->IRName = "printf";
    }

    Value* call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) override {
        const auto firstArg = args.front();
        const auto strConst = firstArg->asStrConst();
        const auto formatStr = firstArg->type->strFormatPart() + '\n';
        std::vector<Value*> IRArgs;
        if (strConst) {
            if (!strConst->templateParts.empty()) {
                return printFormat(codeGen, strConst);
            }
            IRArgs.emplace_back(firstArg->getIRValue(codeGen));
        } else if (const auto obj = firstArg->type->asObject()) {
            IRArgs.emplace_back(codeGen->getIRStr(formatStr));
            for (const auto& field : obj->fields) {
                const auto ir = field->getIRValue(codeGen);
                IRArgs.emplace_back(loadIRArg(codeGen, ir, field->type));
            }
        } else {
            IRArgs.emplace_back(codeGen->getIRStr(formatStr));
            for (int i = 0; i < args.size(); ++i) {
                const auto arg = args[i];
                IRArgs.emplace_back(arg->getIRValue(codeGen));
            }
        }
        return codeGen->callLgsFunc(name, FunctionType::get(codeGen->voidTy(), {codeGen->ptrTy()}, true), IRArgs);
    }

    Function* getIRFunc(LgsCodeGen* codeGen) override {
        const auto ft = FunctionType::get(codeGen->i32Ty(), {codeGen->ptrTy()}, true);
        return codeGen->getFunc("printf", ft);
    }

    static Value* printFormat(LgsCodeGen* codeGen, const LgsStrConst* const strConst) {
        auto formated = strConst->formatedStr;
        std::vector<Value*> values;
        for (const auto part : strConst->templateParts) {
            auto partIR = loadIRArg(codeGen, part->getIRValue(codeGen), part->type);
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
};
