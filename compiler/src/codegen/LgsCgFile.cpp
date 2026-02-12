#include "codegen/LgsCgFile.h"
#include "builtins/LgsTest.h"
#include "LgsConfigs.h"
#include "builtins/LgsSys.h"
#include "exprs/LgsArrayExpr.h"
#include "funcs/LgsCoroutine.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsEnvVar.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsTypeExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsEnum.h"
#include "files/LgsMainFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsAppConfigs.h"
#include "logos/LgsPaths.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsDArray.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsSize.h"
#include "exprs/LgsMatrixExpr.h"
#include "exprs/LgsMetaSelection.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/LgsNullable.h"
#include <llvm/IR/Module.h>
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <unistd.h>
#include <unordered_set>

bool LgsCgFile::generateSrcFile(LgsFile* file, const LgsPaths& paths) {
    visitExternalSymbols(file);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        visitInterface(interfaceFile->interface);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(file)) {
        visitTestFile(testFile);
    }
    if (appConfigs->debugMode) cg.finalizeDebugger(paths.buildDir);
    return cg.writeIRModule(paths, appConfigs->optLevel);
}

void LgsCgFile::visitMainFile(LgsMainFile* mainFile) {
    for (const auto varDec : mainFile->varDecs) {
        visitConstant(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    }
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto object : mainFile->objects) {
        visitObject(object);
    }
    for (const auto enum_ : mainFile->enums) {
        visitEnum(enum_);
    }

    for (const auto& [name, func] : mainFile->funcs) {
        if (const auto mainFunc = dynamic_cast<LgsMainFunc*>(func)) {
            visitMainFunc(mainFunc);
        } else {
            visitFunc(func);
        }
    }
}

void LgsCgFile::visitInterface(const LgsInterface* interface) {
    for (const auto& [_, method] : interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCgFile::visitTestFile(const LgsTestFile* testFile) {
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

void LgsCgFile::visitObject(LgsObject* obj) {
    if(const auto singleton = obj->singleton) {
        const auto objIRType = obj->getIRType(cg);
        singleton->IRValue = cg.IRModule->getGlobalVariable(obj->name);
        if (!singleton->IRValue) {
            const auto zeroInit = ConstantAggregateZero::get(objIRType);
            singleton->IRValue = cg.createGlobal(obj->name, objIRType, zeroInit);
        }
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
}

void LgsCgFile::visitEnum(const LgsEnum* enum_) {
    for (const auto field : enum_->fields) {
        if (!field->expr) continue;
        visitExpr(field->expr);
    }
}

void LgsCgFile::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    initMainArgs(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    stack.exitScope();
}

void LgsCgFile::visitFunc(LgsFunc* func) {
    const auto ft = func->funcType;
    if (!ft->genericTypes.empty()) return;
    stack.enterScope(func);
    createPrologue(func);
    if (func->isTest) for (auto [_, then] : func->mocks) visitExpr(then);
    auto& params = ft->params;
    if (ft->isVariadic) {
        params.back().IRValue = cg.builder.CreateAlloca(cg.ptrTy(), nullptr, "va_list");
        cg.callIntrinsics(Intrinsic::vastart, {cg.ptrTy()}, {params.back().IRValue});
    }
    visitStmtsBlock(func->stmtsBlock);
    if (ft->isVariadic) {
        cg.callIntrinsics(Intrinsic::vaend, {cg.ptrTy()}, {params.back().IRValue});
    }
    createEpilogue(func);
    stack.exitScope();
}

void LgsCgFile::visitExternalSymbols(LgsFile* file) {
    for (auto [name, symbol] : file->symbolTable.symbols) {
        if (symbol.symbolType == VAR_DEC && symbol.isExternal) {
            visitConstant(symbol.varDec->expr);
            symbol.varDec->IRValue = symbol.varDec->expr->IRValue;
        }
    }
}

void LgsCgFile::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) visitIfStmt(ifStmt);
    else if (const auto pattern = stmt->asSwitch()) visitSwitch(pattern);
    else if (const auto varDec = stmt->asVarDec()) visitVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) visitLoop(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) visitCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) visitDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) visitAssignment(assignment);
    else if (const auto ioStmt = stmt->asIOStmt()) visitIOStmt(ioStmt);
    else if (const auto returnStmt = stmt->asReturn()) visitReturnStmt(returnStmt);
    else if (const auto breakStmt = stmt->asBreak()) visitBreakStmt(breakStmt);
    else if (stmt->asContinue()) visitContinueStmt();
}

void LgsCgFile::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock) return;
    for (const auto& stmt : stmtsBlock->stmts) {
        switch (stmt.wrapperType) {
        case LgsStmtWrapper::WrapperType::Object:
            visitObject(stmt.obj);
            break;
        case LgsStmtWrapper::WrapperType::Stmt:
            visitStmt(stmt.stmt);
            if (appConfigs->debugMode) stmt.stmt->setDebugValue(cg);
            break;
        case LgsStmtWrapper::WrapperType::Expr:
            visitExpr(stmt.expr);
            if (appConfigs->debugMode) stmt.expr->setDebugValue(cg);
            break;
        }
    }
}

void LgsCgFile::visitLoop(LgsForLoop* loop) {
    stack.enterScope(loop);
    loop->setBlocks(cg);
    if (const auto rangeLoop = loop->asRangeLoop()) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = loop->asForeachLoop()) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = loop->asInfiniteLoop()) {
        visitInfiniteLoop(infiniteLoop);
    } else if (const auto whileLoop = loop->asWhileLoop()) {
        visitWhileLoop(whileLoop);
    } else {
        assert(0);
    }
    visitStmtsBlock(loop->stmtsBlock);
    loop->incAndJumpToCond(cg);
    cg.startBlock(loop->IRExitBlock);
    stack.exitScope();
}

