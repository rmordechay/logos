#include "builtins/LgsPrint.h"
#include "exprs/unary/constants/LgsStrConst.h"

Value* LgsPrint::call(LgsLLVM& codeGen, const std::vector<LgsExpr*>& args) {
    const auto firstArg = args.front();
    assert(firstArg->type->rtt != RTT_UNKNOWN);
    std::vector<Value*> IRArgs;
    const auto baseStr = codeGen.getIRStr(firstArg->type->strFormatPart());
    IRArgs.emplace_back(baseStr);
    IRArgs.emplace_back(codeGen.i32(firstArg->type->rtt));
    IRArgs.emplace_back(firstArg->getIRPtrTo(codeGen));
    const auto ft = codeGen.getFT(codeGen.voidTy(), {codeGen.ptrTy(), codeGen.i32Ty(), codeGen.ptrTy()}, false);
    return codeGen.callLgsFunc(name, ft, IRArgs);
}

Function* LgsPrint::getIRFunc(LgsLLVM& codeGen) {
    const auto ft = codeGen.getFT(codeGen.i32Ty(), {codeGen.ptrTy()}, true);
    return codeGen.getFunc("printf", ft);
}

Value* LgsPrint::printFormat(LgsLLVM& codeGen, const LgsStrConst* const strConst) {
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
