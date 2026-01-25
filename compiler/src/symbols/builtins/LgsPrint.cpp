#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>

#include "LgsDefinitions.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCodeGen& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    if (arg->type->asFloat()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->IRValue, cg.doubleTy())});
    }
    if (arg->type->asStr() || arg->type->asBool() || arg->type->asEnum()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        const auto value = arg->type->asIRStr(cg, arg->loadIR(cg));
        return cg.callPrintf({fmt, value});
    }
    if (arg->type->isInt || arg->type->asChar()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, arg->loadIR(cg)});
    }
    if (const auto vec = arg->type->asVec()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        std::vector<Value*> vecArgs = {fmt};
        const auto vecExpr = arg->loadIR(cg);
        for (size_t i = 0; i < vec->dimVec; ++i) {
            const auto element = cg.builder.CreateExtractValue(vecExpr, i);
            vecArgs.push_back(element);
        }
        return cg.callPrintf(vecArgs);
    }
    assert(arg->type->rttKind != RTT_UNKNOWN);
    const std::vector<Type*> params = {cg.i32Ty(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {cg.i32(arg->type->rttKind), arg->type->getRTType(cg), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}

Function* LgsPrint::generateFmtFunc(LgsCodeGen& cg) {
    const auto funcName = "formatElemen";
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), cg.ptrTy(), cg.i32Ty(), cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    const auto defaultBlock = cg.createBlock(BLOCK_DEFAULT);
    cg.builder.SetInsertPoint(entryBlock);

    const auto buffer = func->getArg(0);
    const auto bufferOffsetPtr = func->getArg(1);
    const auto kind = func->getArg(2);
    const auto rtt = func->getArg(3);
    const auto value = func->getArg(4);
    buffer->setName("buffer");
    kind->setName("kind");
    rtt->setName("rtt");
    value->setName("value");
    const auto typeInfo = cg.getStructType({cg.sizeTy(), cg.i32Ty()});
    const auto switchStmt = cg.builder.CreateSwitch(kind, defaultBlock);
    const auto sArrBlock = cg.createBlock("sarr_block");
    const auto intBlock = cg.createBlock("int_block");
    switchStmt->addCase(cg.i32(RTT_SARRAY), sArrBlock);
    switchStmt->addCase(cg.i32(RTT_INT), intBlock);

    // SArray
    cg.startBlock(sArrBlock);
    const auto sArrType = cg.getStructType({cg.sizeTy(), cg.ptrTy()});
    const auto len = cg.loadStructField(sArrType, rtt, 0, cg.sizeTy());
    const auto baseType = cg.loadStructField(sArrType, rtt, 1, cg.ptrTy());
    auto baseSize = cg.load(cg.sizeTy(), baseType);
    const auto baseKind = cg.loadStructField(typeInfo, baseType, 1, cg.i32Ty());
    auto bufferOffset = cg.load(cg.sizeTy(), bufferOffsetPtr);
    auto pos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, bufferOffset);
    cg.store(cg.i8('['), pos);
    cg.incSize(bufferOffset, bufferOffsetPtr);
    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto offset = cg.builder.CreateMul(baseSize, iValue);
        const auto gep = cg.builder.CreatePtrAdd(value, offset);
        cg.builder.CreateCall(func, {buffer, bufferOffsetPtr, baseKind, baseType, gep});
        bufferOffset = cg.load(cg.sizeTy(), bufferOffsetPtr);
        cg.store(cg.builder.CreateAdd(bufferOffset, baseSize), bufferOffsetPtr);
    });
    bufferOffset = cg.load(cg.sizeTy(), bufferOffsetPtr);
    pos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, bufferOffset);
    cg.store(cg.i8(']'), pos);
    cg.incSize(bufferOffset, bufferOffsetPtr);
    bufferOffset = cg.load(cg.sizeTy(), bufferOffsetPtr);
    pos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, bufferOffset);
    cg.store(cg.i8Zero(), pos);
    cg.incSize(bufferOffset, bufferOffsetPtr);
    cg.printStr(buffer);
    cg.builder.CreateRetVoid();

    // Int
    cg.startBlock(intBlock);
    baseSize = cg.load(cg.sizeTy(), rtt);
    bufferOffset = cg.load(cg.sizeTy(), bufferOffsetPtr);
    pos = cg.builder.CreateInBoundsGEP(cg.i8Ty(), buffer, bufferOffset);
    const auto fmtStr = cg.callSnprintf("%d", {cg.load(cg.i32Ty(), value)});
    cg.callMemcpy(pos, fmtStr, cg.callStrLen(fmtStr));
    cg.builder.CreateRetVoid();

    cg.startBlock(defaultBlock);
    cg.builder.CreateRetVoid();
    return func;
}