void LgsCgFile::visitRangeLoop(LgsRangeLoop* loop) {
    visitExpr(loop->startRange);
    visitExpr(loop->endRange);
    loop->iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(loop->loopStart(cg), cg.sizeTy());
    cg.store(loopStart, loop->iPtr);
    cg.builder.CreateBr(loop->IRCondBlock);

    // Condition
    cg.startBlock(loop->IRCondBlock);
    const auto loopEnd = loop->loopEnd(cg);
    const auto condition = cg.builder.CreateICmpSLT(loop->loadIndex(cg), loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    if (!loop->loopVars.empty()) {
        loop->loopVars[0]->IRValue = loop->loadIndex(cg);
    }
}

void LgsCgFile::visitForeachLoop(LgsForeachLoop* loop) {
    visitExpr(loop->iterExpr);
    const auto indexTy = cg.sizeTy();
    loop->iPtr = cg.allocaAndStore(indexTy, cg.zeroSize());
    if (loop->iterExpr->type->asMap()) {
        loop->iteratorCounter = cg.allocaAndStore(cg.sizeTy(), cg.zeroSize());
    }

    // Condition
    cg.branchAndStartBlock(loop->IRCondBlock);
    const auto cond = cg.builder.CreateICmpSLT(loop->loadIndex(cg), loop->loopEnd(cg));
    cg.builder.CreateCondBr(cond, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    const auto iterable = loop->iterExpr->type->asIterable();
    iterable->setLoopIRVars(cg, loop);
}

void LgsCgFile::visitInfiniteLoop(const LgsInfiniteLoop* loop) {
    cg.branchAndStartBlock(loop->IRBodyBlock);
}

void LgsCgFile::visitLoopMetaVar(LgsMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    const auto iValue = loop->loadIndex(cg);
    switch (metaVar->varType) {
    case FOR_I: {
        metaVar->IRValue = iValue;
        break;
    }
    case FOR_IS_FIRST: {
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, loop->loopStart(cg));
        break;
    }
    case FOR_IS_LAST: {
        const auto decremented = cg.builder.CreateSub(loop->loopEnd(cg), cg.usize(1));
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, decremented);
        break;
    }
    case FOR_ELEMENT:
        metaVar->IRValue = loop->loopVars.front()->IRValue;
        break;
    }
}

void LgsCgFile::visitWhileLoop(const LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    // Condition
    cg.startBlock(loop->IRCondBlock);
    visitExpr(loop->condExpr);
    cg.builder.CreateCondBr(loop->condExpr->IRValue, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    cg.startBlock(loop->IRBodyBlock);
}

void LgsCgFile::visitVarDec(LgsVarDec* varDec) {
    if (varDec->shouldAllocate()) {
        varDec->IRValue = cg.builder.CreateAlloca(varDec->type->getIRType(cg));
        varDec->expr->pointee = varDec->IRValue;
        visitExpr(varDec->expr);
        if (varDec->expr->IRValue != varDec->IRValue) {
            cg.store(varDec->expr->IRValue, varDec->IRValue);
        }
        varDec->IRValue->setName(varDec->name);
    } else {
        visitExpr(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    }
    assert(varDec->IRValue);
}

void LgsCgFile::visitAssignment(const LgsAssignment* assignment) {
    assert(!assignment->binaryExpr);
    const auto left = assignment->left;
    const auto right = assignment->right;
    visitExpr(left);
    right->pointee = left->IRValue;
    visitExpr(right);
    cg.store(right->IRValue, left->pointee ? left->pointee : left->IRValue);
}

void LgsCgFile::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->macroTrueBlock) {
        return visitStmtsBlock(ifStmt->macroTrueBlock);
    }
    if (ifStmt->elseIfs.empty()) {
        if (ifStmt->elseBlock) {
            visitIfWithElse(ifStmt);
        } else {
            visitSimpleIf(ifStmt);
        }
    } else {
        visitElseIf(ifStmt);
    }
}

void LgsCgFile::visitSimpleIf(LgsIfStmt* ifStmt) {
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    cg.ifStmt(ifStmt->ifCond->IRValue, [this, &ifStmt] {
        visitStmtsBlock(ifStmt->ifBlock);
    });
    stack.exitScope();
}

void LgsCgFile::visitIfWithElse(LgsIfStmt* ifStmt) {
    const auto IRBlockTrue = cg.createBlock(BLOCK_TRUE);
    const auto IRBlockExit = cg.createBlock(BLOCK_EXIT);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_FALSE);

    // if block
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    const auto ifCondIR = ifStmt->ifCond->IRValue;
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockExit);
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branch(ifStmt->IRExitBlock);
    stack.exitScope();

    // else block
    stack.enterScope(ifStmt);
    cg.startBlock(IRBlockExit);
    visitStmtsBlock(ifStmt->elseBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock);
    stack.exitScope();
}

void LgsCgFile::visitElseIf(LgsIfStmt* ifStmt) {
    auto IRBlockTrue = cg.createBlock(BLOCK_TRUE);
    auto IRBlockElseIfCheck = cg.createBlock(BLOCK_ELSE_IF_CHECK);
    const auto IRBlockExit = cg.createBlock(BLOCK_EXIT);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_FALSE);

    // if block
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    const auto ifCondIR = ifStmt->ifCond->IRValue;
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branch(ifStmt->IRExitBlock);
    stack.exitScope();

    for (size_t i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockElseIfCheck);
        visitExpr(expr);
        const auto elseIfCondIR = expr->IRValue;
        IRBlockTrue = cg.createBlock(BLOCK_ELSE_IF);
        if (i == ifStmt->elseIfs.size() - 1) {
            if (ifStmt->elseBlock) {
                cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockExit);
            } else {
                cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, ifStmt->IRExitBlock);
            }
        } else {
            IRBlockElseIfCheck = cg.createBlock(BLOCK_ELSE_IF_CHECK);
            cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElseIfCheck);
        }
        cg.startBlock(IRBlockTrue);
        visitStmtsBlock(stmtBlock);
        cg.branch(ifStmt->IRExitBlock);
        stack.exitScope();
    }

    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockExit);
        visitStmtsBlock(ifStmt->elseBlock);
        cg.branch(ifStmt->IRExitBlock);
        stack.exitScope();
    }
    cg.startBlock(ifStmt->IRExitBlock);
}

