#include "IfStmt.h"

void IfStmt::generateCode(RuntimeStackFrame* stackFrame) {
    const auto currentFunc = stackFrame->currentFunction;
    const auto cond = expr->getLLVMValue(builder, stackFrame);
    const auto ifStartBlock = BasicBlock::Create(*context, "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(*context, "if.end", currentFunc);
    builder->CreateCondBr(cond, ifStartBlock, ifEndBlock);
    builder->SetInsertPoint(ifStartBlock);
    for (const auto& codeNode : codeNodes) {
        codeNode->init(context, builder, module);
        codeNode->generateCode(stackFrame);
    }
    builder->CreateBr(ifEndBlock);
    builder->SetInsertPoint(ifEndBlock);
}
