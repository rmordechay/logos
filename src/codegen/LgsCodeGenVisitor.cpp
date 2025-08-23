#include "codegen/LgsCodeGenVisitor.h"
#include "funcs/LgsCoroutine.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "exprs/unary/LgsCast.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterator.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/LgsVectorExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsDArray.h"
#include "types/LgsInterface.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"
#include "types/LgsTable.h"
#include <llvm/Target/TargetMachine.h>

void LgsCodeGenVisitor::generate(const LgsAppConfigs& appConfigs, const TargetMachine& targetMachine) {
    file.generator.setupModule(file.name, targetMachine.createDataLayout(), appConfigs.debugMode);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterface(interfaceFile->interface);
    }
}

void LgsCodeGenVisitor::visitMainFile(LgsMainFile* mainFile) {
    for (const auto object : mainFile->objects) {
        visitObject(object);
        for (const auto& [_, method] : object->methods) {
            visitFunc(method);
        }
    }
    for (const auto [_, func] : mainFile->funcs) {
        if (const auto mainFunc = dynamic_cast<LgsMainFunc*>(func)) {
            visitMainFunc(mainFunc);
        } else {
            visitFunc(func);
        }
    }
}

void LgsCodeGenVisitor::visitObjFile(const LgsObjectFile* objFile) {
    visitObject(objFile->obj);
    for (const auto& [_, method] : objFile->obj->methods) {
        visitFunc(method);
    }
}

