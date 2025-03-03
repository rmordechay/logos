#include "stmts/LogosIf.h"

#include "CodeGenerator.h"

Value* LogosIf::computeIRValue(CodeGenMetadata* metadata) {
    const auto currentFunc = metadata->logosStack.currentFunc;
    auto& builder = metadata->builder;
    metadata->logosStack.enterScope();

    const auto ifStartBlock = BasicBlock::Create(context, "if.true", currentFunc);
    const auto ifEndBlock = BasicBlock::Create(context, "if.exit", currentFunc);

    const auto condIR = ifCond->writeIRValue(metadata);

    builder.CreateCondBr(condIR, ifStartBlock, ifEndBlock);
    builder.SetInsertPoint(ifStartBlock);
    ifStmtBlock->writeIRValue(metadata);
    builder.CreateBr(ifEndBlock);
    builder.SetInsertPoint(ifEndBlock);

    // for (const auto &ifElseCond : ifElseConds) {
    //     const auto ifElseEndBlock = BasicBlock::Create(context, "if.else.end", currentFunc);
    //     builder.CreateCondBr(condIR, ifEndBlock, ifElseEndBlock);
    //     builder.SetInsertPoint(ifEndBlock);
    //     ifElseCond->writeIRValue(metadata);
    //     builder.CreateBr(ifElseEndBlock);
    //     // builder.SetInsertPoint(ifElseEndBlock);
    // }

    metadata->logosStack.exitScope();
    return nullptr;
}

LogosIf::~LogosIf() {
    delete ifCond;
    delete ifStmtBlock;
    for (const auto &ifElseCond : ifElseConds) {
        delete ifElseCond;
    }
    for (const auto &ifElseStmtBlock : ifElseStmtBlocks) {
        delete ifElseStmtBlock;
    }
    if (elseStmtBlock) {
        delete elseStmtBlock;
    }
}
