#include "codegen/LgsCodeGen.h"
#include "builtins/LgsTest.h"
#include "LgsConfigs.h"
#include "exprs/constants/LgsComplexConst.h"
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
#include "exprs/LgsJson.h"
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
#include <llvm/IR/Module.h>
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <unistd.h>
#include <unordered_set>
#include "cblas/cblas.h"
#include "exprs/LgsMatrixExpr.h"
#include "exprs/LgsMetaSelection.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/LgsNullable.h"

bool LgsCodeGen::generate() {
    cg.setupModule(file.path, appConfigs.debugMode);
    visitExternalSymbols();
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterface(interfaceFile->interface);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(&file)) {
        visitTestFile(testFile);
    }
    if (appConfigs.debugMode) cg.finalizeDebugger(paths.buildDir);
    return cg.writeIRModule(paths, appConfigs.optLevel);
}

void LgsCodeGen::visitMainFile(LgsMainFile* mainFile) {
    for (const auto varDec : mainFile->varDecs) {
        visitConstant(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    }
    for (const auto& [_, symbol] : globals.table.symbols) {
        if (symbol.symbolType != VAR_DEC) continue;
        visitConstant(symbol.varDec->expr);
        symbol.varDec->IRValue = symbol.varDec->expr->IRValue;
    }
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto object : mainFile->objects) {
        visitObject(object);
    }
    for (auto [_, genericsCall] : file.symbolTable.genericFuncCalls) {
        visitFunc(genericsCall);
    }

    for (const auto& [name, func] : mainFile->funcs) {
        if (const auto mainFunc = dynamic_cast<LgsMainFunc*>(func)) {
            visitMainFunc(mainFunc);
        } else {
            visitFunc(func);
        }
    }
}