void LgsCodeGenVisitor::visitInterfaceFile(const LgsInterfaceFile* interfaceFile) {
    for (const auto& [_, method] : interfaceFile->interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCodeGenVisitor::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    // codeGen->callRuntimeInit();
    if (!func->funcType->params.empty()) func->initMainArgs(generator);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    generator.builder.CreateRet(generator.i32(EXIT_SUCCESS));
    stack.exitScope();
}

void LgsCodeGenVisitor::visitFunc(LgsFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    if (!generator.lastInstTerminator()) generator.builder.CreateRetVoid();
    stack.exitScope();
}

void LgsCodeGenVisitor::visitObject(LgsObject* obj) const {
    if (obj->IRType) return;
    std::vector<Type*> elementTypes;
    elementTypes.reserve(obj->fields.size());
    for (int i = 0; i < obj->fields.size(); ++i) {
        const auto field = obj->fields[i];
        field->position = i;
        Type* fieldType;
        if (field->type->asObject() || field->type->asFuncType()) {
            fieldType = generator.ptrTy();
        } else {
            fieldType = field->type->getIRType(generator);
        }
        elementTypes.push_back(fieldType);
    }
    obj->IRType = StructType::getTypeByName(generator.context, obj->name);
    if (!obj->IRType) {
        obj->IRType = StructType::create(generator.context, elementTypes, obj->name);
    }
    for (const auto& field : obj->fields) {
        field->parentIRType = obj->IRType;
    }
}

void LgsCodeGenVisitor::visitInterface(LgsInterface* interface) const {
    if (interface->IRType) return;
    interface->IRType = StructType::getTypeByName(generator.context, interface->name);
    std::vector<Type*> elementTypes;
    for (int i = 0; i < interface->methods.size(); ++i) {
        elementTypes.emplace_back(generator.ptrTy());
    }
    if (!interface->IRType) {
        interface->IRType = StructType::create(generator.context, elementTypes, interface->name);
    }
}

void LgsCodeGenVisitor::visitGroup(LgsGroup* group) {
    assert(0);
}

void LgsCodeGenVisitor::visitTable(LgsTable* table) {
    assert(0);
}

void LgsCodeGenVisitor::visitField(LgsField* field) const {
    if (field->parentIRType->isVectorTy()) {
        const auto vec = generator.builder.CreateLoad(field->parentIRType, field->parentIRValue);
        const auto i = generator.isize(field->position);
        field->IRValue = generator.builder.CreateExtractElement(vec, i);
    } else {
        field->IRValue = generator.builder.CreateStructGEP(field->parentIRType, field->parentIRValue, field->position);
    }
}

void LgsCodeGenVisitor::visitParam(LgsParam* param) const {
    if (!param->isVariadic) return;
    if (param->vaList) {
        param->IRValue = param->vaList;
        return;
    }
    param->vaList = generator.builder.CreateAlloca(generator.builder.getPtrTy());
    const auto vaStart = Intrinsic::getDeclaration(generator.IRModule, Intrinsic::vastart, {generator.builder.getPtrTy()});
    generator.builder.CreateCall(vaStart, {param->vaList});
    param->IRValue = param->vaList;

}

void LgsCodeGenVisitor::visitLoop(LgsForLoop* loopStmt) {
    stack.enterScope(loopStmt);
    loopStmt->setBlocks(generator);
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = dynamic_cast<LgsInfiniteLoop*>(loopStmt)) {
        visitInfiniteLoop(infiniteLoop);
    } else if (const auto whileLoop = dynamic_cast<LgsWhileLoop*>(loopStmt)) {
        visitWhileLoop(whileLoop);
    } else {
        assert(0);
    }
    visitStmtsBlock(loopStmt->stmtsBlock);
    loopStmt->incAndJumpToCond(generator);
    startBlock(loopStmt->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGenVisitor::visitRangeLoop(LgsRangeLoop* loop) {
    loop->iPtr = generator.builder.CreateAlloca(generator.i32Ty());
    generator.builder.CreateStore(loopStart(loop), loop->iPtr);
    generator.builder.CreateBr(loop->IRCondBlock);

    // Condition
    startBlock(loop->IRCondBlock);
    const auto iValue = loop->loadIndex(generator);
    const auto condition = generator.builder.CreateICmpSLT(iValue, loopEnd(loop));
    visitLoopTerminals(loop, iValue);
    generator.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    startBlock(loop->IRBodyBlock);
    loop->loopVars.front()->setIRValue(iValue);
}

void LgsCodeGenVisitor::visitForeachLoop(LgsForeachLoop* loop) {
    loop->iPtr = generator.builder.CreateAlloca(generator.i32Ty());
    generator.builder.CreateStore(generator.i32Zero(), loop->iPtr);
    branchAndStartBlock(loop->IRCondBlock);
    const auto iterable = loop->iterExpr->type->asIterable();
    if (iterable->asMap()) { // With iterator
        LgsIterator iterator = loop->iterExpr->toIterator();
        iterator.initIterator(generator);
        generator.builder.CreateCondBr(iterator.hasNext(generator), loop->IRBodyBlock, loop->IRExitBlock);
        startBlock(loop->IRBodyBlock);
        loop->iterPtr = getIRValue(loop->iterExpr);
        loop->setMapIterVars(generator, iterator);
    } else { // Without iterator
        auto iValue = loop->loadIndex(generator);
        const auto loopEnd = iterable->IRLength(generator, loop->iterExpr);
        if (loopEnd->getType()->isIntegerTy(64)) {
            iValue = generator.builder.CreateSExt(iValue, generator.i64Ty());
        }
        const auto condition = generator.builder.CreateICmpSLT(iValue, loopEnd);
        generator.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
        startBlock(loop->IRBodyBlock);
        loop->iterPtr = getIRValue(loop->iterExpr);
        if (const auto str = iterable->asStr()) {
            loop->setStrIterVars(generator, str);
        } else if (const auto arr = iterable->asDArray()) {
            loop->setArrIterVars(generator, arr);
        } else {
            assert(0);
        }
    }
}

void LgsCodeGenVisitor::visitInfiniteLoop(LgsInfiniteLoop* loop) {
    if (!loop->loopVars.empty()) {
        loop->iPtr = generator.builder.CreateAlloca(generator.i32Ty());
        generator.builder.CreateStore(generator.i32Zero(), loop->iPtr);
    }
    branchAndStartBlock(loop->IRBodyBlock);
    if (!loop->loopVars.empty()) {
        const auto iValue = loop->loadIndex(generator);
        loop->loopVars.front()->setIRValue(iValue);
    }
}

void LgsCodeGenVisitor::visitWhileLoop(LgsWhileLoop* loop) {
    generator.builder.CreateBr(loop->IRCondBlock);
    // Condition
    startBlock(loop->IRCondBlock);
    const auto condition = getIRValue(loop->condExpr);
    generator.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    startBlock(loop->IRBodyBlock);
}

void LgsCodeGenVisitor::visitLoopTerminals(const LgsRangeLoop* loop, Value* iValue) {
    if (loop->isFirst) {
        loop->isFirst->setIRValue(generator.builder.CreateICmpEQ(iValue, loopStart(loop)));
    }
    if (loop->isLast) {
        const auto decremented = generator.builder.CreateSub(loopEnd(loop), generator.i32(1));
        loop->isLast->setIRValue(generator.builder.CreateICmpEQ(iValue, decremented));
    }
}

void LgsCodeGenVisitor::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) return visitIfStmt(ifStmt);
    if (const auto pattern = stmt->asPattern()) return visitPatternMatching(pattern);
    if (const auto varDec = stmt->asVarDec()) return visitVarDec(varDec);
    if (const auto loopStmt = stmt->asLoop()) return visitLoop(loopStmt);
    if (const auto coroutine = stmt->asCoroutine()) return visitCoroutine(coroutine);
    if (const auto deferStmt = stmt->asDefer()) return visitDeferStmt(deferStmt);
    if (const auto assignment = stmt->asAssignment()) return visitAssignment(assignment);
    if (const auto funcCall = stmt->asFuncCall()) return visitFuncCall(funcCall);
    if (const auto postfixExpr = stmt->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
    if (const auto selection = stmt->asSelection()) return visitSelection(selection);
    if (const auto returnStmt = stmt->asReturn()) return visitReturnStmt(returnStmt);
    if (const auto breakStmt = stmt->asBreak()) return visitBreakStmt(breakStmt);
    if (stmt->asContinue()) return visitContinueStmt();
    assert(0);
}

void LgsCodeGenVisitor::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    for (const auto stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
}

void LgsCodeGenVisitor::visitVarDec(LgsVarDec* varDec) {
    const auto IRType = varDec->type->getIRType(generator);
    const auto exprIRValue = getIRValue(varDec->expr);
    if (varDec->shouldAllocate(IRType)) {
        varDec->IRValue = generator.builder.CreateAlloca(IRType, nullptr, varDec->name);
        generator.builder.CreateStore(exprIRValue, getIRValue(varDec));
    } else {
        varDec->IRValue = exprIRValue;
    }
}

void LgsCodeGenVisitor::visitAssignment(const LgsAssignment* assignment) {
    Value* results = nullptr;
    switch (assignment->assignmentType) {
    case ASSIGN:
        assignment->createIRAssignment(generator);
        return;
    case ASSIGN_ADD:
        results = assignment->lValue->addIR(generator, assignment->rValue);
        break;
    case ASSIGN_SUB:
        results = assignment->lValue->subIR(generator, assignment->rValue);
        break;
    case ASSIGN_MUL:
        results = assignment->lValue->mulIR(generator, assignment->rValue);
        break;
    case ASSIGN_DIV:
        results = assignment->lValue->divIR(generator, assignment->rValue);
        break;
    case ASSIGN_MOD:
        results = assignment->lValue->modIR(generator, assignment->rValue);
        break;
    case ASSIGN_AND:
        results = assignment->lValue->bitAndIR(generator, assignment->rValue);
        break;
    case ASSIGN_OR:
        results = assignment->lValue->bitOrIR(generator, assignment->rValue);
        break;
    case ASSIGN_XOR:
        results = assignment->lValue->bitXorIR(generator, assignment->rValue);
        break;
    case ASSIGN_LSHIFT:
        results = assignment->lValue->lshiftIR(generator, assignment->rValue);
        break;
    case ASSIGN_RSHIFT:
        results = assignment->lValue->rshiftIR(generator, assignment->rValue);
        break;
    }
    assert(results);
    generator.builder.CreateStore(results, getIRValue(assignment->lValue));
}

void LgsCodeGenVisitor::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->elseIfs.empty()) {
        if (!ifStmt->elseBlock) {
            visitSimpleIf(ifStmt);
        } else {
            visitIfWithElse(ifStmt);
        }
    } else {
        visitElseIf(ifStmt);
    }
}

