#include "SemAnalyser.h"

#include "LogosConfigs.h"
#include "LogosErrors.h"
#include "LogosParser.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstantExpr.h"
#include "exprs/LogosFuncCallExpr.h"
#include "exprs/LogosOperator.h"
#include "exprs/LogosVariableExpr.h"
#include "files/LogosMainFile.h"
#include "funcs/LogosPrint.h"
#include "funcs/LogosUserFunc.h"
#include "stmts/LogosIfStmt.h"
#include "stmts/LogosVarDec.h"

void SemAnalyser::analyseProject(const LogosFile* mainFile) {
    visitMainFile(mainFile);
}

void SemAnalyser::visitMainFile(const LogosFile* mainFile) {
    const auto fileCtx = mainFile->fileCtx;
    map<string, LogosSymbol*> rootFrame;
    rootFrame[LOGOS_PRINT.name] = new LogosSymbol(const_cast<LogosFunc*>(&LOGOS_PRINT));
    stack.push(rootFrame);

    const auto funcImplementations = fileCtx->mainFile()->funcImplementation();
    vector<LogosParser::FuncImplementationContext*> funcsWithoutMain;
    LogosParser::FuncImplementationContext* mainFunc = nullptr;
    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNCTION) {
            mainFunc = func;
        } else {
            funcsWithoutMain.push_back(func);
        }
    }

    visitMainFunc(mainFunc);
    for (const auto func : funcsWithoutMain) {
        visitFuncImplementation(func);
    }
}

void SemAnalyser::visitMainFunc(LogosParser::FuncImplementationContext* ctx) {
    const auto mainFunc = new LogosUserFunc(LOGOS_MAIN_FUNCTION, LOGOS_INT);
    stack.top()[LOGOS_MAIN_FUNCTION] = new LogosSymbol(mainFunc);
    visitFuncImplementation(ctx);
}

void SemAnalyser::visitFuncImplementation(LogosParser::FuncImplementationContext* ctx) {
    const auto funcSignature = ctx->funcSignature();
    visitUserFuncDef(funcSignature);
    const auto statements = ctx->funcBody()->statementsBlock()->statement();
    for (const auto statement : statements) {
        visitStatement(statement);
    }
}

void SemAnalyser::visitUserFuncDef(LogosParser::FuncSignatureContext* const ctx) {
    const auto type = ctx->TYPE();
    auto funcName = ctx->VARIABLE()->getText();
    LogosUserFunc* logosUserFunc;
    if (type) {
        logosUserFunc = new LogosUserFunc(funcName, getType(type->getText()));
    } else {
        logosUserFunc = new LogosUserFunc(funcName);
    }
    const auto args = ctx->variableDefintionList();
    if (args) {
        const auto params = args->explicitVarDec();
        for (const auto param : params) {
            const LogosType& argType = getType(param->TYPE()->getText());
            const auto logosVarDec = new LogosVarDec(param->VARIABLE()->getText(), argType);
            logosUserFunc->params.push_back(logosVarDec);
        }
    }
    stack.top()[funcName] = new LogosSymbol(logosUserFunc);
    codeNodes.push_back(logosUserFunc);
}

void SemAnalyser::visitStatementList(const std::vector<LogosParser::StatementContext*>& ctx) {
    map<string, LogosSymbol*> frame;
    auto currentFrame = stack.top();
    frame.insert(currentFrame.begin(), currentFrame.end());
    stack.push(frame);
    for (const auto statement : ctx) {
        visitStatement(statement);
    }
    stack.pop();
}

void SemAnalyser::visitStatement(LogosParser::StatementContext* ctx) {
    if (const auto implicitVarDec = ctx->implicitVarDec()) {
        visitImplicitVarDec(implicitVarDec);
    } else if (const auto explicitVarDec = ctx->explicitVarDec()) {
        visitExplicitVariableDec(explicitVarDec);
    } else if (const auto funcCall = ctx->funcCall()) {
        visitFuncCall(funcCall);
    } else if (const auto ifStmt = ctx->ifStatement()) {
        visitIfStatement(ifStmt);
    }
}

void SemAnalyser::visitImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    addSymbol(variableName, logosExpr);
    codeNodes.push_back(new LogosVarDec(variableName, logosExpr));
}

void SemAnalyser::visitExplicitVariableDec(LogosParser::ExplicitVarDecContext* ctx) {
}


void SemAnalyser::visitFuncCall(LogosParser::FuncCallContext* ctx) {
    codeNodes.push_back(getFuncCallExpr(ctx));
}

void SemAnalyser::visitIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto ifStmt = new LogosIfStmt(expr);
    codeNodes.push_back(ifStmt);
    const auto startIndex = codeNodes.size();
    const auto statements = ctx->statementsBlock()->statement();
    visitStatementList(statements);
    const auto endIndex = codeNodes.size();

    ifStmt->codeNodes.insert(ifStmt->codeNodes.begin(), make_move_iterator(codeNodes.begin() + startIndex),
                             make_move_iterator(codeNodes.begin() + endIndex));
    codeNodes.erase(codeNodes.begin() + startIndex, codeNodes.begin() + endIndex);
}

const LogosType& SemAnalyser::getType(const string& typeText) {
    if (typeText == LogosInt::name) return LOGOS_INT;
    return LOGOS_INT;
}

LogosExpr* SemAnalyser::getExpr(LogosParser::ExprContext* ctx) {
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    return new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
}

LogosUnaryExpr* SemAnalyser::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        return getVariableExpr(variable->getText());
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    return nullptr;
}

LogosUnaryExpr* SemAnalyser::getVariableExpr(const string& symbolName) {
    if (const auto resolvedSymbol = resolveSymbol(symbolName)) {
        return new LogosVariableExpr(*resolvedSymbol->type, symbolName);
    }
    return nullptr;
}


LogosUnaryExpr* SemAnalyser::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto funcName = ctx->VARIABLE()->getText();
    const auto logosFunc = static_cast<LogosFunc*>(resolveSymbol(funcName)->value);
    vector<LogosExpr*> args;
    for (const auto funcArg : ctx->funcArgList()->funcArg()) {
        args.push_back(getExpr(funcArg->expr()));
    }
    return new LogosFuncCallExpr(*logosFunc, args);
}

LogosUnaryExpr* SemAnalyser::getConstantExpr(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstantExpr(LOGOS_INT, value);
    }
    return nullptr;
}

void SemAnalyser::addSymbol(const string& variableName, LogosExpr* logosExpr) {
    stack.top()[variableName] = new LogosSymbol(logosExpr);
}

LogosSymbol* SemAnalyser::resolveSymbol(const string& symbolName) {
    auto frame = stack.top();
    const auto it = frame.find(symbolName);
    if (it == frame.end()) {
        return nullptr;
    }
    return it->second;
}

SemAnalyser::~SemAnalyser() {
    for (auto& [name, symbol] : stack.top()) {
        delete symbol;
    }
    for (const auto codeNode : codeNodes) {
        delete codeNode;
    }
}
