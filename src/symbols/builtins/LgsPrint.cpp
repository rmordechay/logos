#include "builtins/LgsPrint.h"
#include "data/LgsDefinitions.h"
#include "exprs/constants/LgsStrConst.h"

Value* LgsPrint::call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
    const auto arg = args.front();
    assert(arg->type->getRTType() != RTT_UNKNOWN);
    if (const auto strConst = arg->asStrConst()) {
        if (!strConst->templateParts.empty()) return printFormat(cg, strConst);
    }
    std::vector<Value*> IRArgs;
    const auto baseStr = cg.getIRStr(arg->type->strFormatPart());
    IRArgs.emplace_back(baseStr);
    IRArgs.emplace_back(cg.i32(arg->type->getRTType()));
    IRArgs.emplace_back(arg->getIRPtr(cg));
    return cg.callLgsFunc(name, cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, IRArgs);
}

Value* LgsPrint::printFormat(LgsLLVMGen& cg, const LgsStrConst* const strConst) {
    auto formated = strConst->formatedStr;
    std::vector<Value*> values;
    for (const auto part : strConst->templateParts) {
        auto partIR = part->IRValue;
        values.push_back(partIR);
        const auto pos = formated.find(LGS_STR_FMT_PLACEHOLDER);
        if (pos != std::string::npos) {
            formated.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->strFormatPart());
        }
    }
    std::vector IRArgs = {cg.getIRStr(formated + "\n")};
    IRArgs.insert(IRArgs.end(), values.begin(), values.end());
    return cg.callPrintf(IRArgs);
}