void LgsCodeGenVisitor::visitSimpleIf(LgsIfStmt* ifStmt) {
    const auto IRBlockIfTrue = generator.createBlock(BLOCK_NAME_IF_TRUE);
    ifStmt->IRExitBlock = generator.createBlock(BLOCK_NAME_IF_FALSE);

    stack.enterScope(ifStmt);
    generator.builder.CreateCondBr(getIRValue(ifStmt->ifCond), IRBlockIfTrue, ifStmt->IRExitBlock);
    startBlock(IRBlockIfTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    branchAndStartBlock(ifStmt->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGenVisitor::visitIfWithElse(LgsIfStmt* ifStmt) {
    const auto IRBlockTrue = generator.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockElse = generator.createBlock(BLOCK_NAME_ELSE);
    ifStmt->IRExitBlock = generator.createBlock(BLOCK_NAME_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    generator.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElse);
    startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    generator.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    // else block
    stack.enterScope(ifStmt);
    startBlock(IRBlockElse);
    visitStmtsBlock(ifStmt->elseBlock);
    branchAndStartBlock(ifStmt->IRExitBlock);
    stack.exitScope();
}


void LgsCodeGenVisitor::visitElseIf(LgsIfStmt* ifStmt) {
    auto IRBlockTrue = generator.createBlock(BLOCK_NAME_IF_TRUE);
    auto IRBlockElseIfCheck = generator.createBlock(BLOCK_NAME_ELSE_IF_CHECK);
    const auto IRBlockElse = generator.createBlock(BLOCK_NAME_ELSE);
    ifStmt->IRExitBlock = generator.createBlock(BLOCK_NAME_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    generator.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    generator.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    for (int i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        stack.enterScope(ifStmt);
        startBlock(IRBlockElseIfCheck);
        const auto elseIfCondIR = getIRValue(expr);
        IRBlockTrue = generator.createBlock(BLOCK_NAME_ELSE_IF);
        if (i == ifStmt->elseIfs.size() - 1) {
            if (ifStmt->elseBlock) {
                generator.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElse);
            } else {
                generator.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, ifStmt->IRExitBlock);
            }
        } else {
            IRBlockElseIfCheck = generator.createBlock(BLOCK_NAME_ELSE_IF_CHECK);
            generator.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElseIfCheck);
        }
        startBlock(IRBlockTrue);
        visitStmtsBlock(stmtBlock);
        generator.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }

    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        startBlock(IRBlockElse);
        visitStmtsBlock(ifStmt->elseBlock);
        generator.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }
    startBlock(ifStmt->IRExitBlock);
}

