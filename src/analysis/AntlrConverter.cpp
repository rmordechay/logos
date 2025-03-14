#include "analysis/AntlrConverter.h"

#include "binary/LgsBinaryExpr.h"
#include "binary/LgsOperator.h"
#include "unary/LgsMethodCall.h"
#include "constants/LgsConstant.h"
#include "constants/LgsStringConst.h"
#include "unary//LgsInstance.h"
#include "unary//LgsSelection.h"
#include <exprs/unary/LgsArray.h>
#include <exprs/unary/LgsArrayIndex.h>
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsVariable.h>
#include "funcs/LgsParam.h"
#include "loops/LgsLoopVar.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"
#include "types/LgsFloat.h"
#include "constants/LgsTypeConst.h"

#include <LgsDefinitions.h>
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <types/LgsString.h>
#include <types/LgsVoid.h>

LgsFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath) {
    LgsFile* logosFile = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        logosFile = getMainFile(mainFileCtx, filePath);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        logosFile = getObjectFile(objFileCtx, filePath);
    }
    logosFile->absPath = filePath;
    return logosFile;
}

LgsMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx, const string& filePath) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LgsMainFile(filePath);
    for (const auto& func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNC) {
            const auto mainFunc = new LgsFuncImpl(LOGOS_MAIN_FUNC, &LOGOS_INT);
            mainFile->mainFunc = mainFunc;
            const auto statementsBlock = func->funcBody()->statementsBlock();
            mainFunc->stmtBlock = getStmtBlock(statementsBlock);
        } else {
            auto logosFunc = getFuncImpl(func);
            mainFile->funcs.emplace_back(logosFunc);
        }
    }
    return mainFile;
}

LgsObjectFile* AntlerConverter::getObjectFile(LogosParser::ObjectFileContext* ctx, const string& filePath) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LgsObjectFile(objName, filePath);
    objFile->obj = getObject(ctx);
    return objFile;
}

LgsObject* AntlerConverter::getObject(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto obj = new LgsObject(objName);
    for (int i = 0; i < ctx->explicitVarDec().size(); ++i) {
        const auto varDec = ctx->explicitVarDec()[i];
        const auto field = getField(varDec, i, obj->name);
        obj->fields[field->name] = field;
    }
    for (const auto& func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto method = getMethodImpl(func, obj);
        obj->methods[funcName] = method;
    }
    return obj;
}

LgsField* AntlerConverter::getField(LogosParser::ExplicitVarDecContext* varDec, const size_t position, const string& parentName) {
    const auto name = varDec->VARIABLE()->getText();
    const auto type = getType(varDec->type()->TYPE());
    const auto expr = getExpr(varDec->expr());
    return new LgsField(name, parentName, type, position, expr);
}

LgsFuncImpl* AntlerConverter::getFuncImpl(LogosParser::FuncImplementationContext* ctx) {
    const auto rt = getFuncType(ctx);
    const auto signature = ctx->funcSignature();
    const auto name = signature->VARIABLE()->getText();

    const auto func = new LgsFuncImpl(name, rt);
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setPosition(ctx->start);

    const auto params = signature->paramList();
    if (!params) return func;

    for (const auto& varDec : params->explicitVarDec()) {
        auto param = getParam(varDec);
        func->params.emplace_back(param);
    }
    return func;
}

LgsMethodImpl* AntlerConverter::getMethodImpl(LogosParser::FuncImplementationContext* ctx, LgsObject* obj) {
    const auto rt = getFuncType(ctx);
    const auto signature = ctx->funcSignature();
    const auto name = signature->VARIABLE()->getText();

    const auto method = new LgsMethodImpl(name, rt, obj->name);
    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    method->setPosition(ctx->start);

    const auto params = signature->paramList();
    if (!params) return method;

    for (const auto& varDec : params->explicitVarDec()) {
        auto param = getParam(varDec);
        method->params.emplace_back(param);
    }
    return method;
}

LgsStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    vector<LgsStmt*> stmts;
    for (const auto& statement : ctx->statement()) {
        auto stmt = getStmt(statement);
        stmts.emplace_back(stmt);
    }
    return new LgsStmtBlock(stmts);
}

LgsStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto fieldDef = ctx->assignment()) {
        return getAssignment(fieldDef);
    }
    if (const auto implicitVarDec = ctx->implicitVarDec()) {
        return getImplicitVarDec(implicitVarDec);
    }
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        return getExplicitVarDec(explicitVarDec);
    }
    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCall(funcCall);
    }
    if (const auto ifStmt = ctx->ifStatement()) {
        return getIfStatement(ifStmt);
    }
    if (const auto loopStmt = ctx->loopStatement()) {
        return getLoopStatement(loopStmt);
    }
    if (const auto returnStmt = ctx->returnStatement()) {
        return new LgsReturn(getExpr(returnStmt->expr()));
    }
    return nullptr;
}