void LgsCgFile::visitSwitch(LgsSwitch* switchStmt) {
    assert(switchStmt->cond);
    const auto defaultBlock = cg.createBlock(BLOCK_DEFAULT);
    const auto exitBlock = cg.createBlock(BLOCK_EXIT, cg.currentFunc);
    const auto cond = switchStmt->cond;
    visitExpr(cond);

    const auto exprIRValue = cond->type->hashValue(cg, cond->IRValue);
    SwitchInst* switchInst;
    if (switchStmt->elseBlock) {
        const auto numOfCases = switchStmt->patterns.size();
        switchInst = cg.builder.CreateSwitch(exprIRValue, defaultBlock, numOfCases);
    } else {
        switchInst = cg.builder.CreateSwitch(exprIRValue, exitBlock, switchStmt->patterns.size());
    }

    for (size_t i = 0; i < switchStmt->patterns.size(); ++i) {
        stack.enterScope(switchStmt);
        const auto [expr, stmtsBlock] = switchStmt->patterns[i];
        visitExpr(expr);
        const auto patternBlock = cg.createBlock(BLOCK_CASE_PREFIX, cg.currentFunc);
        const auto hashed = expr->type->hashValue(cg, expr->IRValue);
        switchInst->addCase(llvm::dyn_cast<ConstantInt>(hashed), patternBlock);
        cg.builder.SetInsertPoint(patternBlock);
        visitStmtsBlock(stmtsBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    if (switchStmt->elseBlock) {
        stack.enterScope(switchStmt);
        cg.startBlock(defaultBlock);
        visitStmtsBlock(switchStmt->elseBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }
    cg.builder.SetInsertPoint(exitBlock);
}

void LgsCgFile::visitContinueStmt() {
    stack.currentLoop()->incAndJumpToCond(cg);
}

void LgsCgFile::visitReturnStmt(LgsReturn* returnStmt) {
    visitExpr(returnStmt->expr);
    returnStmt->expr->IRValue = returnStmt->expr ? returnStmt->expr->IRValue : nullptr;
    const auto currentFunc = stack.currentFunc();
    if (currentFunc->funcType->rt->isVoid()) {
        cg.callPopStack();
        cg.builder.CreateRetVoid();
    } else if (!currentFunc->returnStmts.empty()) {
        if (currentFunc->returnStmts.empty()) {
            cg.builder.CreateRet(returnStmt->expr->IRValue);
        } else if (currentFunc->returnStmts.size() == 1) {
            cg.callPopStack();
            if (returnStmt->expr->type->isNumber()) {
                cg.builder.CreateRet(returnStmt->expr->loadIR(cg));
            } else {
                cg.builder.CreateRet(returnStmt->expr->IRValue);
            }
        } else {
            returnStmt->parentBlock = cg.builder.GetInsertBlock();
            cg.builder.CreateBr(currentFunc->epilogue);
        }
    }
}

void LgsCgFile::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        cg.builder.CreateBr(stack.getOutermostIfStmt()->IRExitBlock);
    } else if (breakStmt->tag != "") {
        cg.builder.CreateBr(stack.findTagExitBlock(breakStmt->tag));
    } else {
        const auto loop = stack.currentLoop();
        cg.builder.CreateBr(loop->IRExitBlock);
    }
}

void LgsCgFile::visitCoroutine(const LgsCoroutine* coroutine) {
    LgsFuncCall* fc = nullptr;
    if (coroutine->funcCall->name == "") {
        visitLambda(coroutine->funcCall->func);
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
        fc = coroutine->selection->asMethodCall();
    }

    if (!cg.IRModule->getFunction(fc->coroutine->funcType->getName())) {
        cg.savedIP = cg.builder.saveIP();
        visitFunc(fc->coroutine);
        cg.builder.restoreIP(cg.savedIP);
    }

    Type* ctxTy = nullptr;
    Value* ctx = nullptr;
    if (fc->args.empty()) {
        ctxTy = cg.ptrTy();
        ctx = cg.null();
    } else {
        ctxTy = getThunkCtxType(fc);
        ctx = getThunkCtx(fc, ctxTy);
    }
    cg.callRuntimeFunc("addCoro", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {getThunkFunc(fc, ctxTy), ctx});
}

void LgsCgFile::visitDeferStmt(const LgsDeferStmt* defer) {
    LgsFuncCall* fc = nullptr;
    if (defer->funcCall->name == "") {
        visitLambda(defer->funcCall->func);
        visitFuncCall(defer->funcCall);
        fc = defer->funcCall;
    } else if (defer->funcCall) {
        visitFuncCall(defer->funcCall);
        fc = defer->funcCall;
    } else if (defer->selection) {
        visitSelection(defer->selection);
        fc = defer->selection->asMethodCall();
    }
    Type* ctxTy = nullptr;
    Value* ctx = nullptr;
    if (fc->args.empty()) {
        ctxTy = cg.ptrTy();
        ctx = cg.null();
    } else {
        ctxTy = getThunkCtxType(fc);
        ctx = getThunkCtx(fc, ctxTy);
    }
    cg.callRuntimeFunc("addDefer", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {getThunkFunc(fc, ctxTy), ctx});
}

void LgsCgFile::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitExpr(ioStmt->varDec->expr);
    visitStmtsBlock(ioStmt->stmtsBlock);
}

void LgsCgFile::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        visitTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (checkMock(expr)) return;
        if (const auto func = expr->asFunc()) visitLambda(func);
        else if (const auto charConst = expr->asCharConst()) visitCharConst(charConst);
        else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
        else if (const auto intConst = expr->asIntConst()) visitIntConst(intConst);
        else if (const auto floatConst = expr->asFloatConst()) visitFloatConst(floatConst);
        else if (const auto instance = expr->asInstance()) visitInstance(instance);
        else if (const auto funcCall = expr->asFuncCall()) visitFuncCall(funcCall);
        else if (const auto selection = expr->asSelection()) visitSelection(selection);
        else if (const auto metaSelection = expr->asMetaSelection()) visitMetaSelection(metaSelection);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex);
        else if (const auto variable = expr->asVariable()) visitVariable(variable);
        else if (const auto envVar = expr->asEnvVar()) visitEnvVar(envVar);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto matrixExpr = expr->asMatrixExpr()) visitMatrixExpr(matrixExpr);
        else if (const auto loopMetaVar = expr->asLoopMetaVar()) visitLoopMetaVar(loopMetaVar);
        else if (const auto nullableExpr = expr->asNullableExpr()) visitNullableExpr(nullableExpr);
        else if (const auto cast = expr->asCast()) visitCast(cast);
    }
}