void LgsCodeGenVisitor::visitPatternMatching(LgsIfStmt* pm) {
    const auto defaultBlock = generator.createBlock(BLOCK_NAME_DEFAULT_CASE);
    const auto exitBlock = generator.createBlock(BLOCK_NAME_EXIT_PATTERN);

    const auto exprIRValue = pm->ifCond->hash(generator);
    SwitchInst* switchInst;
    if (pm->elseBlock) {
        const auto numOfCases = pm->elseIfs.size() + !!pm->elseBlock;
        switchInst = generator.builder.CreateSwitch(exprIRValue, defaultBlock, numOfCases);
    } else {
        switchInst = generator.builder.CreateSwitch(exprIRValue, exitBlock, pm->elseIfs.size());
    }

    std::vector<BasicBlock*> blocks;
    for (size_t i = 0; i < pm->elseIfs.size(); ++i) {
        const auto [expr, stmtsBlock] = pm->elseIfs[i];
        stack.enterScope(pm);
        const auto patterIRValue = expr->hash(generator);
        const auto IRFunc = stack.currentFunc()->getIRFunc(generator);
        const auto patternBlock = generator.createBlock(BLOCK_NAME_CASE_PREFIX + std::to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        generator.builder.SetInsertPoint(patternBlock);
        generator.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    if (pm->elseBlock) {
        stack.enterScope(pm);
        startBlock(defaultBlock);
        generator.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    startBlock(exitBlock);

}

void LgsCodeGenVisitor::visitCoroutine(const LgsCoroutine* coroutine) {
    const LgsFuncCall* fc = nullptr;
    if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
        fc = coroutine->selection->lastExpr()->asFuncCall();
    } else {
        assert(0);
    }
    const auto ctxTy = generator.getThunkCtxType(fc);
    const auto ctx = generator.getThunkCtx(fc, ctxTy);
    const auto func = generator.getThunkFunc(fc, ctxTy);
    generator.addCoro(func, ctx);
}

void LgsCodeGenVisitor::visitReturnStmt(LgsReturn* returnStmt) {
    returnStmt->IRValue = returnStmt->expr ? getIRValue(returnStmt->expr) : nullptr;
    const auto currentFunc = stack.currentFunc();
    const auto currentStmtsBlock = stack.currentFunc();
    if (currentStmtsBlock->needsCleanup()) {
        returnStmt->parentBlock = generator.builder.GetInsertBlock();
        const auto cleanupBlock = currentStmtsBlock->getCleanupBlock(generator);
        generator.builder.CreateBr(cleanupBlock);
    } else {
        if (currentFunc->funcType->rt->isVoid()) {
            generator.builder.CreateRetVoid();
        } else {
            generator.builder.CreateRet(returnStmt->IRValue);
        }
    }
}

void LgsCodeGenVisitor::visitContinueStmt() {
    const auto currentLoop = stack.currentLoop();
    currentLoop->incAndJumpToCond(generator);
}

void LgsCodeGenVisitor::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        generator.builder.CreateBr(stack.outermostIfStmt()->IRExitBlock);
    } else {
        const auto loop = stack.currentLoop();
        generator.builder.CreateBr(loop->IRExitBlock);
    }
}

