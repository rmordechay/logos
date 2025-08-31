#include "builtins/LgsPrint.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/constants/LgsStrConst.h"

Value* LgsPrint::call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
    const auto firstArg = args.front();
    assert(firstArg->type->rtt != RTT_UNKNOWN);
    std::vector<Value*> IRArgs;
    const auto baseStr = cg.getIRStr(firstArg->type->strFormatPart());
    IRArgs.emplace_back(baseStr);
    IRArgs.emplace_back(cg.i32(firstArg->type->rtt));
    const auto type = firstArg->IRValue->getType();
    const auto v = type->isIntegerTy() ? firstArg->getIRPtrTo(cg) : firstArg->loadIR(cg);
    IRArgs.emplace_back(v);
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy()}, false);
    return cg.callLgsFunc(name, ft, IRArgs);
}

Function* LgsPrint::getIRFunc(LgsLLVMGen& cg) {
    const auto ft = cg.getFT(cg.i32Ty(), {cg.ptrTy()}, true);
    return cg.getFunc("printf", ft);
}

Value* LgsPrint::printFormat(LgsLLVMGen& cg, const LgsStrConst* const strConst) {
    auto formated = strConst->formatedStr;
    std::vector<Value*> values;
    for (const auto part : strConst->templateParts) {
        auto partIR = part->loadIR(cg);
        values.push_back(partIR);
        const auto pos = formated.find(LGS_STR_FMT_PLACEHOLDER);
        if (pos != std::string::npos) {
            formated.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->strFormatPart());
        }
    }
    std::vector IRArgs = {cg.getIRStr(formated)};
    IRArgs.insert(IRArgs.end(), values.begin(), values.end());
    return cg.callPrintf(IRArgs);
}