void LgsCgFile::visitBinaryExpr(LgsBinaryExpr* binExpr) {
    assert(binExpr->type);
    const auto l = binExpr->left;
    const auto r = binExpr->right;
    visitExpr(l);
    visitExpr(r);
    const auto type = binExpr->type;
    switch (binExpr->op.opType) {
    case ADD: binExpr->IRValue = type->addIR(cg, binExpr); break;
    case SUB: binExpr->IRValue = type->subIR(cg, binExpr); break;
    case MUL: binExpr->IRValue = type->mulIR(cg, binExpr); break;
    case DIV: binExpr->IRValue = type->divIR(cg, binExpr); break;
    case MODULO: binExpr->IRValue = type->modIR(cg, binExpr); break;
    case POW: binExpr->IRValue = type->powIR(cg, binExpr); break;
    case BIT_AND: binExpr->IRValue = type->bitAndIR(cg, binExpr); break;
    case BIT_OR: binExpr->IRValue = type->bitOrIR(cg, binExpr); break;
    case BIT_XOR: binExpr->IRValue = type->bitXorIR(cg, binExpr); break;
    case LSHIFT: binExpr->IRValue = type->rshiftIR(cg, binExpr); break;
    case RSHIFT: binExpr->IRValue = type->lshiftIR(cg, binExpr); break;
    case EQ: binExpr->IRValue = eqIR(cg, l->loadIR(cg), r->loadIR(cg), l->type); break;
    case NE: binExpr->IRValue = neIR(cg, l->loadIR(cg), r->loadIR(cg), l->type); break;
    case LT: binExpr->IRValue = ltIR(cg, l->loadIR(cg), r->loadIR(cg), l->type); break;
    case GT: binExpr->IRValue = gtIR(cg, l->loadIR(cg), r->loadIR(cg), l->type); break;
    case GE: binExpr->IRValue = geIR(cg, l->loadIR(cg), r->loadIR(cg), l->type); break;
    case LE: binExpr->IRValue = leIR(cg, l->loadIR(cg), r->loadIR(cg), l->type); break;
    case AND: binExpr->IRValue = andIR(cg, l->loadIR(cg), r->loadIR(cg)); break;
    case OR: binExpr->IRValue = orIR(cg, l->loadIR(cg), r->loadIR(cg)); break;
    case IN: binExpr->IRValue = r->type->asIterable()->inIR(cg, r->IRValue, l->IRValue); break;
    case CROSS: binExpr->IRValue = crossIR(cg, binExpr->left->IRValue, binExpr->right->IRValue, type->asVec()); break;
    default: assert(0);
    }
}

void LgsCgFile::visitTernaryExpr(LgsTernaryExpr* ternaryExpr) {
    const auto cond = ternaryExpr->condExpr;
    const auto then = ternaryExpr->thenExpr;
    const auto else_ = ternaryExpr->elseExpr;
    visitExpr(cond);
    visitExpr(then);
    visitExpr(else_);
    ternaryExpr->IRValue = cg.builder.CreateSelect(cond->IRValue, then->IRValue, else_->IRValue);
}

void LgsCgFile::visitInstance(LgsInstance* instance) {
    const auto obj = instance->obj;
    if (obj->isExternal) {
        instance->IRValue = cg.builder.CreateAlloca(obj->getIRType(cg));
        assert(instance->args.empty());
        return;
    }

    instance->IRValue = obj->getIRZeroValue(cg, instance->pointee);
    // Args
    std::unordered_set<std::string> visited;
    for (const auto& [argName, arg] : instance->args) {
        visited.insert(argName);
        const auto field = instance->getField(argName);
        arg.expr->pointee = field->getGEP(cg, instance->IRValue);
        visitExpr(arg.expr);
        cg.store(arg.expr->IRValue, arg.expr->pointee);
    }

    // Zero values
    for (const auto field : instance->fields) {
        const auto fieldType = field->type;
        if (visited.contains(field->name) || fieldType->asEnum()) continue;
        const auto pointee = field->getGEP(cg, instance->IRValue);
        cg.store(field->type->getIRZeroValue(cg, pointee), pointee);
    }
}

void LgsCgFile::visitConstant(LgsExpr* expr) {
    if (const auto charConst = expr->asCharConst()) visitCharConst(charConst);
    else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
    else if (const auto intConst = expr->asIntConst()) visitIntConst(intConst);
    else if (const auto floatConst = expr->asFloatConst()) visitFloatConst(floatConst);
    else assert(0);
}

void LgsCgFile::visitFloatConst(LgsFloatConst* floatConst) {
    if (floatConst->type->asFloat()) {
        floatConst->IRValue = cg.floatv(floatConst->value);
    } else if (floatConst->type->asDouble()) {
        floatConst->IRValue = cg.doublev(floatConst->value);
    } else {
        assert(0);
    }
}

void LgsCgFile::visitIntConst(LgsIntConst* intConst) {
    if (intConst->type->asBool()) {
        intConst->IRValue = cg.i1(intConst->value);
    } else if (intConst->type->asChar()) {
        intConst->IRValue = cg.i8(intConst->value);
    } else if (intConst->type->asShort()) {
        intConst->IRValue = cg.i16(intConst->value);
    } else if (intConst->type->asInt()) {
        intConst->IRValue = cg.i32(intConst->value);
    } else if (intConst->type->asLong()) {
        intConst->IRValue = cg.i64(intConst->value);
    } else if (intConst->type->asSize()) {
        intConst->IRValue = cg.usize(intConst->value);
    } else if (intConst->type->asFloat()) {
        intConst->IRValue = cg.floatv(intConst->value);
    } else {
        assert(0);
    }
}

void LgsCgFile::visitStrConst(LgsStrConst* strConst) {
    if (strConst->parts.empty()) {
        strConst->IRValue = cg.allocStrConst(cg.getString(strConst->value));
        return;
    }

    for (const auto parts : strConst->parts) {
        visitExpr(parts);
    }
    auto formatted = strConst->formatedStr;
    std::vector<Value*> values;
    for (const auto part : strConst->parts) {
        auto partIR = part->loadIR(cg);
        values.push_back(partIR);
        const auto pos = formatted.find(LGS_STR_FMT_PLACEHOLDER);
        if (pos != std::string::npos) {
            formatted.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->fmtStr());
        }
    }
    strConst->IRValue = cg.callSnprintf(formatted + "\n", values);
}