void LgsCodeGenVisitor::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    const LgsFuncCall* fc = nullptr;
    if (deferStmt->funcCall) {
        visitFuncCall(deferStmt->funcCall);
        fc = deferStmt->funcCall;
    } else if (deferStmt->selection) {
        visitSelection(deferStmt->selection);
        fc = deferStmt->selection->lastExpr()->asFuncCall();
    } else {
        assert(0);
    }
    const auto ctxTy = generator.getThunkCtxType(fc);
    const auto ctx = generator.getThunkCtx(fc, ctxTy);
    const auto func = generator.getThunkFunc(fc, ctxTy);
    generator.addDeferFunc(func, ctx);
}

void LgsCodeGenVisitor::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->sizeExpr);
    }
    if (const auto castExpr = dynamic_cast<LgsCast*>(expr)) {
        visitCast(castExpr);
    } else if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
    assert(expr->IRValue);
}

void LgsCodeGenVisitor::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto func = unaryExpr->asFunc()) return visitLambda(func);
    if (const auto instance = unaryExpr->asInstance()) return visitInstance(instance);
    if (const auto funcCall = unaryExpr->asFuncCall()) return visitFuncCall(funcCall);
    if (const auto strConst = unaryExpr->asStrConst()) return visitStrConst(strConst);
    if (const auto selection = unaryExpr->asSelection()) return visitSelection(selection);
    if (const auto arrayExpr = unaryExpr->asArrayExpr()) return visitArrayExpr(arrayExpr);
    if (const auto hashMap = unaryExpr->asHashMap()) return visitHashMap(hashMap);
    if (const auto iterIndex = unaryExpr->asIterIndex()) return visitIterIndex(iterIndex);
    if (const auto variable = unaryExpr->asVariable()) return visitVariable(variable);
    if (const auto postfixExpr = unaryExpr->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
    if (const auto prefixExpr = unaryExpr->asPrefixExpr()) return visitPrefixExpr(prefixExpr);
    if (const auto vecExpr = unaryExpr->asVectorExpr()) return visitVectorExpr(vecExpr);
    if (const auto intConst = unaryExpr->asIntConst()) return visitIntConst(intConst);
    assert(0);
}