void LgsCodeGen::visitInterface(const LgsInterface* interface) {
    for (const auto& [_, method] : interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCodeGen::visitTestFile(const LgsTestFile* testFile) {
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

void LgsCodeGen::visitObject(LgsObject* obj) {
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

void LgsCodeGen::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    initMainArgs(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    stack.exitScope();
}

void LgsCodeGen::visitFunc(LgsFunc* func) {
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

void LgsCodeGen::visitExternalSymbols() {
    for (auto [name, symbol] : file.symbolTable.symbols) {
        if (symbol.symbolType == VAR_DEC && symbol.isExternal) {
            visitConstant(symbol.varDec->expr);
            symbol.varDec->IRValue = symbol.varDec->expr->IRValue;
        }
    }
}

void LgsCodeGen::visitStmt(LgsStmt* stmt) {
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

void LgsCodeGen::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    assert(stmtsBlock);
    for (const auto& stmt : stmtsBlock->stmts) {
        switch (stmt.wrapperType) {
        case LgsStmtWrapper::WrapperType::Object:
            visitObject(stmt.obj);
            break;
        case LgsStmtWrapper::WrapperType::Stmt:
            visitStmt(stmt.stmt);
            if (appConfigs.debugMode) stmt.stmt->setDebugValue(cg);
            break;
        case LgsStmtWrapper::WrapperType::Expr:
            visitExpr(stmt.expr);
            if (appConfigs.debugMode) stmt.expr->setDebugValue(cg);
            break;
        }
    }
}

void LgsCodeGen::visitLoop(LgsForLoop* loop) {
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
    if (stack.currentFunc()->funcType->isCoroutine) {
        cg.callRuntimeFunc("yield", cg.voidTy());
    }
    loop->incAndJumpToCond(cg);
    cg.startBlock(loop->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGen::visitRangeLoop(LgsRangeLoop* loop) {
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

void LgsCodeGen::visitForeachLoop(LgsForeachLoop* loop) {
    visitExpr(loop->iterExpr);
    const auto indexTy = cg.sizeTy();
    loop->iPtr = cg.allocaAndStore(indexTy, cg.sizeZero());
    loop->iterator = cg.allocaAndStore(cg.sizeTy(), loop->iPtr);
    cg.branchAndStartBlock(loop->IRCondBlock);

    const auto cond = cg.builder.CreateICmpSLT(loop->loadIndex(cg), loop->loopEnd(cg));
    cg.builder.CreateCondBr(cond, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    const auto iterable = loop->iterExpr->type->asIterable();
    iterable->unpackLoopIR(cg, loop);
}

void LgsCodeGen::visitInfiniteLoop(const LgsInfiniteLoop* loop) const {
    cg.branchAndStartBlock(loop->IRBodyBlock);
}

void LgsCodeGen::visitLoopMetaVar(LgsMetaVar* metaVar) const {
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

void LgsCodeGen::visitWhileLoop(const LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    // Condition
    cg.startBlock(loop->IRCondBlock);
    visitExpr(loop->condExpr);
    cg.builder.CreateCondBr(loop->condExpr->IRValue, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    cg.startBlock(loop->IRBodyBlock);
}

void LgsCodeGen::visitVarDec(LgsVarDec* varDec) {
    if (varDec->shouldAllocate()) {
        varDec->IRValue = cg.builder.CreateAlloca(varDec->type->getIRType(cg));
        varDec->expr->IRValue = varDec->IRValue;
        visitExpr(varDec->expr);
        if (varDec->expr->IRValue != varDec->IRValue) {
            cg.store(varDec->expr->IRValue, varDec->IRValue);
        }
    } else {
        visitExpr(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    }
    assert(varDec->IRValue);
    varDec->IRValue->setName(varDec->name);
}

void LgsCodeGen::visitAssignment(const LgsAssignment* assignment) {
    const auto lValue = assignment->lExpr;
    const auto rValue = assignment->rExpr;
    if (const auto iterIndex = lValue->asIterIndex()) {
        visitIterIndex(iterIndex, true);
    } else if (const auto var = lValue->asVariable()) {
        visitVariable(var);
    } else if (const auto selection = lValue->asSelection()) {
        visitSelection(selection, true);
    } else if (const auto nullable = lValue->asNullableExpr()) {
        visitExpr(nullable->baseExpr, true);
        nullable->IRValue = nullable->baseExpr->IRValue;
    }
    assignment->rExpr->pointee = assignment->lExpr->IRValue;
    visitExpr(assignment->rExpr, true);

    const Value* results = nullptr;
    switch (assignment->assignmentType.opType) {
    case ASSIGN: lValue->assign(cg, rValue); return;
    case ASSIGN_ADD: results = lValue->type->addIR(cg, lValue, rValue); break;
    case ASSIGN_SUB: results = lValue->type->subIR(cg, lValue, rValue); break;
    case ASSIGN_MUL: results = lValue->type->mulIR(cg, lValue, rValue); break;
    case ASSIGN_DIV: results = lValue->type->divIR(cg, lValue, rValue); break;
    case ASSIGN_MOD: results = lValue->type->modIR(cg, lValue, rValue); break;
    case ASSIGN_POW: results = lValue->type->powIR(cg, lValue, rValue); break;
    case ASSIGN_AND: results = lValue->type->bitAndIR(cg, lValue, rValue); break;
    case ASSIGN_OR: results = lValue->type->bitOrIR(cg, lValue, rValue); break;
    case ASSIGN_XOR: results = lValue->type->bitXorIR(cg, lValue, rValue); break;
    case ASSIGN_LSHIFT: results = lValue->type->lshiftIR(cg, lValue, rValue); break;
    case ASSIGN_RSHIFT: results = lValue->type->rshiftIR(cg, lValue, rValue); break;
    case ASSIGN_UNKNOWN: break;
    }
    assert(results);
}

void LgsCodeGen::visitIfStmt(LgsIfStmt* ifStmt) {
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

void LgsCodeGen::visitSimpleIf(LgsIfStmt* ifStmt) {
    stack.enterScope(ifStmt);
    visitExpr(ifStmt->ifCond);
    cg.ifStmt(ifStmt->ifCond->IRValue, [this, &ifStmt] {
        visitStmtsBlock(ifStmt->ifBlock);
    });
    stack.exitScope();
}

void LgsCodeGen::visitIfWithElse(LgsIfStmt* ifStmt) {
    const auto IRBlockTrue = cg.createBlock(BLOCK_TRUE);
    const auto IRBlockExit = cg.createBlock(BLOCK_EXIT);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockExit);
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    // else block
    stack.enterScope(ifStmt);
    cg.startBlock(IRBlockExit);
    visitStmtsBlock(ifStmt->elseBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGen::visitElseIf(LgsIfStmt* ifStmt) {
    auto IRBlockTrue = cg.createBlock(BLOCK_TRUE);
    auto IRBlockElseIfCheck = cg.createBlock(BLOCK_ELSE_IF_CHECK);
    const auto IRBlockExit = cg.createBlock(BLOCK_EXIT);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    for (size_t i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockElseIfCheck);
        const auto elseIfCondIR = getIRValue(expr);
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
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }

    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockExit);
        visitStmtsBlock(ifStmt->elseBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }
    cg.startBlock(ifStmt->IRExitBlock);
}

void LgsCodeGen::visitSwitch(LgsSwitch* switchStmt) {
    assert(switchStmt->cond);
    const auto defaultBlock = cg.createBlock("");
    const auto exitBlock = cg.createBlock("", cg.currentFunc);
    visitExpr(switchStmt->cond);

    const auto exprIRValue = switchStmt->cond->hashValue(cg);
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
        const auto patternBlock = cg.createBlock(BLOCK_CASE_PREFIX + std::to_string(i), cg.currentFunc);
        const auto hashed = expr->hashValue(cg);
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

void LgsCodeGen::visitContinueStmt() const {
    stack.currentLoop()->incAndJumpToCond(cg);
}

void LgsCodeGen::visitReturnStmt(LgsReturn* returnStmt) {
    visitExpr(returnStmt->expr);
    returnStmt->IRValue = returnStmt->expr ? returnStmt->expr->IRValue : nullptr;
    const auto currentFunc = stack.currentFunc();
    cg.callPopStack();
    if (currentFunc->funcType->rt->isVoid()) {
        cg.builder.CreateRetVoid();
    } else {
        cg.builder.CreateRet(returnStmt->expr->IRValue);
    }
}

void LgsCodeGen::visitBreakStmt(const LgsBreak* breakStmt) const {
    if (breakStmt->isBreakIf) {
        cg.builder.CreateBr(stack.getOutermostIfStmt()->IRExitBlock);
    } else if (breakStmt->tag != "") {
        cg.builder.CreateBr(stack.findTagExitBlock(breakStmt->tag));
    } else {
        const auto loop = stack.currentLoop();
        cg.builder.CreateBr(loop->IRExitBlock);
    }
}

void LgsCodeGen::visitCoroutine(const LgsCoroutine* coroutine) {
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

void LgsCodeGen::visitDeferStmt(const LgsDeferStmt* defer) {
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

void LgsCodeGen::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitExpr(ioStmt->varDec->expr);
    visitStmtsBlock(ioStmt->stmtsBlock);
}

void LgsCodeGen::visitExpr(LgsExpr* expr, const bool assign) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        if (iter->size && !iter->size->IRValue) {
            visitExpr(iter->size);
        }
    }
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
        else if (const auto complex = expr->asComplexConst()) visitComplexConst(complex);
        else if (const auto instance = expr->asInstance()) visitInstance(instance);
        else if (const auto funcCall = expr->asFuncCall()) visitFuncCall(funcCall);
        else if (const auto selection = expr->asSelection()) visitSelection(selection, assign);
        else if (const auto metaSelection = expr->asMetaSelection()) visitMetaSelection(metaSelection);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex, assign);
        else if (const auto variable = expr->asVariable()) visitVariable(variable);
        else if (const auto envVar = expr->asEnvVar()) visitEnvVar(envVar);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto matrixExpr = expr->asMatrixExpr()) visitMatrixExpr(matrixExpr);
        else if (const auto loopMetaVar = expr->asLoopMetaVar()) visitLoopMetaVar(loopMetaVar);
        else if (const auto nullableExpr = expr->asNullableExpr()) visitNullableExpr(nullableExpr);
        else if (const auto cast = expr->asCast()) visitCast(cast);
        else if (const auto json = expr->asJson()) visitJson(json);
    }
}

void LgsCodeGen::visitBinaryExpr(LgsBinaryExpr* binExpr) {
    assert(binExpr->type);
    const auto l = binExpr->left;
    const auto r = binExpr->right;
    visitExpr(l);
    visitExpr(r);
    switch (binExpr->op.opType) {
    case ADD: binExpr->IRValue = binExpr->type->addIR(cg, l, r); break;
    case SUB: binExpr->IRValue = binExpr->type->subIR(cg, l, r); break;
    case MUL: binExpr->IRValue = binExpr->type->mulIR(cg, l, r); break;
    case DIV: binExpr->IRValue = binExpr->type->divIR(cg, l, r); break;
    case MODULO: binExpr->IRValue = binExpr->type->modIR(cg, l, r); break;
    case POW: binExpr->IRValue = binExpr->type->powIR(cg, l, r); break;
    case BIT_AND: binExpr->IRValue = binExpr->type->bitAndIR(cg, l, r); break;
    case BIT_OR: binExpr->IRValue = binExpr->type->bitOrIR(cg, l, r); break;
    case BIT_XOR: binExpr->IRValue = binExpr->type->bitXorIR(cg, l, r); break;
    case LSHIFT: binExpr->IRValue = binExpr->type->rshiftIR(cg, l, r); break;
    case RSHIFT: binExpr->IRValue = binExpr->type->lshiftIR(cg, l, r); break;
    case CROSS: binExpr->IRValue = binExpr->type->crossIR(cg, l, r); break;
    case EQ: binExpr->IRValue = eqIR(cg, l, r); break;
    case NE: binExpr->IRValue = neIR(cg, l, r); break;
    case LT: binExpr->IRValue = ltIR(cg, l, r); break;
    case GT: binExpr->IRValue = gtIR(cg, l, r); break;
    case GE: binExpr->IRValue = geIR(cg, l, r); break;
    case LE: binExpr->IRValue = leIR(cg, l, r); break;
    case AND: binExpr->IRValue = andIR(cg, l, r); break;
    case OR: binExpr->IRValue = orIR(cg, l, r); break;
    case IN: binExpr->IRValue = r->type->asIterable()->inIR(cg, r, l); break;
    case NOOP: assert(0);
    }
}

void LgsCodeGen::visitTernaryExpr(LgsTernaryExpr* ternaryExpr) {
    const auto cond = ternaryExpr->condExpr;
    const auto then = ternaryExpr->thenExpr;
    const auto else_ = ternaryExpr->elseExpr;
    visitExpr(cond);
    visitExpr(then);
    visitExpr(else_);
    ternaryExpr->IRValue = cg.builder.CreateSelect(cond->IRValue, then->IRValue, else_->IRValue);
}

void LgsCodeGen::visitCast(LgsCast* cast) {
    assert(cast->value);
    visitExpr(cast->value);
    cast->IRValue = cast->value->IRValue;
}

void LgsCodeGen::visitLambda(LgsFunc* func) {
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;
    func->IRValue = func->getIRFunc(cg);
    visitFunc(func);
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
}

void LgsCodeGen::visitConstant(LgsExpr* expr) {
    if (const auto charConst = expr->asCharConst()) visitCharConst(charConst);
    else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
    else if (const auto intConst = expr->asIntConst()) visitIntConst(intConst);
    else if (const auto floatConst = expr->asFloatConst()) visitFloatConst(floatConst);
    else assert(0);
}

void LgsCodeGen::visitFloatConst(LgsFloatConst* floatConst) const {
    if (floatConst->type->asFloat()) {
        floatConst->IRValue = cg.floatv(floatConst->value);
    } else if (floatConst->type->asDouble()) {
        floatConst->IRValue = cg.doublev(floatConst->value);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitComplexConst(const LgsComplexConst* complex) {
    visitExpr(complex->real);
    visitExpr(complex->imaginary);
    cg.storeStructField(complex->type->getIRType(cg), complex->IRValue, 0, complex->real->IRValue);
    cg.storeStructField(complex->type->getIRType(cg), complex->IRValue, 1, complex->imaginary->IRValue);
}

void LgsCodeGen::visitNullableExpr(LgsNullableExpr* nullableExpr) {
    if (nullableExpr->baseExpr) {
        visitExpr(nullableExpr->baseExpr);
    }

    const auto nullable = nullableExpr->type->asNullable();
    const auto ty = nullable->getIRType(cg);
    if (nullableExpr->isNull) {
        if (nullable->passByRef) {
            nullableExpr->IRValue = cg.null();
        } else {
            nullableExpr->IRValue = nullableExpr->pointee ? nullableExpr->pointee : cg.builder.CreateAlloca(ty);
            nullable->storeIsSet(cg, nullableExpr->IRValue, cg.false_());
        }
    } else if (nullable->passByRef) {
        nullableExpr->IRValue = nullableExpr->baseExpr->IRValue;
    } else {
        nullableExpr->IRValue = nullableExpr->pointee ? nullableExpr->pointee : cg.builder.CreateAlloca(ty);
        const auto isSet = cg.builder.CreateIsNotNull(nullableExpr->baseExpr->IRValue);
        nullable->setNullableFields(cg, nullableExpr->IRValue, nullableExpr->baseExpr->loadIR(cg), isSet);
    }
}

void LgsCodeGen::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    for (const auto element : arrayExpr->elements) {
        visitExpr(element);
    }
    if (arrayExpr->type->asSArray()) {
        visitStaticArray(arrayExpr);
    } else if (arrayExpr->type->asDArray() || arrayExpr->type->asSet()) {
        visitDynamicArray(arrayExpr);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitStaticArray(LgsArrayExpr* arrayExpr) const {
    const auto sArr = arrayExpr->type->asSArray();
    const auto sArrTypeIR = sArr->getIRType(cg);
    if (arrayExpr->elements.empty()) {
        arrayExpr->IRValue = sArr->getIRZeroValue(cg, arrayExpr->pointee);
        return;
    }

    if (arrayExpr->pointee) {
        arrayExpr->IRValue = arrayExpr->pointee;
    } else {
        arrayExpr->IRValue = cg.builder.CreateAlloca(sArrTypeIR);
    }

    // Check if all args are const for chunk copy
    std::vector<Constant*> constantArgs;
    auto allArgsAreConst = true;
    for (const auto element : arrayExpr->elements) {
        if (const auto constant = llvm::dyn_cast<Constant>(element->IRValue)) {
            constantArgs.push_back(constant);
        } else {
            allArgsAreConst = false;
            break;
        }
    }

    if (allArgsAreConst) {
        const auto sArrTy = llvm::dyn_cast<ArrayType>(sArrTypeIR);
        const auto argsIR = ConstantArray::get(sArrTy, constantArgs);
        cg.store(argsIR, arrayExpr->IRValue);
    } else {
        if (sArr->baseType->asSArray()) return; // Nested arrays are handled before
        LgsIntConst temp(&LGS_INT, 0);
        for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
            const auto element = arrayExpr->elements[i];
            temp.IRValue = cg.i32(i);
            sArr->addIRElement(cg, arrayExpr, &temp, element);
        }
    }

    // Init rest of the values with zero
    const size_t arrSize = sArr->size->getConstInt().value();
    const auto tempExpr = sArr->baseType->getZeroValue();
    LgsIntConst index(&LGS_INT, 0);
    for (size_t i = arrayExpr->elements.size(); i < arrSize; ++i) {
        index.IRValue = cg.i32(i);
        tempExpr->IRValue = sArr->baseType->getIRZeroValue(cg);
        sArr->addIRElement(cg, arrayExpr, &index, tempExpr);
    }
    freeExpr(tempExpr);
}

void LgsCodeGen::visitDynamicArray(LgsArrayExpr* arrayExpr) const {
    const auto dArr = arrayExpr->type->asDArray();
    arrayExpr->IRValue = dArr->getIRZeroValue(cg, arrayExpr->pointee);
    for (const auto element : arrayExpr->elements) {
        dArr->addIRElement(cg, arrayExpr, nullptr, element);
    }
}

void LgsCodeGen::visitVectorExpr(LgsVectorExpr* vectorExpr) {
    const auto ty = vectorExpr->type->getIRType(cg);
    if (vectorExpr->elements.empty()) {
        vectorExpr->IRValue = ConstantAggregateZero::get(ty);
        return;
    }

    // Check if all args are const for chunk copy
    std::vector<Constant*> constantArgs;
    auto allArgsAreConst = true;
    for (const auto element : vectorExpr->elements) {
        visitExpr(element);
        if (const auto constant = llvm::dyn_cast<Constant>(element->IRValue)) {
            constantArgs.push_back(constant);
        } else {
            allArgsAreConst = false;
            break;
        }
    }

    if (allArgsAreConst) {
        vectorExpr->IRValue = ConstantVector::get(constantArgs);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitMatrixExpr(const LgsMatrixExpr* matrixExpr) {
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
                const std::vector<Value*> indices = {cg.i32Zero(), cg.i32(index++)};
                const auto gep = cg.builder.CreateInBoundsGEP(matTypeIR, matrixExpr->IRValue, indices);
                cg.store(element->IRValue, gep);
            }
        }
    }
}

void LgsCodeGen::visitHashMap(LgsHashMap* hashMap) {
    const auto map = hashMap->type->asMap();
    hashMap->IRValue = map->getIRZeroValue(cg, hashMap->pointee);
    for (const auto [key, value] : hashMap->elements) {
        visitExpr(key);
        visitExpr(value);
        map->addIRElement(cg, hashMap, key, value);
    }
}

void LgsCodeGen::visitEnvVar(LgsEnvVar* envVar) const {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {cg.getString(envVar->name), cg.emptyStr()};
    envVar->IRValue = cg.callLgsFunc(LgsSys::name, "getEnv", cg.ptrTy(), params, IRArgs);
}

void LgsCodeGen::visitVariable(LgsVariable* variable) {
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
        assert(variable->ref.object->singleton);
        variable->IRValue = getIRValue(variable->ref.object->singleton);
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

void LgsCodeGen::visitSelection(LgsSelection* selection, const bool assign) {
    const auto firstExpr = selection->exprs.front();
    if (!firstExpr->isImportName) {
        visitExpr(firstExpr);
        assert(!firstExpr->IRValue || &firstExpr->IRValue->getContext() == &cg.IRModule->getContext());
    }

    for (size_t i = firstExpr->isImportName; i < selection->exprs.size() - 1; ++i) {
        const auto parent = selection->exprs[i];
        const auto child = selection->exprs[i + 1];
        if (const auto var = child->asVariable()) {
            visitFieldSelection(var, parent, assign);
        } else if (const auto nullableExpr = child->asNullableExpr()) {
            visitNullableSelection(nullableExpr, parent);
        } else if (const auto methodCall = child->asFuncCall()) {
            if (methodCall->isMock) continue;
            visitFuncCall(methodCall);
        } else if (const auto iterIndex = child->asIterIndex()) {
            const auto baseExpr = iterIndex->getBaseExpr()->asVariable();
            const auto field = parent->type->getField(baseExpr->name);
            iterIndex->pointee = field->getGEP(cg, parent->IRValue);
            visitIterIndex(iterIndex, false);
        } else {
            assert(0);
        }
    }
    selection->IRValue = selection->exprs.back()->IRValue;
}

void LgsCodeGen::visitFieldSelection(LgsVariable* var, LgsExpr* parent, const bool assign) const {
    assert(parent->IRValue && &parent->IRValue->getContext() == &cg.IRModule->getContext());
    const auto field = var->ref.field;
    // Function pointer
    if (var->ref.symbolType == FUNC) {
        var->IRValue = var->ref.func->getIRFunc(cg);
        return;
    }

    // Enum field
    if (field->isEnumField) {
        var->IRValue = cg.usize(field->position);
        return;
    }

    // Enum type
    if (field->type->asEnum()) {
        if (assign) {
            var->IRValue = field->getGEP(cg, parent->IRValue);
        } else {
            var->IRValue = cg.load(cg.sizeTy(), field->getGEP(cg, parent->IRValue));
        }
        return;
    }

    // Singleton
    if (parent->asTypeExpr() && parent->type->asObject()->singleton) {
        parent->IRValue = cg.createGlobal(parent->type->getName(), parent->type->getIRType(cg), nullptr);
    }

    // Virtual fields
    if (field->isVirtual) {
        const auto id = cg.usize(hashString(field->name));
        var->IRValue = cg.getFromVTable(parent->IRValue, id);
        return;
    }

    // Vector
    if (field->type->asVec()) {
        createVecField(field, parent->IRValue);
    }
    var->IRValue = field->getGEP(cg, parent->IRValue);
    if (!assign && field->type->asObject()) {
        var->IRValue = cg.load(cg.ptrTy(), var->IRValue);
    }
}

void LgsCodeGen::visitNullableSelection(LgsExpr* child, LgsExpr* parent) const {
    assert(parent->type->asNullable());
    const auto field = child->asNullableExpr()->baseExpr->asVariable()->ref.field;
    const auto isNullBlock = cg.createBlock(BLOCK_TRUE);
    const auto isNotNullBlock = cg.createBlock(BLOCK_IF_FALSE);
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

void LgsCodeGen::visitMetaSelection(LgsMetaSelection* metaSelection) {
    visitExpr(metaSelection->baseExpr);
    if (const auto methodCall = metaSelection->child->asFuncCall()) {
        for (const auto& arg : methodCall->args) {
            if (arg.isSelf) continue;
            visitExpr(arg.expr);
        }
        metaSelection->IRValue = methodCall->func->call(cg, methodCall->args);
    }
}

void LgsCodeGen::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        if (arg.isSelf) continue;
        visitExpr(arg.expr);
    }

    // Function pointer
    if (funcCall->ref.symbolType != UNKNOWN) {
        LgsType* type = nullptr;
        LgsValue* value = nullptr;
        if (funcCall->ref.symbolType == PARAM) {
            type = funcCall->ref.param->type;
            value = funcCall->ref.param;
        } else if (funcCall->ref.symbolType == VAR_DEC) {
            type = funcCall->ref.varDec->type;
            value = funcCall->ref.varDec;
        }
        funcCall->func = new LgsFunc(type->asFuncType());
        funcCall->func->IRValue = getIRValue(value);
    }
    assert(funcCall->func || funcCall->coroutine);

    const auto func = funcCall->func ? funcCall->func : funcCall->coroutine;
    const auto ft = func->funcType;

    // Visit defaults
    if (ft->hasDefaults) {
        const auto diff = ft->params.size() - funcCall->args.size() - 1;
        for (size_t i = diff; i < ft->params.size(); ++i) {
            visitExpr(ft->params[i].expr);
        }
    }

    // Virtual call
    if (ft->isVirtual) {
        const auto name = func->funcType->getName();
        const auto id = cg.usize(hashString(name));
        func->IRValue = cg.getFromVTable(funcCall->args.front().expr->IRValue, id);
    }

    if (func->funcType->isBuiltin) {
        if (func->funcType->name == MAP_FUNC) {
            createMapFunc(func);
        } else if (func->funcType->name == FILTER_FUNC) {
            createFilterFunc(func);
        } else if (func->funcType->name == FOREACH_FUNC) {
            createForeachFunc(func);
        }
    }
    assert(func->funcType->genericTypes.empty());
    if (funcCall->coroutine || funcCall->isDeferred) return;
    funcCall->IRValue = func->call(cg, funcCall->args);
}

void LgsCodeGen::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto exprIRVal = getIRValue(prefixExpr->expr);
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

void LgsCodeGen::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
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

void LgsCodeGen::visitIntConst(LgsIntConst* intConst) const {
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
    } else if (intConst->type->asFloat()) { // IntConst to float is allowed
        intConst->IRValue = cg.floatv(intConst->value);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitStrConst(LgsStrConst* strConst) {
    if (strConst->parts.empty()) {
        strConst->IRValue = cg.getString(strConst->value);
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

void LgsCodeGen::visitCharConst(LgsCharConst* charConst) const {
    charConst->IRValue = cg.i8(charConst->value);
}

void LgsCodeGen::visitInstance(LgsInstance* instance) {
    const auto obj = instance->obj;
    const auto sizeIR = cg.usize(obj->sizeBytes());
    instance->IRValue = cg.heapAlloc(sizeIR);

    // Args
    std::unordered_set<std::string> visited;
    for (const auto& [argName, arg] : instance->args) {
        visited.insert(argName);
        const auto field = instance->obj->getField(argName);
        arg.expr->pointee = field->getGEP(cg, instance->IRValue);
        visitExpr(arg.expr);
        cg.store(arg.expr->IRValue, arg.expr->pointee);
    }

    // Zero values
    for (const auto field : instance->obj->fields) {
        if (visited.contains(field->name) || field->type->asEnum()) continue;
        const auto pointee = field->getGEP(cg, instance->IRValue);
        if (field->expr) {
            cg.store(field->expr->IRValue, pointee);
        } else {
            const auto zeroValue = field->type->getIRZeroValue(cg, pointee);
            cg.store(zeroValue, pointee);
        }
    }
    addVirtuals(instance->obj, instance->IRValue);
}

void LgsCodeGen::visitIterIndex(LgsIterIndex* iterIndex, const bool assign) {
    iterIndex->baseExpr->pointee = iterIndex->pointee;
    iterIndex->pointee = nullptr;
    visitExpr(iterIndex->baseExpr);
    visitExpr(iterIndex->index.from);
    if(iterIndex->index.to) {
        visitExpr(iterIndex->index.to);
        iterIndex->setIRRangePtr(cg, assign);
    } else {
        iterIndex->setIRElementPtr(cg, assign);
    }
}

void LgsCodeGen::visitJson(LgsJson* json) {
    assert(0);
}

void LgsCodeGen::createPrologue(LgsFunc* func) const {
    if (appConfigs.debugMode) func->setDebugValue(cg);
    cg.currentFunc = func->getIRFunc(cg);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    cg.builder.SetInsertPoint(entryBlock);
    if (func->funcType->name == LGS_MAIN_FUNC) {
        cg.callRuntimeFunc("init", cg.voidTy());
    }
    cg.callStackPush();
}

void LgsCodeGen::createEpilogue(const LgsFunc* func) const {
    if (func->funcType->name == LGS_MAIN_FUNC) {
        cg.callPopStack();
        cg.callRuntimeFunc("close", cg.voidTy());
        cg.builder.CreateRet(cg.i32(EXIT_SUCCESS));
    } else if (func->funcType->rt->isVoid() && !cg.lastInstTerminator()) {
        cg.callPopStack();
        cg.builder.CreateRetVoid();
    }
}

void LgsCodeGen::initMainArgs(const LgsMainFunc* mainFunc) const {
    const auto ft = mainFunc->funcType;
    if (ft->params.empty()) return;
    const auto argsArray = ft->params.front().expr->asArrayExpr();
    const auto sArray = argsArray->type->asSArray();
    sArray->size->IRValue = cg.currentFunc->getArg(0);
    argsArray->IRValue = cg.currentFunc->getArg(1);
    mainFunc->funcType->params[0].IRValue = argsArray->IRValue;
}

StructType* LgsCodeGen::getThunkCtxType(const LgsFuncCall* fc) const {
    std::vector<Value*> args;
    std::vector<Type*> types;
    for (const auto& arg : fc->args) {
        types.push_back(arg.expr->type->getIRType(cg));
    }
    return cg.getStructType(types, fc->name + "ThunkType");
}

Value* LgsCodeGen::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const {
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (size_t i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i].expr->IRValue;
        cg.storeStructField(ctxTy, ctx, i, v);
    }
    return ctx;
}

Function* LgsCodeGen::getThunkFunc(LgsFuncCall* fc, Type* ctxTy) const {
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

void LgsCodeGen::createVecField(LgsField* field, Value* parent) const {
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

bool LgsCodeGen::checkMock(LgsExpr* expr) const {
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

Value* LgsCodeGen::getIRValue(LgsValue* value) {
    if (value->IRValue) return value->IRValue;
    if (const auto expr = dynamic_cast<LgsExpr*>(value)) {
        visitExpr(expr);
    } else if (const auto stmt = dynamic_cast<LgsStmt*>(value)) {
        visitStmt(stmt);
    } else {
        assert(0);
    }
    assert(value->IRValue);
    return value->IRValue;
}

void LgsCodeGen::addVirtuals(LgsObject* obj, Value* ptr) const {
    for (const auto& field : obj->fields) {
        if (!field->isVirtual) continue;
        const auto virtualID = cg.usize(hashString(field->name));
        const auto objIR = obj->getIRType(cg);
        const auto fieldGEP = cg.builder.CreateStructGEP(objIR, ptr, field->position);
        cg.addToVTable(ptr, virtualID, fieldGEP);
    }

    for (const auto& [_, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        auto methodName = method->funcType->name;
        for (const auto implement : obj->implements) {
            if (!implement->methods.contains(methodName)) continue;
            const auto name = implement->methods[methodName]->funcType->getName();
            const auto virtualID = cg.usize(hashString(name));
            const auto IRFunc = method->getIRFunc(cg);
            cg.addToVTable(ptr, virtualID, IRFunc);
            break;
        }
    }

    // TODO make virtual only if the method was overridden
    // Implemented interface methods
    // const auto obj = type->asObject();
    // if (!obj) return;
    // for (const auto implement : obj->implements) {
    //     for (const auto& [methodName, interfaceMethod] : implement->methods) {
    //         if (!interfaceMethod->stmtsBlock) continue;
    //         const auto objMethod = obj->methods.find(methodName);
    //         if (objMethod != obj->methods.end()) continue;
    //         const auto id = cg.hashConst(methodName);
    //         const auto IRFunc = interfaceMethod->getIRFunc(cg);
    //         cg.addToVTable(ptr, id, IRFunc);
    //     }
    // }
}

void LgsCodeGen::createMapFunc(LgsFunc* func) const {
    if (cg.IRModule->getFunction(func->funcType->getName())) return;
    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;

    // Init
    const auto IRFunc = func->getIRFunc(cg);
    cg.currentFunc = IRFunc;
    const auto& iterableParam = func->funcType->params[0];
    const auto& callbackParam = func->funcType->params[1];
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto condBlock = cg.createBlock(BLOCK_LOOP_COND);
    const auto bodyBlock = cg.createBlock(BLOCK_LOOP_BODY);
    const auto exitBlock = cg.createBlock(BLOCK_LOOP_EXIT);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto iterable = iterableParam.type->asIterable();
    LgsDArray dArray(iterable->baseType);
    LgsArrayExpr newArr(&dArray);
    newArr.IRValue = dArray.getIRZeroValue(cg, nullptr);

    const auto iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(cg.sizeZero(), cg.sizeTy());
    cg.store(loopStart, iPtr);
    cg.builder.CreateBr(condBlock);

    // Condition
    cg.startBlock(condBlock);
    LgsIntConst size(&LGS_SIZE, 0);
    size.IRValue = cg.load(cg.sizeTy(), iPtr);
    const auto tempExpr = iterableParam.type->getZeroValue();
    auto length = iterable->lenIR(cg, iterableParam.IRValue);
    length = cg.extendToSize(length);
    const auto condition = cg.builder.CreateICmpSLT(size.IRValue, length);
    cg.builder.CreateCondBr(condition, bodyBlock, exitBlock);

    // Body
    cg.startBlock(bodyBlock);
    auto element = iterable->getIRElement(cg, tempExpr, &size);
    if (element->getType()->isPointerTy()) {
        element = cg.load(iterable->baseType->getIRType(cg), element);
    }
    const auto ft = llvm::dyn_cast<FunctionType>(callbackParam.type->getIRType(cg));
    const auto v = cg.builder.CreateCall(ft, callbackParam.IRValue, {element});
    tempExpr->IRValue = v;
    iterable->addIRElement(cg, &newArr, &size, tempExpr);
    freeExpr(tempExpr);

    // Increment
    const auto inc = cg.builder.CreateAdd(size.IRValue, cg.usize(1));
    cg.store(inc, iPtr);
    cg.builder.CreateBr(condBlock);

    // End func
    cg.startBlock(exitBlock);
    cg.callPopStack();
    cg.builder.CreateRet(newArr.IRValue);

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    func->IRValue = IRFunc;
}

void LgsCodeGen::createFilterFunc(LgsFunc* func) const {
    // if (cg.IRModule->getFunction(func->funcType->getName())) return;
    // // Save state
    // cg.savedIP = cg.builder.saveIP();
    // const auto originalFunc = cg.currentFunc;
    //
    // const auto IRFunc = func->getIRFunc(cg);
    // // Init
    // cg.currentFunc = IRFunc;
    // const auto& iterableParam = func->funcType->params[0];
    // const auto& callbackParam = func->funcType->params[1];
    // const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    // const auto condBlock = cg.createBlock(BLOCK_LOOP_COND);
    // const auto bodyBlock = cg.createBlock(BLOCK_LOOP_BODY);
    // const auto trueBlock = cg.createBlock(BLOCK_IF_TRUE);
    // const auto falseBlock = cg.createBlock(BLOCK_IF_FALSE);
    // const auto exitBlock = cg.createBlock(BLOCK_LOOP_EXIT);
    // cg.builder.SetInsertPoint(entryBlock);
    // cg.callStackPush();
    //
    // const auto iterable = iterableParam.type->asIterable();
    // const auto newArr = iterableParam.type->getIRZeroValue(cg);
    //
    // const auto iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    // const auto loopStart = cg.builder.CreateSExt(cg.sizeZero(), cg.sizeTy());
    // cg.store(loopStart, iPtr);
    // cg.builder.CreateBr(condBlock);
    //
    // // Condition
    // cg.startBlock(condBlock);
    // const auto iValue = cg.load(cg.sizeTy(), iPtr);
    // auto length = iterable->lenIR(cg, iterableParam.IRValue);
    // length = cg.extendToSize(length);
    // const auto condition = cg.builder.CreateICmpSLT(iValue, length);
    // cg.builder.CreateCondBr(condition, bodyBlock, exitBlock);
    //
    // // Body
    // cg.startBlock(bodyBlock);
    // auto element = iterable->getIRElement(cg, iterableParam.IRValue, iValue);
    // if (element->getType()->isPointerTy()) {
    //     element = cg.load(iterable->baseType->getIRType(cg), element);
    // }
    // const auto ft = llvm::dyn_cast<FunctionType>(callbackParam.type->getIRType(cg));
    // const auto filterCond = cg.builder.CreateCall(ft, callbackParam.IRValue, {element});
    // cg.builder.CreateCondBr(filterCond, trueBlock, falseBlock);
    // cg.startBlock(trueBlock);
    // // iterable->addIRElement(cg, newArr, iValue, element);
    // cg.branchAndStartBlock(falseBlock);
    //
    // // Increment
    // const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    // cg.store(inc, iPtr);
    // cg.builder.CreateBr(condBlock);
    //
    // // End func
    // cg.startBlock(exitBlock);
    // cg.callPopStack();
    // cg.builder.CreateRet(newArr);
    //
    // // Restore state
    // cg.currentFunc = originalFunc;
    // cg.builder.restoreIP(cg.savedIP);
    // func->IRValue = IRFunc;
}

void LgsCodeGen::createForeachFunc(LgsFunc* func) const {
    // if (cg.IRModule->getFunction(func->funcType->getName())) return;
    // // Save state
    // cg.savedIP = cg.builder.saveIP();
    // const auto originalFunc = cg.currentFunc;
    // cg.currentFunc = func->getIRFunc(cg);
    // func->IRValue = cg.currentFunc;
    //
    // // Init
    // const auto& iterableParam = func->funcType->params[0];
    // const auto& callbackParam = func->funcType->params[1];
    // const auto iterable = iterableParam.type->asIterable();
    // const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    // const auto condBlock = cg.createBlock(BLOCK_LOOP_COND);
    // const auto bodyBlock = cg.createBlock(BLOCK_LOOP_BODY);
    // const auto exitBlock = cg.createBlock(BLOCK_LOOP_EXIT);
    // cg.builder.SetInsertPoint(entryBlock);
    // cg.callStackPush();
    //
    // const auto iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    // const auto loopStart = cg.builder.CreateSExt(cg.sizeZero(), cg.sizeTy());
    // cg.store(loopStart, iPtr);
    // cg.builder.CreateBr(condBlock);
    //
    // // Condition
    // cg.startBlock(condBlock);
    // const auto iValue = cg.load(cg.sizeTy(), iPtr);
    // auto length = iterable->lenIR(cg, iterableParam.IRValue);
    // length = cg.extendToSize(length);
    // const auto condition = cg.builder.CreateICmpSLT(iValue, length);
    // cg.builder.CreateCondBr(condition, bodyBlock, exitBlock);
    //
    // // Body
    // cg.startBlock(bodyBlock);
    // auto element = iterable->getIRElement(cg, iterableParam.IRValue, iValue);
    // if (element->getType()->isPointerTy()) {
    //     element = cg.load(iterable->baseType->getIRType(cg), element);
    // }
    // const auto ft = llvm::dyn_cast<FunctionType>(callbackParam.type->getIRType(cg));
    // cg.builder.CreateCall(ft, callbackParam.IRValue, {element});
    //
    // // Increment
    // const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    // cg.store(inc, iPtr);
    // cg.builder.CreateBr(condBlock);
    //
    // // End func
    // cg.startBlock(exitBlock);
    // cg.callPopStack();
    // cg.builder.CreateRetVoid();
    //
    // // Restore state
    // cg.currentFunc = originalFunc;
    // cg.builder.restoreIP(cg.savedIP);
}
