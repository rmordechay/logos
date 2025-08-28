#pragma once
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/LgsAny.h"
#include "types/LgsVoid.h"
#include "stmts/LgsField.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/LgsVectorExpr.h"
#include "configs/LgsDefinitions.h"

class LgsPrint final : public LgsFunc {
public:
    static constexpr auto name = "print";
    explicit LgsPrint(): LgsFunc(name, &LGS_VOID, {&LGS_ANY}, PUBLIC) {}

    Value* call(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) override {
        const auto firstArg = args.front();
        assert(firstArg->type->rtt != RTT_UNKNOWN);
        std::vector<Value*> IRArgs;
        const auto baseStr = codeGen.getIRStr(firstArg->type->strFormatPart());
        IRArgs.emplace_back(baseStr);
        IRArgs.emplace_back(codeGen.i32(firstArg->type->rtt));
        IRArgs.emplace_back(firstArg->IRValue);
        const auto ft = codeGen.getFT(codeGen.voidTy(), {codeGen.ptrTy(), codeGen.i32Ty(), codeGen.ptrTy()}, false);
        return codeGen.callLgsFunc(name, ft, IRArgs);
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