void LgsCodeGenVisitor::visitBinaryExpr(LgsBinaryExpr* binaryExpr) const {
    switch (binaryExpr->op) {
    case ADD:
        binaryExpr->IRValue = binaryExpr->left->addIR(generator, binaryExpr->right);
        break;
    case SUB:
        binaryExpr->IRValue = binaryExpr->left->subIR(generator, binaryExpr->right);
        break;
    case MUL:
        binaryExpr->IRValue = binaryExpr->left->mulIR(generator, binaryExpr->right);
        break;
    case DIV:
        binaryExpr->IRValue = binaryExpr->left->divIR(generator, binaryExpr->right);
        break;
    case IN:
        binaryExpr->IRValue = binaryExpr->left->inIR(generator, binaryExpr->right);
        break;
    case MOD:
        binaryExpr->IRValue = binaryExpr->left->modIR(generator, binaryExpr->right);
        break;
    case EQ:
        binaryExpr->IRValue = binaryExpr->left->eqIR(generator, binaryExpr->right);
        break;
    case NE:
        binaryExpr->IRValue = binaryExpr->left->neIR(generator, binaryExpr->right);
        break;
    case AND:
        binaryExpr->IRValue = binaryExpr->left->andIR(generator, binaryExpr->right);
        break;
    case OR:
        binaryExpr->IRValue = binaryExpr->left->orIR(generator, binaryExpr->right);
        break;
    case LT:
        binaryExpr->IRValue = binaryExpr->left->ltIR(generator, binaryExpr->right);
        break;
    case GT:
        binaryExpr->IRValue = binaryExpr->left->gtIR(generator, binaryExpr->right);
        break;
    case GE:
        binaryExpr->IRValue = binaryExpr->left->geIR(generator, binaryExpr->right);
        break;
    case LE:
        binaryExpr->IRValue = binaryExpr->left->leIR(generator, binaryExpr->right);
        break;
    case BIT_AND:
        binaryExpr->IRValue = binaryExpr->left->bitAndIR(generator, binaryExpr->right);
        break;
    case BIT_OR:
        binaryExpr->IRValue = binaryExpr->left->bitOrIR(generator, binaryExpr->right);
        break;
    case BIT_XOR:
        binaryExpr->IRValue = binaryExpr->left->bitXorIR(generator, binaryExpr->right);
        break;
    case LSHIFT:
        binaryExpr->IRValue = binaryExpr->left->rshiftIR(generator, binaryExpr->right);
        break;
    case RSHIFT:
        binaryExpr->IRValue = binaryExpr->left->lshiftIR(generator, binaryExpr->right);
        break;
    case NOOP:
        assert(0);
    }

}

void LgsCodeGenVisitor::visitCast(LgsCast* lgsCast) {
    lgsCast->IRValue = getIRValue(lgsCast->toValue);
}

void LgsCodeGenVisitor::visitLambda(LgsFunc* func) {
    generator.savedIP = generator.builder.saveIP();
    visitFunc(func);
    generator.builder.restoreIP(generator.savedIP);
    func->IRValue = func->getIRFunc(generator);
}

void LgsCodeGenVisitor::visitIntConst(LgsIntConst* intConst) {
    if (intConst->type->asBool()) {
        intConst->IRValue = generator.i1(intConst->value);
    } else if (intConst->type->asChar()) {
        intConst->IRValue = generator.i8(intConst->value);
    } else if (intConst->type->asShort()) {
        intConst->IRValue = generator.i16(intConst->value);
    } else if (intConst->type->asInt()) {
        intConst->IRValue = generator.i32(intConst->value);
    } else if (intConst->type->asLong()) {
        intConst->IRValue = generator.i64(intConst->value);
    }
}

void LgsCodeGenVisitor::visitArrayExpr(LgsArrayExpr* array) const {
    if (array->type->asSArray()) {
        array->IRValue = array->createConstArray(generator);
    } else if (array->type->asDArray()) {
        array->IRValue = array->createDynamicArray(generator);
    }
    else assert(0);
}

void LgsCodeGenVisitor::visitHashMap(LgsHashMap* hashMap) {
    const auto mapType = hashMap->type->asMap();
    const auto valueType = mapType->typePair->value;
    const auto elementSize = generator.isize(valueType->getSizeBytes());
    hashMap->IRValue = generator.builder.CreateAlloca(mapType->getMapStruct(generator));
    mapType->initFunc->callIR(generator, {getIRValue(hashMap), elementSize});
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
        mapType->addFunc->call(generator, {hashMap, element->key, element->value});
    }
}

void LgsCodeGenVisitor::visitVectorExpr(LgsVectorExpr* vec) {
    const auto ty = vec->type->getIRType(generator);
    vec->IRValue = generator.builder.CreateAlloca(ty);
    generator.builder.CreateStore(ConstantAggregateZero::get(ty), getIRValue(vec));
}