LgsAssignment* AntlerConverter::getAssignment(LogosParser::AssignmentContext* ctx) {
    const auto assignment = new LgsAssignment();
    assignment->rvalue = getExpr(ctx->expr());

    if (const auto variable = ctx->VARIABLE()) {
        assignment->lvalue = getVariable(variable->getText(), ctx);
    } else if (const auto arrayIndex = ctx->arrayIndex()) {
        assignment->lvalue = getArrayIndex(arrayIndex);
    } else if (const auto selection = ctx->selection()) {
        assignment->lvalue = getSelection(selection);
    }

    assignment->setPosition(ctx->start);
    return assignment;
}

LgsVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LgsVarDec(variableName, nullptr, logosExpr);
    logosVarDec->setPosition(ctx->start);
    return logosVarDec;
}

LgsVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto userType = getType(ctx->type()->TYPE());
    const auto varDec = new LgsVarDec(variableName, userType, expr);
    varDec->setPosition(ctx->start);
    return varDec;
}

LgsParam* AntlerConverter::getParam(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto userType = getType(ctx->type()->TYPE());
    const auto param = new LgsParam(variableName, userType, expr);
    param->setPosition(ctx->start);
    return param;
}

LgsIf* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto ifStmt = new LgsIf(expr, stmts);
    for (const auto &elseIfStmt : ctx->elseIfStatement()) {
        auto elseIfExpr = getExpr(elseIfStmt->expr());
        auto elseIfStmtBlock = getStmtBlock(elseIfStmt->statementsBlock());
        ifStmt->elseIfConds.emplace_back(elseIfExpr);
        ifStmt->elseIfStmtBlocks.emplace_back(elseIfStmtBlock);
    }
    if (const auto &elseStmt = ctx->elseStatement()) {
        ifStmt->elseStmtBlock = getStmtBlock(elseStmt->statementsBlock());
    }
    ifStmt->setPosition(ctx->start);
    return ifStmt;
}

LgsLoop* AntlerConverter::getLoopStatement(LogosParser::LoopStatementContext* ctx) {
    LgsLoop* loopStmt = nullptr;
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    if (const auto iterableExpr = ctx->iterableExpr) {
        const auto variable = new LgsVariable(ctx->exprList()->expr()[0]->getText());
        const auto loopVar = new LgsLoopVar(variable->name);
        loopVar->element = new LgsArrayIndex(variable, {LOGOS_INT.getZeroValue()});
        loopStmt = new LgsForeachLoop(loopVar, getExpr(iterableExpr), stmts);
    } else if (const auto range = ctx->iterableRange) {
        const auto loopVarName = ctx->VARIABLE()->getText();
        const auto loopVar = new LgsLoopVar(loopVarName, &LOGOS_INT);
        loopStmt = new LgsRangeLoop(loopVar, getExpr(range->start), getExpr(range->end), stmts);
    } else {
        assert(false && "No loop statements found");
    }
    loopStmt->setPosition(ctx->start);
    return loopStmt;
}

LgsExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    return getBinaryExpr(ctx);
}

LgsUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->VARIABLE()) return getVariable(variable->getText(), ctx);
    if (const auto constant = ctx->constant()) return getConstant(constant);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (const auto constructor = ctx->constructor()) return getInstance(constructor);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto array = ctx->array()) return getArray(array);
    if (const auto arrayIndex = ctx->arrayIndex()) return getArrayIndex(arrayIndex);
    return nullptr;
}

LgsExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LgsBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setPosition(ctx->start);
    return logosBinaryExpr;
}

LgsUnaryExpr* AntlerConverter::getArray(LogosParser::ArrayContext* ctx) {
    const auto array = new LgsArray();
    for (const auto& expr : ctx->expr()) {
        array->elements.emplace_back(getExpr(expr));
    }
    array->setPosition(ctx->start);
    return array;
}

LgsVariable* AntlerConverter::getVariable(const string& varName, const ParserRuleContext* ctx) {
    const auto variable = new LgsVariable(varName);
    variable->setPosition(ctx->start);
    return variable;
}

LgsFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LgsFuncCall(name);
    const auto funcArgList = ctx->funcArgList();
    if (funcArgList) {
        const auto args = funcArgList->funcArg();
        for (const auto& arg : args) {
            auto argExpr = getExpr(arg->expr());
            funcCallExpr->args.emplace_back(argExpr);
        }
    }
    funcCallExpr->setPosition(ctx->start);
    return funcCallExpr;
}

LgsMethodCall* AntlerConverter::getMethodCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LgsMethodCall(name);
    const auto funcArgList = ctx->funcArgList();
    if (funcArgList) {
        const auto args = funcArgList->funcArg();
        for (const auto& arg : args) {
            auto argExpr = getExpr(arg->expr());
            funcCallExpr->args.emplace_back(argExpr);
        }
    }
    funcCallExpr->setPosition(ctx->start);
    return funcCallExpr;
}

LgsSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = getFirstSelection(ctx);
    const auto innerExprs = getSelectionInnerExprs(ctx);
    vector<LgsUnaryExpr*> exprs;
    exprs.emplace_back(firstExpr);
    exprs.insert(exprs.end(), innerExprs.begin(), innerExprs.end());
    const auto selection = new LgsSelection(exprs);
    selection->setPosition(ctx->start);
    return selection;
}

LgsUnaryExpr* AntlerConverter::getFirstSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = ctx->firstSelectionElement();
    if (const auto variable = firstExpr->VARIABLE()) {
        return getVariable(variable->getText(), ctx);
    }
    if (const auto self = firstExpr->SELF()) {
        return getVariable(self->getText(), ctx);
    }
    if (const auto funcCall = firstExpr->funcCall()) {
        return getFuncCall(funcCall);
    }
    if (const auto arrayIndex = firstExpr->arrayIndex()) {
        return getArrayIndex(arrayIndex);
    }
    if (const auto type = firstExpr->TYPE()) {
        return getTypeConstant(type, ctx);
    }
    return nullptr;
}

vector<LgsUnaryExpr*> AntlerConverter::getSelectionInnerExprs(LogosParser::SelectionContext* ctx) {
    const auto innerSelections = ctx->innerSelectionElement();
    vector<LgsUnaryExpr*> exprs;
    exprs.reserve(innerSelections.size());
    for (int i = 0; i < innerSelections.size(); ++i) {
        const auto& expr = innerSelections[i];
        if (const auto field = expr->VARIABLE()) {
            const auto logosField = getVariable(field->getText(), expr);
            exprs.emplace_back(logosField);
        } else if (const auto methodCall = expr->funcCall()) {
            const auto logosFuncCall = getMethodCall(methodCall);
            exprs.emplace_back(logosFuncCall);
        } else if (const auto arrayIndex = expr->arrayIndex()) {
            const auto logosArrayIndex = getArrayIndex(arrayIndex);
            exprs.emplace_back(logosArrayIndex);
        }
    }
    return exprs;
}

LgsInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto name = ctx->TYPE()->getText();
    const auto instance = new LgsInstance(name);
    instance->setPosition(ctx->start);
    const auto args = ctx->funcArgList();
    if (!args) {
        return instance;
    }

    for (const auto& arg : args->funcArg()) {
        auto argExpr = getExpr(arg->expr());
        instance->args.emplace_back(argExpr);
    }
    return instance;
}

LgsArrayIndex* AntlerConverter::getArrayIndex(LogosParser::ArrayIndexContext* ctx) {
    LgsUnaryExpr* baseExpr;
    if (const auto variable = ctx->VARIABLE()) {
        baseExpr = getVariable(variable->getText(), ctx);
    } else {
        baseExpr = getFuncCall(ctx->funcCall());
    }

    vector<LgsExpr*> indexExprs;
    for (const auto& expr : ctx->expr()) {
        indexExprs.emplace_back(getExpr(expr));
    }

    return new LgsArrayIndex(baseExpr, indexExprs);
}


LgsUnaryExpr* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LgsConstant(&LOGOS_INT, value);
    }
    if (const auto intToken = ctx->FLOAT()) {
        const auto value = stof(intToken->getText());
        return new LgsConstant(&LOGOS_FLOAT, value);
    }
    if (const auto intToken = ctx->BOOL()) {
        const auto value = intToken->getText() == "true";
        return new LgsConstant(&LOGOS_BOOL, value);
    }
    if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        return new LgsConstant(&LOGOS_STRING, new LgsStringConst(value));
    }
    return nullptr;
}

LgsTypeConst* AntlerConverter::getTypeConstant(tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) {
    const auto typeConst = new LgsTypeConst(getType(type));
    typeConst->setPosition(ctx->start);
    return typeConst;
}

LgsType* AntlerConverter::getType(tree::TerminalNode* type) {
    if (!type) return &LOGOS_VOID;
    const auto typeText = type->getText();
    if (typeText == LOGOS_INT.getName()) return &LOGOS_INT;
    if (typeText == LOGOS_FLOAT.getName()) return &LOGOS_FLOAT;
    if (typeText == LOGOS_BOOL.getName()) return &LOGOS_BOOL;
    if (typeText == LOGOS_STRING.getName()) return &LOGOS_STRING;
    if (typeText == "") return &LOGOS_VOID;
    // TODO memory leak
    return new LgsObject(typeText);
}

LgsType* AntlerConverter::getFuncType(LogosParser::FuncImplementationContext* ctx) {
    const auto signature = ctx->funcSignature();
    if (signature->type()->TYPE()) return getType(signature->type()->TYPE());
    return &LOGOS_VOID;
}