void LgsCgFile::visitCharConst(LgsCharConst* charConst) {
    charConst->IRValue = cg.i8(charConst->value);
}

void LgsCgFile::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    visitExpr(prefixExpr->expr);
    const auto exprIRVal = prefixExpr->expr->IRValue;
    switch (prefixExpr->op) {
    case NOT_PREFIX: {
        prefixExpr->IRValue = cg.builder.CreateNot(exprIRVal);
        break;
    }
    case MINUS_PREFIX: {
        const auto zero = ConstantInt::get(prefixExpr->type->getIRType(cg), 0);
        prefixExpr->IRValue = cg.builder.CreateSub(zero, exprIRVal);
        break;
    }
    case SQRT_PREFIX: {
        auto d = cg.builder.CreateSIToFP(exprIRVal, cg.doubleTy());
        prefixExpr->IRValue = cg.callFunc("sqrt", cg.doubleTy(), {cg.doubleTy()}, {d});
        break;
    }
    }
}

void LgsCgFile::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->baseExpr;
    visitExpr(baseExpr);
    postfixExpr->IRValue = postfixExpr->baseExpr->loadIR(cg);
    assert(baseExpr->IRValue->getType()->isPointerTy());
    const auto baseExprType = postfixExpr->baseExpr->type->getIRType(cg);
    const auto one = ConstantInt::get(baseExprType, 1, true);
    Value* newValue = nullptr;
    switch (postfixExpr->op) {
    case INC: {
        newValue = cg.builder.CreateAdd(postfixExpr->IRValue, one);
        break;
    }
    case DEC: {
        newValue = cg.builder.CreateSub(postfixExpr->IRValue, one);
        break;
    }
    }
    cg.store(newValue, postfixExpr->baseExpr->IRValue);
}

void LgsCgFile::visitVariable(LgsVariable* variable) {
    switch (variable->ref.symbolType) {
    case VAR_DEC:
        assert(variable->ref.varDec->IRValue);
        variable->IRValue = variable->ref.varDec->IRValue;
        break;
    case PARAM:
        if (variable->ref.param->isSelf) {
            variable->IRValue = cg.currentFunc->getArg(0);
        } else {
            assert(variable->ref.param->IRValue);
            variable->IRValue = variable->ref.param->IRValue;
        }
        break;
    case FUNC:
        variable->IRValue = variable->ref.func->getIRFunc(cg);
        break;
    case OBJECT:
        if (!variable->ref.object->singleton) return;
        variable->IRValue = variable->ref.object->singleton->IRValue;
        break;
    case FIELD:
        if (variable->ref.field->type->asEnum()) {
            variable->IRValue = cg.usize(variable->ref.field->position);
        } else {
            variable->IRValue = variable->pointee;
        }
        break;
    case GENERIC:
    case ENUM:
    case INTERFACE:
    case SUBTYPE:
        return;
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCgFile::visitNullableExpr(LgsNullableExpr* expr) {
    const auto nullable = expr->type->asNullable();
    assert(nullable);
    visitExpr(expr->baseExpr);
    if (expr->isNull) {
        expr->IRValue = nullable->getIRZeroValue(cg, expr->pointee);
    } else {
        if (nullable->passByRef) {
            if (expr->pointee) cg.store(expr->baseExpr->IRValue, expr->pointee);
            expr->IRValue = expr->baseExpr->IRValue;
        } else {
            expr->IRValue = nullable->getIRZeroValue(cg, expr->pointee);
            nullable->setIRFields(cg, expr->IRValue, expr->baseExpr->loadIR(cg), cg.true_());
        }
    }
}

void LgsCgFile::visitIterIndex(LgsIterIndex* iterIndex) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto iterable = baseExpr->type->asIterable();
    const auto from = iterIndex->index.from;
    const auto to = iterIndex->index.to;
    assert(iterable && !iterIndex->pointee);
    visitExpr(baseExpr);
    visitExpr(from);
    visitExpr(to);
    if (to) {
        iterIndex->IRValue = iterIndex->getIRRangePtr(cg);
    } else {
        const auto baseExprValue = baseExpr->pointee ? baseExpr->pointee : baseExpr->IRValue;
        iterIndex->IRValue = iterable->getIRElement(cg, baseExprValue, from->IRValue);
    }
}

void LgsCgFile::visitSelection(LgsSelection* selection) {
    visitExpr(selection->exprs.front());
    const auto iterationCount = selection->exprs.size() - 1;
    for (size_t i = 0; i < iterationCount; ++i) {
        const auto parent = selection->exprs[i];
        const auto child = selection->exprs[i + 1];
        // cg.createNullPtrGuard(cg.loadPtr(parent->IRValue));
        if (const auto var = child->asVariable()) {
            visitFieldSelection(var, parent);
        } else if (const auto nullableExpr = child->asNullableExpr()) {
            visitNullableSelection(nullableExpr, parent);
        } else if (const auto methodCall = child->asFuncCall()) {
            if (methodCall->isMock) continue;
            visitFuncCall(methodCall);
        } else if (const auto metaSelection = child->asMetaSelection()) {
            visitMetaSelection(metaSelection);
        } else if (const auto instance = child->asInstance()) {
            visitInstance(instance);
        } else {
            assert(0);
        }
        if (i < iterationCount - 1 && child->type->passByRef) {
            child->IRValue = cg.loadPtr(child->IRValue);
        }
    }
    selection->IRValue = selection->exprs.back()->IRValue;
}

void LgsCgFile::visitFieldSelection(LgsVariable* var, LgsExpr* parent) {
    const auto field = var->ref.field;
    const auto fieldType = field->type;

    // Function pointer
    if (var->ref.symbolType == FUNC) {
        var->IRValue = var->ref.func->getIRFunc(cg);
        return;
    }

    // Enum field
    if (const auto enum_ = var->type->asEnum()) {
        if (field->expr) {
            var->IRValue = UndefValue::get(enum_->getIRType(cg));
            var->IRValue = cg.builder.CreateInsertValue(var->IRValue, cg.usize(enum_->fieldIndex), 0);
            var->IRValue = cg.builder.CreateInsertValue(var->IRValue, field->expr->IRValue, 1);
        } else {
            var->IRValue = cg.usize(enum_->fieldIndex);
        }
        return;
    }

    // Singleton
    if (parent->asTypeExpr() && parent->type->asObject()->singleton) {
        assert(0);
    }

    // Virtual fields
    if (field->isVirtual) {
        const auto ty = parent->type->getIRType(cg);
        const auto rttType = LgsInstance::loadRTType(cg, ty, parent->IRValue);
        var->IRValue = cg.getVField(rttType, parent->IRValue, cg.getString(field->name));
        return;
    }

    // Vector
    if (fieldType->asVec()) {
        createVecField(field, parent->IRValue);
    }
    var->IRValue = field->getGEP(cg, parent->IRValue);
}

void LgsCgFile::visitNullableSelection(LgsExpr* child, LgsExpr* parent) {
    assert(parent->type->asNullable());
    const auto field = child->asNullableExpr()->baseExpr->asVariable()->ref.field;
    const auto isNullBlock = cg.createBlock(BLOCK_TRUE);
    const auto isNotNullBlock = cg.createBlock(BLOCK_FALSE);
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);

    child->IRValue = cg.builder.CreateAlloca(cg.ptrTy());
    const auto condition = cg.builder.CreateIsNull(parent->loadIR(cg));
    cg.builder.CreateCondBr(condition, isNullBlock, isNotNullBlock);

    // isNull block
    cg.startBlock(isNullBlock);
    cg.store(cg.null(), child->IRValue);
    cg.builder.CreateBr(exitBlock);

    // isNotNull block
    cg.startBlock(isNotNullBlock);
    cg.store(field->getGEP(cg, parent->IRValue), child->IRValue);

    // exit block
    cg.branchAndStartBlock(exitBlock);
}