void LgsCodeGenVisitor::visitVariable(LgsVariable* variable) {
    switch (variable->ref.symbolType) {
    case VAR_DEC:
        variable->IRValue = getIRValue(variable->ref.varDec);
        break;
    case PARAM:
        variable->IRValue = getIRValue(variable->ref.param);
        break;
    case FUNC:
        variable->IRValue = variable->ref.func->getIRFunc(generator);
        break;
    case OBJECT:
        assert(variable->ref.object->singleton);
        variable->IRValue = getIRValue(variable->ref.object->singleton);
        break;
    case ENUM:
    case ENUM_FIELD:
        variable->IRValue = generator.getIRStr(variable->name);
        break;
    case TABLE:
        variable->IRValue = variable->ref.table->instance->IRValue;
        break;
    case INTERFACE:
    case GROUP:
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCodeGenVisitor::visitSelection(LgsSelection* selection) {
    auto startIndex = 0;
    const auto parentAsVar = selection->exprs.front()->asVariable();
    if (parentAsVar && parentAsVar->ref.symbolType == OBJECT) {
        selection->exprs.front() = parentAsVar->ref.object->singleton;
        startIndex = 1;
    }
    for (int i = startIndex; i < selection->exprs.size() - 1; ++i) {
        const auto parentExpr = selection->exprs[i];
        const auto childExpr = selection->exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            const auto field = parentExpr->type->getField(var->name);
            field->parentIRType = parentExpr->type->getIRType(generator);
            field->parentIRValue = getIRValue(parentExpr);
            if (i > 0) {
                field->parentIRValue = generator.builder.CreateLoad(generator.ptrTy(), field->parentIRValue);
            }
            const auto fieldIR = getIRValue(field);
            childExpr->setIRValue(fieldIR);
        } else {
        }
    }
    selection->IRValue = getIRValue(selection->lastExpr());
}

void LgsCodeGenVisitor::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    if (funcCall->ref.symbolType == PARAM) {
        LgsFunc f(funcCall->ref.param->type->asFuncType());
        f.setIRValue(getIRValue(funcCall->ref.param));
        funcCall->IRValue = f.call(generator, funcCall->args);
        return;
    }
    if (funcCall->func->funcType->isVirtual) {
        funcCall->resolveVirtualFunc(generator);
    }
    funcCall->IRValue = funcCall->func->call(generator, funcCall->args);
}

void LgsCodeGenVisitor::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto exprIRVal = getIRValue(prefixExpr->expr);
    switch (prefixExpr->op) {
    case NOT_PREFIX: {
        prefixExpr->IRValue = generator.builder.CreateNot(exprIRVal);
        break;
    }
    case MINUS_PREFIX: {
        const auto zero = ConstantInt::get(prefixExpr->type->getIRType(generator), 0);
        prefixExpr->IRValue = generator.builder.CreateSub(zero, exprIRVal);
        break;
    }
    case SQRT_PREFIX: {
        prefixExpr->IRValue = generator.callSqrt(exprIRVal);
        break;
    }
    }
}

void LgsCodeGenVisitor::visitPostfixExpr(LgsPostfixExpr* postfixExpr) const {
    postfixExpr->IRValue = postfixExpr->IncOrDecValue(generator);
}

void LgsCodeGenVisitor::visitStrConst(LgsStrConst* strConst) const {
    strConst->IRValue = generator.getIRStr(strConst->value);
}

void LgsCodeGenVisitor::visitInstance(LgsInstance* instance) const {
    if (instance->table) return instance->createIRTable(generator);
    const auto objIRType = instance->obj->getIRType(generator);
    if(instance->obj->singleton) {
        instance->IRValue = generator.createGlobal(objIRType, ConstantAggregateZero::get(objIRType), instance->obj->name);
    } else {
        instance->IRValue = generator.builder.CreateAlloca(objIRType);
    }
    instance->initFields(generator);
    if (!instance->obj->interfaces.empty()) {
        instance->setVirtuals(generator);
    }
}

