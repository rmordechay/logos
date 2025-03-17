#include "analysis/AntlrConverter.h"

#include "binary/LgsBinaryExpr.h"
#include "binary/LgsOperator.h"
#include "constants/LgsBoolConst.h"
#include "constants/LgsConst.h"
#include "constants/LgsFloatConst.h"
#include "constants/LgsIntConst.h"
#include "constants/LgsStrConst.h"
#include "unary//LgsInstance.h"
#include "unary//LgsSelection.h"
#include <exprs/unary/LgsArray.h>
#include <exprs/unary/LgsArrayIndex.h>
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsVariable.h>
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "types/LgsBool.h"
#include "types/LgsFloat.h"
#include "constants/LgsTypeConst.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <types/LgsStr.h>
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

LgsFuncImpl* AntlerConverter::getFuncImpl(LogosParser::FuncImplementationContext* ctx) {
    const auto rt = getFuncType(ctx);
    const auto signature = ctx->funcSignature();
    const auto name = signature->VARIABLE()->getText();
    vector<LgsParam*> params;
    if (signature->paramList()) {
        for (const auto& varDec : signature->paramList()->explicitVarDec()) {
            auto param = getParam(varDec);
            params.emplace_back(param);
        }
    }
    const auto func = new LgsFuncImpl(name, rt, params);
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setLocation(ctx->start);
    return func;
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

LgsMethodImpl* AntlerConverter::getMethodImpl(LogosParser::FuncImplementationContext* ctx, const LgsObject* obj) {
    const auto rt = getFuncType(ctx);
    const auto signature = ctx->funcSignature();
    const auto name = signature->VARIABLE()->getText();

    const auto method = new LgsMethodImpl(name, rt, obj->name);
    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    method->setLocation(ctx->start);

    const auto params = signature->paramList();
    if (!params) return method;

    for (const auto& varDec : params->explicitVarDec()) {
        auto param = getParam(varDec);
        method->params.emplace_back(param);
    }
    return method;
}

LgsField* AntlerConverter::getField(LogosParser::ExplicitVarDecContext* varDec, const size_t position, const string& parentName) {
    const auto name = varDec->VARIABLE()->getText();
    const auto type = getType(varDec->type()->TYPE());
    const auto expr = getExpr(varDec->expr());
    return new LgsField(name, parentName, type, position, expr);
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

    assignment->setLocation(ctx->start);
    return assignment;
}

LgsVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LgsVarDec(variableName, nullptr, logosExpr);
    logosVarDec->setLocation(ctx->start);
    return logosVarDec;
}

LgsVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto userType = getType(ctx->type()->TYPE());
    const auto varDec = new LgsVarDec(variableName, userType, expr);
    varDec->setLocation(ctx->start);
    return varDec;
}

LgsParam* AntlerConverter::getParam(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr());
    const auto userType = getType(ctx->type()->TYPE());
    const auto param = new LgsParam(variableName, userType, expr);
    param->setLocation(ctx->start);
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
    ifStmt->setLocation(ctx->start);
    return ifStmt;
}

LgsLoop* AntlerConverter::getLoopStatement(LogosParser::LoopStatementContext* ctx) {
    LgsLoop* loopStmt = nullptr;
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    if (const auto iterableExpr = ctx->iterableExpr) {
        const auto variable = new LgsVariable(ctx->exprList()->expr()[0]->getText());
        const auto loopVar = new LgsVariable(variable->name);
        loopStmt = new LgsForeachLoop(loopVar, getExpr(iterableExpr), stmts);
    } else if (const auto range = ctx->iterableRange) {
        const auto loopVarName = ctx->VARIABLE()->getText();
        const auto loopVar = new LgsVariable(loopVarName);
        loopStmt = new LgsRangeLoop(loopVar, getExpr(range->start), getExpr(range->end), stmts);
    } else {
        assert(false && "No loop statements found");
    }
    loopStmt->setLocation(ctx->start);
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
    logosBinaryExpr->setLocation(ctx->start);
    return logosBinaryExpr;
}

LgsUnaryExpr* AntlerConverter::getArray(LogosParser::ArrayContext* ctx) {
    const auto array = new LgsArray();
    for (const auto& expr : ctx->expr()) {
        array->elements.emplace_back(getExpr(expr));
    }
    array->setLocation(ctx->start);
    return array;
}

LgsVariable* AntlerConverter::getVariable(const string& varName, const ParserRuleContext* ctx) {
    const auto variable = new LgsVariable(varName);
    variable->setLocation(ctx->start);
    return variable;
}

LgsFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    vector<LgsExpr*> args;
    if (ctx->funcArgList()) {
        for (const auto& arg : ctx->funcArgList()->funcArg()) {
            auto argExpr = getExpr(arg->expr());
            args.emplace_back(argExpr);
        }
    }
    const auto funcCall = new LgsFuncCall(name, args);
    funcCall->setLocation(ctx->start);
    return funcCall;
}

LgsSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    vector exprs = {getFirstSelection(ctx)};
    const auto innerExprs = getSelectionInnerExprs(ctx);
    exprs.insert(exprs.end(), innerExprs.begin(), innerExprs.end());
    const auto selection = new LgsSelection(exprs);
    selection->setLocation(ctx->start);
    return selection;
}

LgsUnaryExpr* AntlerConverter::getFirstSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = ctx->firstSelectionElement();
    if (const auto variable = firstExpr->VARIABLE()) {
        return getVariable(variable->getText(), ctx);
    }
    if (const auto selfInstance = firstExpr->SELF_INSTANCE()) {
        return getVariable(selfInstance->getText(), ctx);
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
    if (const auto selfClass = firstExpr->SELF_CLASS()) {
        return getTypeConstant(selfClass, ctx);
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
        } else if (const auto funcCall = expr->funcCall()) {
            const auto logosFuncCall = getFuncCall(funcCall);
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
    instance->setLocation(ctx->start);
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

LgsConst* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) {
    LgsConst* constant = nullptr;
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        constant = new LgsIntConst(value);
    }
    if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        constant = new LgsFloatConst(value);
    }
    if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == "true";
        constant = new LgsBoolConst(value);
    }
    if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        if (value.size() == 1) {
            constant = new LgsCharConst(value[0]);
        }
        else {
            const auto strConst = new LgsStrConst(value);
            strConst->cleanStr();
            constant = strConst;
        }
    }
    constant->setLocation(ctx->start);
    return constant;
}

LgsTypeConst* AntlerConverter::getTypeConstant(tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) {
    const auto typeConst = new LgsTypeConst(getType(type));
    typeConst->setLocation(ctx->start);
    return typeConst;
}

LgsType* AntlerConverter::getType(tree::TerminalNode* type) {
    if (!type) return &LOGOS_VOID;
    const auto typeText = type->getText();
    if (typeText == LOGOS_INT.getName()) return &LOGOS_INT;
    if (typeText == LOGOS_FLOAT.getName()) return &LOGOS_FLOAT;
    if (typeText == LOGOS_BOOL.getName()) return &LOGOS_BOOL;
    if (typeText == LOGOS_STR.getName()) return &LOGOS_STR;
    if (typeText == "") return &LOGOS_VOID;
    return new LgsObject(type->getText());
}

LgsType* AntlerConverter::getFuncType(LogosParser::FuncImplementationContext* ctx) {
    const auto signature = ctx->funcSignature();
    if (signature->type()) {
        return getType(signature->type()->TYPE());
    }
    return &LOGOS_VOID;
}