void LgsCgFile::visitMetaSelection(LgsMetaSelection* metaSelection) {
    visitExpr(metaSelection->baseExpr);
    if (const auto fc = metaSelection->child->asFuncCall()) {
        visitFuncCall(fc);
        metaSelection->IRValue = fc->IRValue;
        return;
    }
    if (const auto var = metaSelection->child->asVariable()) {
        const auto field = var->ref.field;
        visitExpr(field->expr);
        metaSelection->IRValue = field->expr->IRValue;
        return;
    }
    assert(0);
}

void LgsCgFile::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        if (arg.isSelf) continue;
        visitExpr(arg.expr);
    }

    // Function pointer
    if (funcCall->ref.symbolType != UNKNOWN) {
        LgsType* type = nullptr;
        const LgsValue* value = nullptr;
        if (funcCall->ref.symbolType == PARAM) {
            type = funcCall->ref.param->type;
            value = funcCall->ref.param;
        } else if (funcCall->ref.symbolType == VAR_DEC) {
            type = funcCall->ref.varDec->type;
            value = funcCall->ref.varDec;
        }
        funcCall->func = new LgsFunc(type->asFuncType());
        funcCall->func->IRValue = value->IRValue;
    }
    assert(funcCall->func || funcCall->coroutine);
    const auto func = funcCall->func ? funcCall->func : funcCall->coroutine;
    const auto ft = func->funcType;
    assert(func->funcType->genericTypes.empty());

    // Default params
    if (ft->hasDefaults) {
        const auto diff = ft->params.size() - funcCall->args.size() - 1;
        for (size_t i = diff; i < ft->params.size(); ++i) {
            visitExpr(ft->params[i].expr);
        }
    }

    // Virtual func call
    if (ft->isVirtual) {
        const auto self = funcCall->args.front().expr;
        const auto offset = cg.getTypeSize(cg.sizeTy());
        const auto rttType = cg.builder.CreatePtrAdd(self->IRValue, offset);
        const auto objType = loadRTTInfoExtra(cg, cg.loadPtr(rttType));
        func->IRValue = cg.getVFunc(objType, cg.getString(ft->name));
    }

    if (funcCall->coroutine || funcCall->isDeferred) return;
    funcCall->IRValue = func->call(cg, funcCall->args);
}

void LgsCgFile::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    if (arrayExpr->type->asSArray()) {
        visitStaticArray(arrayExpr);
    } else if (arrayExpr->type->asDArray() || arrayExpr->type->asSet()) {
        visitDynamicArray(arrayExpr);
    } else {
        assert(0);
    }
}

void LgsCgFile::visitStaticArray(LgsArrayExpr* arrayExpr) {
    const auto sArr = arrayExpr->type->asSArray();
    const auto ty = sArr->getIRType(cg);
    arrayExpr->IRValue = sArr->getIRZeroValue(cg, arrayExpr->pointee);
    if (arrayExpr->elements.empty()) {
        cg.store(ConstantAggregateZero::get(ty), arrayExpr->IRValue);
        return;
    }

    // Init with zero the remaining args that are not set by the user.
    if (!arrayExpr->pointee && arrayExpr->elements.size() < sArr->len) {
        cg.store(ConstantAggregateZero::get(ty), arrayExpr->IRValue);
    }

    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        element->pointee = sArr->getIRElement(cg, arrayExpr->IRValue, cg.i32(i));
        visitExpr(element);
    }

    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        cg.store(element->IRValue, element->pointee);
    }
}

void LgsCgFile::visitDynamicArray(LgsArrayExpr* arrayExpr) {
    for (const auto element : arrayExpr->elements) {
        visitExpr(element);
    }
    const auto dArr = arrayExpr->type->asDArray();
    arrayExpr->IRValue = dArr->getIRZeroValue(cg, arrayExpr->pointee);
    for (const auto element : arrayExpr->elements) {
        dArr->addIRElement(cg, arrayExpr->IRValue, nullptr, element->IRValue);
    }
}