void LgsCodeGenVisitor::visitIterIndex(LgsIterIndex* iterIndex) {
    visitExpr(iterIndex->baseExpr);
    visitExpr(iterIndex->index->from);
    visitExpr(iterIndex->index->to);
    const auto baseExprType = iterIndex->baseExpr->type;
    if (baseExprType->asSArray()) {
        iterIndex->IRValue = iterIndex->loadFromSArray(generator);
    } else if (iterIndex->baseExpr->type->isVector()) {
        iterIndex->IRValue = iterIndex->loadFromVec(generator);
    } else if (const auto arr = baseExprType->asDArray()) {
        iterIndex->IRValue = iterIndex->loadFromDArray(generator, arr);
    } else if (const auto map = baseExprType->asMap()) {
        iterIndex->IRValue = iterIndex->loadFromMap(generator, map);
    } else if (const auto str = baseExprType->asStr()) {
        iterIndex->IRValue = iterIndex->loadFromStr(generator, str);
    } else {
        assert(0);
    }
}

Value* LgsCodeGenVisitor::getIRValue(LgsValue* value) {
    if (value->IRValue) return value->IRValue;
    if (const auto expr = dynamic_cast<LgsExpr*>(value)) {
        visitExpr(expr);
    } else if (const auto param = dynamic_cast<LgsParam*>(value)) {
        visitParam(param);
    } else {
        assert(0);
    }
    assert(value->IRValue);
    return value->IRValue;
}

Value* LgsCodeGenVisitor::loopEnd(const LgsRangeLoop* loop) {
    visitExpr(loop->endRange);
    return getIRValue(loop->endRange);
}

Value* LgsCodeGenVisitor::loopStart(const LgsRangeLoop* loop) {
    if (!loop->startRange) return generator.i32Zero();
    visitExpr(loop->startRange);
    return getIRValue(loop->startRange);
}

void LgsCodeGenVisitor::generateIf(Value* cond, const std::function<void()>& blockStmtCb) {
    const auto IRBlockIfTrue = generator.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = generator.createBlock(BLOCK_NAME_IF_FALSE);
    generator.builder.CreateCondBr(cond, IRBlockIfTrue, IRBlockIfFalse);
    startBlock(IRBlockIfTrue);
    blockStmtCb();
    branchAndStartBlock(IRBlockIfFalse);
}

void LgsCodeGenVisitor::startBlock(BasicBlock* block) {
    block->insertInto(stack.currentFunc()->getIRFunc(generator));
    generator.builder.SetInsertPoint(block);
}

void LgsCodeGenVisitor::branchAndStartBlock(BasicBlock* block) {
    generator.branchIfNeeded(block);
    startBlock(block);
}

void LgsCodeGenVisitor::createPrologue(LgsFunc* func) const {
    const auto IRFunc = func->getIRFunc(generator);
    IRFunc->setLinkage(func->funcType->isPublic ? GlobalValue::ExternalLinkage : GlobalValue::PrivateLinkage);
    const auto entryBlock = generator.createBlock(BLOCK_NAME_ENTRY, IRFunc);
    generator.builder.SetInsertPoint(entryBlock);
    generator.callStackPush();
}

void LgsCodeGenVisitor::createEpilogue(LgsFunc* func) {
    branchAndStartBlock(func->getCleanupBlock(generator));
    if (func->hasDefers) {
        generator.callDefers();
    }
    if (!func->needsCleanup()) {
        generator.callPopStack();
        return;
    }
    if (func->returnStmts.size() == 1 && func->heapAllocExprs.size() == 1) {
        generator.callPopStack();
        const auto returnStmt = func->returnStmts.front();
        if (func->heapAllocExprs.front() == returnStmt->expr) {
            generator.builder.CreateRet(returnStmt->IRValue);
        } else {
            freeHeap(func);
        }
    } else if (!func->returnStmts.empty()) {
        auto rt = func->funcType->rt->getIRType(generator);
        if (func->funcType->rt->asDArray()) {
            rt = rt->getPointerTo();
        }
        const auto phi = generator.builder.CreatePHI(rt, func->returnStmts.size());
        for (const auto returnStmt : func->returnStmts) {
            phi->addIncoming(getIRValue(returnStmt->expr), returnStmt->parentBlock);
        }
        generator.callPopStack();
        generator.builder.CreateRet(phi);
    } else {
        generator.callPopStack();
    }
}

void LgsCodeGenVisitor::freeHeap(const LgsFunc* func) {
    for (const auto expr : func->heapAllocExprs) {
        expr->type->freeValue(generator, getIRValue(expr));
    }
}
