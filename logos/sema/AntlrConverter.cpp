#include "AntlrConverter.h"

LogosFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx) {
    LogosFile* logosFile = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        logosFile = getMainFile(mainFileCtx);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        logosFile = getObjFile(objFileCtx);
    }
    logosFile->imports = getImportsStmt(ctx->importStatement());
    return logosFile;
}

LogosMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LogosMainFile();

    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNCTION) {
            const auto mainFunc = new LogosUserFunc(LOGOS_MAIN_FUNCTION, &LOGOS_INT);
            const auto statements = func->funcBody()->statementsBlock()->statement();
            for (const auto statement : statements) {
                auto logosStmt = getStmt(statement);
                mainFunc->stmts.emplace_back(logosStmt);
            }
            mainFile->mainFunc = mainFunc;
        } else {
            auto x = getFunc(func);
            mainFile->funcs.emplace_back(x);
        }
    }
    return mainFile;
}

LogosObject* AntlerConverter::getObject(LogosParser::ObjectFileContext* ctx) {
    const auto obj = new LogosObject();
    for (const auto varDec : ctx->explicitVarDec()) {
        auto funcName = varDec->VARIABLE()->getText();
        auto logosVarDec = getVarDec(varDec);
        obj->fields.emplace_back(logosVarDec);
    }
    for (const auto func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        auto logosFunc = getFunc(func);
        obj->funcs.emplace_back(logosFunc);
    }
    return obj;
}

LogosObjectFile* AntlerConverter::getObjFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LogosObjectFile(objName);
    objFile->obj = getObject(ctx);
    return objFile;
}

LogosFunc *AntlerConverter::getFunc(LogosParser::FuncImplementationContext* ctx) {
    const auto funcSignature = ctx->funcSignature();
    const auto funcName = funcSignature->VARIABLE()->getText();
    const auto& type = getType(funcSignature->TYPE());
    const auto logosUserFunc = new LogosUserFunc(funcName, &type);

    const auto args = funcSignature->variableDefintionList();
    if (args) {
        const auto params = args->explicitVarDec();
        for (const auto param : params) {
            const auto& argType = getType(param->TYPE());
            const auto logosVarDec = new LogosVarDec(param->VARIABLE()->getText(), &argType);
            logosUserFunc->params.push_back(logosVarDec);
        }
    }
    logosUserFunc->stmts = getStmtList(ctx->funcBody()->statementsBlock());
    return logosUserFunc;
}

vector<LogosImportStmt*> AntlerConverter::getImportsStmt(LogosParser::ImportStatementContext* ctx) {
    vector<LogosImportStmt*> imports;
    if (ctx) {
        vector<const LogosType*> qualifiedImport;
        const auto type = ctx->importPath()[0]->TYPE()[0];
        new LogosImportStmt(&getType(type));
    }
    return imports;
}

vector<LogosStmt*> AntlerConverter::getStmtList(LogosParser::StatementsBlockContext* ctx) {
    vector<LogosStmt*> stmts;
    for (const auto statement: ctx->statement()) {
        stmts.push_back(getStmt(statement));
    }
    return stmts;
}

LogosStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto implicitVarDec = ctx->implicitVarDec()) {
        return getVarDec(implicitVarDec);
    }
    if (const auto explicitVarDec = ctx->explicitVarDec()) {
        return getVarDec(explicitVarDec);
    }
    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }
    if (const auto ifStmt = ctx->ifStatement()) {
        return getIfStatement(ifStmt);
    }
    if (const auto returnStmt = ctx->returnStatement()) {
        return new LogosReturnStmt(getExpr(returnStmt->expr()));
    }
    return nullptr;
}

LogosVarDec* AntlerConverter::getVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    return new LogosVarDec(variableName, logosExpr);
}

LogosVarDec* AntlerConverter::getVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    return new LogosVarDec(variableName, logosExpr);
}

LogosIfStmt* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtList(ctx->statementsBlock());
    return new LogosIfStmt(expr, stmts);
}

LogosExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    return new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
}

LogosUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto constant = ctx->constant()) {
        return getConstantExpr(constant);
    }

    if (const auto variable = ctx->VARIABLE()) {
        return new LogosVariableExpr(variable->getText());
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCallExpr(funcCall);
    }

    if (const auto funcCall = ctx->constructorCall()) {
        return getConstructorCallExpr(funcCall);
    }
    return nullptr;
}

LogosConstructorExpr* AntlerConverter::getConstructorCallExpr(LogosParser::ConstructorCallContext* ctx) {
    const auto name = ctx->TYPE()->getText();
    const auto constructorExpr = new LogosConstructorExpr(name);
    const auto args = ctx->funcArgList();
    if (!args) {
        return constructorExpr;
    }
    for (const auto arg : args->funcArg()) {
        auto argExpr = getExpr(arg->expr());
        constructorExpr->args.push_back(argExpr);
    }
    return constructorExpr;
}

LogosFuncCallExpr* AntlerConverter::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LogosFuncCallExpr(name);
    const auto args = ctx->funcArgList()->funcArg();
    for (const auto arg : args) {
        auto argExpr = getExpr(arg->expr());
        funcCallExpr->args.push_back(argExpr);
    }
    return funcCallExpr;
}

LogosUnaryExpr* AntlerConverter::getConstantExpr(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstantExpr(&LOGOS_INT, value);
    }
    return nullptr;
}

const LogosType& AntlerConverter::getType(antlr4::tree::TerminalNode* type) {
    if (type->getText() == LogosInt::name) return LOGOS_INT;
    return LOGOS_VOID;
}