void LgsCgFile::visitVectorExpr(LgsVectorExpr* vecExpr) {
    const auto vecType = vecExpr->vecType;
    if (vecExpr->elements.empty()) {
        vecExpr->IRValue = vecType->getIRZeroValue(cg, vecExpr->pointee);
        return;
    }

    // Single scalar element
    if (vecExpr->elements.size() == 1) {
        const auto expr = vecExpr->elements.front();
        if (expr->type->isScalar()) {
            visitExpr(expr);
            const auto newVec = cg.builder.CreateVectorSplat(vecType->dimVec, expr->IRValue);
            if (vecExpr->pointee) {
                vecExpr->IRValue = vecExpr->pointee;
                cg.store(newVec, vecExpr->IRValue);
            } else {
                vecExpr->IRValue = cg.allocaAndStore(vecType->getIRType(cg), newVec);
            }
            return;
        }
    }

    // Multiple elements
    vecExpr->IRValue = vecExpr->vecType->getIRZeroValue(cg, vecExpr->pointee);
    for (size_t i = 0; i < vecExpr->elements.size(); ++i) {
        const auto element = vecExpr->elements[i];
        assert(!element->type->asVec());
        element->pointee = vecType->getIRElement(cg, vecExpr->IRValue, cg.i32(i));
        visitExpr(element);
        cg.store(element->IRValue, element->pointee);
    }
}

void LgsCgFile::visitMatrixExpr(const LgsMatrixExpr* matrixExpr) {
    if (!matrixExpr->IRValue) return;
    auto allArgsConst = true;
    std::vector<Constant*> constantArgs;
    for (size_t i = 0; i < matrixExpr->elements.size(); ++i) {
        const auto vector = matrixExpr->elements[i];
        for (size_t j = 0; j < vector->elements.size(); ++j) {
            const auto element = vector->elements[j];
            visitExpr(element);
            if (const auto constant = llvm::dyn_cast<Constant>(element->IRValue)) {
                constantArgs.push_back(constant);
            } else {
                allArgsConst = false;
            }
        }
    }

    const auto matTypeIR = matrixExpr->type->getIRType(cg);
    if (allArgsConst) {
        const auto matArrayType = llvm::dyn_cast<ArrayType>(matTypeIR);
        const auto constantMatrix = ConstantArray::get(matArrayType, constantArgs);
        cg.store(constantMatrix, matrixExpr->IRValue);
    } else {
        auto index = 0;
        for (size_t i = 0; i < matrixExpr->elements.size(); ++i) {
            const auto vector = matrixExpr->elements[i];
            for (size_t j = 0; j < vector->elements.size(); ++j) {
                const auto element = vector->elements[j];
                const std::vector<Value*> indices = {cg.zero32(), cg.i32(index++)};
                const auto gep = cg.builder.CreateInBoundsGEP(matTypeIR, matrixExpr->IRValue, indices);
                cg.store(element->IRValue, gep);
            }
        }
    }
}

void LgsCgFile::visitHashMap(LgsHashMap* hashMap) {
    const auto map = hashMap->type->asMap();
    hashMap->IRValue = hashMap->type->getIRZeroValue(cg, hashMap->pointee);
    for (const auto pair : hashMap->elements) {
        visitExpr(pair->key);
        visitExpr(pair->value);
        map->addIRElement(cg, hashMap->IRValue, pair->key->IRValue, pair->value->IRValue);
    }
}

void LgsCgFile::visitEnvVar(LgsEnvVar* envVar) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {cg.getString(envVar->name), cg.emptyStr()};
    envVar->IRValue = cg.callLgsFunc(LgsSys::name, "getEnv", cg.ptrTy(), params, IRArgs);
}

void LgsCgFile::visitCast(LgsCast* cast) {
    assert(cast->value);
    visitExpr(cast->value);
    cast->IRValue = cast->value->IRValue;
}

void LgsCgFile::visitLambda(LgsFunc* func) {
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    func->IRValue = func->getIRFunc(cg);
    visitFunc(func);
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
}

void LgsCgFile::createPrologue(LgsFunc* func) {
    if (appConfigs->debugMode) func->setDebugValue(cg);
    cg.currentFunc = func->getIRFunc(cg);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    func->epilogue = cg.createBlock("epilogue");
    cg.builder.SetInsertPoint(entryBlock);
    if (func->funcType->name == LGS_MAIN_FUNC) {
        cg.callRuntimeFunc("init", cg.voidTy());
        startTime = cg.measureTimeStart();
    }
    cg.callStackPush();
}

void LgsCgFile::createEpilogue(const LgsFunc* func) {
    const auto ft = func->funcType;
    if (ft->name == LGS_MAIN_FUNC) {
        cg.callPopStack();
        cg.callRuntimeFunc("close", cg.voidTy());
        cg.callPrintf("Time taken: %zuns\n", {cg.measureTimeEnd(startTime)});
        cg.builder.CreateRet(cg.i32(EXIT_SUCCESS));
    } else if (ft->rt->isVoid() && !cg.lastInstTerminator()) {
        cg.callPopStack();
        cg.builder.CreateRetVoid();
    } else if (func->returnStmts.size() > 1) {
        cg.branchAndStartBlock(func->epilogue);
        const auto phi = cg.builder.CreatePHI(ft->rt->getTypeOrPtr(cg), func->returnStmts.size());
        for (const auto returnStmt : func->returnStmts) {
            phi->addIncoming(returnStmt->expr->IRValue, returnStmt->parentBlock);
        }
        cg.callPopStack();
        cg.builder.CreateRet(phi);
    }
}

void LgsCgFile::initMainArgs(const LgsMainFunc* mainFunc) {
    const auto ft = mainFunc->funcType;
    if (ft->params.empty()) return;
    const auto argsArray = ft->params.front().expr->asArrayExpr();
    const auto sArray = argsArray->type->asSArray();
    sArray->lengthExpr->IRValue = cg.currentFunc->getArg(0);
    argsArray->IRValue = cg.currentFunc->getArg(1);
    mainFunc->funcType->params[0].IRValue = argsArray->IRValue;
}

StructType* LgsCgFile::getThunkCtxType(const LgsFuncCall* fc) {
    std::vector<Value*> args;
    std::vector<Type*> types;
    for (const auto& arg : fc->args) {
        types.push_back(arg.expr->type->getIRType(cg));
    }
    return cg.getStructType(types, fc->name + "ThunkType");
}

Value* LgsCgFile::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) {
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (size_t i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i].expr->IRValue;
        cg.storeStructField(ctxTy, ctx, i, v);
    }
    return ctx;
}

