#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>
#include "LgsDefinitions.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
    if (arg->type->asBool()) {
        auto boolStr = cg.builder.CreateSelect(arg->IRValue, cg.getString(LgsBool::trueLiteral), cg.getString(LgsBool::falseLiteral));
        return cg.callPrintf({fmt, boolStr});
    }
    if (arg->type->asFloat()) {
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->IRValue, cg.doubleTy())});
    }
    if (arg->type->isInt || arg->type->asChar() || arg->type->asStr()) {
        return cg.callPrintf({fmt, arg->loadIR(cg)});
    }
    if (const auto enum_ = arg->type->asEnum()) {
        return cg.callPrintf({fmt, cg.getString(enum_->name)});
    }
    if (const auto vec = arg->type->asVec()) {
        std::vector vecArgs = {fmt};
        const auto vecExpr = arg->loadIR(cg);
        for (size_t i = 0; i < vec->dimVec; ++i) {
            const auto element = cg.builder.CreateExtractValue(vecExpr, i);
            vecArgs.push_back(element);
        }
        return cg.callPrintf(vecArgs);
    }
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {arg->type->getRTType(cg), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}

void LgsPrint::generatePrintFunc(LgsCgModule& cg) {
    const auto func = cg.getFunc(std::string(LGS_PREFIX) + name, cg.getFT(cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}));
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    const auto sArrBlock = cg.createBlock("sarray");
    const auto dArrBlock = cg.createBlock("darray");
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);

    cg.builder.SetInsertPoint(entryBlock);
    const auto kind = cg.loadStructField(cg.getRTTBaseStruct(), func->getArg(0), 1, cg.i32Ty());
    cg.printInt(kind);
    const auto switchStmt = cg.builder.CreateSwitch(kind, exitBlock, 2);
    switchStmt->addCase(llvm::cast<ConstantInt>(ConstantInt::get(cg.i32Ty(), RTT_SARRAY)), sArrBlock);
    switchStmt->addCase(llvm::cast<ConstantInt>(ConstantInt::get(cg.i32Ty(), RTT_DARRAY)), dArrBlock);

    cg.startBlock(sArrBlock);
    cg.printStr("sarray\n");
    cg.createBranch(exitBlock);

    cg.startBlock(dArrBlock);
    cg.printStr("darray");
    cg.createBranch(exitBlock);

    cg.startBlock(exitBlock);
    cg.builder.CreateRetVoid();
}
