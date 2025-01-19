#include "LogosIfStmt.h"

Value* LogosIfStmt::getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) {
    const auto currentFunc = stackFrame->top().currentFunction;
    const auto condLLVM = cond->getLLVMValue(builder, stackFrame, module);
    const auto ifStartBlock = BasicBlock::Create(builder->getContext(), "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(builder->getContext(), "if.end", currentFunc);

    builder->CreateCondBr(condLLVM, ifStartBlock, ifEndBlock);
    builder->SetInsertPoint(ifStartBlock);
    for (const auto& codeNode : stmt) {
        codeNode->getLLVMValue(builder, stackFrame, module);
    }
    builder->CreateBr(ifEndBlock);
    builder->SetInsertPoint(ifEndBlock);
    return nullptr;
}