Function* LgsCgFile::getThunkFunc(LgsFuncCall* fc, Type* ctxTy) {
    auto thunkFunc = cg.IRModule->getFunction(fc->name + "Thunk");
    if (thunkFunc) return thunkFunc;
    cg.savedIP = cg.builder.saveIP();

    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy()});
    thunkFunc = cg.getFunc(fc->name + "Thunk", ft, Function::PrivateLinkage);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY);
    entryBlock->insertInto(thunkFunc);
    cg.builder.SetInsertPoint(entryBlock);

    for (size_t i = 0; i < fc->args.size(); i++) {
        fc->args[i].expr->IRValue = cg.builder.CreateStructGEP(ctxTy, thunkFunc->arg_begin(), i);
    }
    const auto func = fc->coroutine ? fc->coroutine : fc->func;
    func->call(cg, fc->args);
    cg.builder.CreateRetVoid();
    cg.builder.restoreIP(cg.savedIP);
    return thunkFunc;
}

void LgsCgFile::moveValue(LgsType* type, Value* left, Value* right) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    if (type->asStr()) {
        const std::vector args = {left, right};
        cg.callRuntimeFunc("moveStr", cg.voidTy(), params, args);
    } else if (type->asObject()) {
        const std::vector args = {left, right};
        cg.callRuntimeFunc("moveObject", cg.voidTy(), params, args);
    } else if (type->asDArray()) {
        const std::vector args = {left, right};
        cg.callRuntimeFunc("moveArr", cg.voidTy(), params, args);
    } else if (const auto nullable = type->asNullable()) {
        moveValue(nullable->baseType, left, right);
    } else if (type->asMap()) {
        assert(0);
    } else {
        assert(0);
    }
}

void LgsCgFile::createVecField(LgsField* field, Value* parent) {
    const auto vec = field->type->asVec();
    assert(vec);
    std::vector<int> mask(vec->dimVec);
    for (size_t i = 0; i < vec->dimVec; i++) {
        mask[i] = LgsVec::getComponentIndex(field->name[i]);
    }
    const auto vecType = field->type->getIRType(cg);
    field->IRValue = cg.builder.CreateAlloca(vecType);
    const auto parentTy = field->parentType->getIRType(cg);
    const auto l = cg.load(parentTy, parent);
    const auto newVec = cg.builder.CreateShuffleVector(l, UndefValue::get(parentTy), mask);
    cg.store(newVec, field->IRValue);
}

bool LgsCgFile::checkMock(LgsExpr* expr) {
    if (stack.stack.empty()) return false;
    const auto currentFunc = stack.currentFunc();
    if (currentFunc->isTest) {
        for (auto [when, then] : currentFunc->mocks) {
            if (!when->equals(expr)) continue;
            expr->IRValue = then->IRValue;
            return true;
        }
    }
    return false;
}

void LgsCgFile::getMapFunc(LgsFuncType* mapFunc) {
    const auto& iterableParam = mapFunc->params[0];
    const auto& cbParam = mapFunc->params[1];
    const auto iterable = iterableParam.type->asIterable();
    const auto funcName = mapFunc->getName();

    const auto ft = llvm::cast<FunctionType>(mapFunc->getIRType(cg));
    const auto cbFt = llvm::cast<FunctionType>(cbParam.type->getIRType(cg));
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto iter = func->getArg(0);
    const auto cb = func->getArg(1);

    LgsDArray dArr(iterable->baseType);
    LgsArrayExpr retArr(&dArr);
    visitArrayExpr(&retArr);
    const auto len = iterable->lenIR(cg, iter);

    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto element = iterable->getIRElement(cg, iter, iValue);
        const auto loadElement = cg.load(iterable->baseType->getIRType(cg), element);
        const auto results = cg.builder.CreateCall(cbFt, cb, {loadElement});
        dArr.addIRElement(cg, retArr.IRValue, nullptr, results);
    });

    cg.callPopStack();
    cg.builder.CreateRet(retArr.IRValue);
}

void LgsCgFile::getFilterFunc(LgsFuncType* filterFunc) {
    const auto& iterableParam = filterFunc->params[0];
    const auto& cbParam = filterFunc->params[1];
    const auto iterable = iterableParam.type->asIterable();
    const auto funcName = filterFunc->getName();

    const auto ft = llvm::cast<FunctionType>(filterFunc->getIRType(cg));
    const auto cbFt = llvm::cast<FunctionType>(cbParam.type->getIRType(cg));
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto iter = func->getArg(0);
    const auto cb = func->getArg(1);

    LgsDArray dArr(iterable->baseType);
    LgsArrayExpr retArr(&dArr);
    visitArrayExpr(&retArr);
    const auto len = iterable->lenIR(cg, iter);

    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto baseTy = iterable->baseType->getIRType(cg);
        const auto element = iterable->getIRElement(cg, iter, iValue);
        const auto loadElement = cg.load(baseTy, element);
        const auto results = cg.builder.CreateCall(cbFt, cb, {loadElement});
        cg.ifStmt(results, [&] {
            dArr.addIRElement(cg, retArr.IRValue, nullptr, cg.load(baseTy, element));
        });
    });

    cg.callPopStack();
    cg.builder.CreateRet(retArr.IRValue);
}

void LgsCgFile::getForeachFunc(LgsFuncType* forEachFunc) {
    const auto& iterableParam = forEachFunc->params[0];
    const auto& cbParam = forEachFunc->params[1];
    const auto iterable = iterableParam.type->asIterable();
    const auto funcName = forEachFunc->getName();

    const auto ft = llvm::cast<FunctionType>(forEachFunc->getIRType(cg));
    const auto cbFt = llvm::cast<FunctionType>(cbParam.type->getIRType(cg));
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto iter = func->getArg(0);
    const auto cb = func->getArg(1);

    const auto len = iterable->lenIR(cg, iter);
    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto element = iterable->getIRElement(cg, iter, iValue);
        const auto loadElement = cg.load(iterable->baseType->getIRType(cg), element);
        cg.builder.CreateCall(cbFt, cb, {loadElement});
    });

    cg.callPopStack();
    cg.builder.CreateRetVoid();
}
