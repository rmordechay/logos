#include "LogosIfStmt.h"

const LogosType& LogosIfStmt::getType() const {
    return LOGOS_INT;
}

Value* LogosIfStmt::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    const auto currentFunc = stackFrame->currentFunction;
    const auto cond2 = cond->getLLVMValue(builder, stackFrame, module);
    const auto ifStartBlock = BasicBlock::Create(builder->getContext(), "if.start", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(builder->getContext(), "if.end", currentFunc);
    builder->CreateCondBr(cond2, ifStartBlock, ifEndBlock);
    builder->SetInsertPoint(ifStartBlock);
    for (const auto& codeNode : codeNodes) {
        codeNode->getLLVMValue(builder, stackFrame, module);
    }
    builder->CreateBr(ifEndBlock);
    builder->SetInsertPoint(ifEndBlock);
    return nullptr;
}
