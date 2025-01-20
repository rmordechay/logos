#include "AntlrConverter.h"

#include "files/LogosObjectFile.h"

LogosFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx) {
    if (const auto mainFileCtx = ctx->mainFile()) {
        return getMainFile(mainFileCtx);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        return getObjFile(objFileCtx);
    }
    return nullptr;
}

LogosMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LogosMainFile();
    mainFile->imports = getImports(ctx->importStatement());

    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNCTION) {
            const auto mainFunc = new LogosUserFunc(LOGOS_MAIN_FUNCTION, &LOGOS_INT);
            const auto statements = func->funcBody()->statementsBlock()->statement();
            for (const auto statement : statements) {
                mainFunc->stmts.push_back(getStmt(statement));
            }
            mainFile->mainFunc = mainFunc;
        } else {
            mainFile->funcs.push_back(getFunc(func));
        }
    }

    return mainFile;
}

LogosObjectFile* AntlerConverter::getObjFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LogosObjectFile(objName);
    objFile->imports = getImports(ctx->importStatement());
    objFile->obj = new LogosObject(new LogosUserType(objName));
    for (const auto varDec : ctx->explicitVarDec()) {
        auto funcName = varDec->VARIABLE()->getText();
        objFile->obj->fields.push_back(getVarDec(varDec));
    }

    for (const auto func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        objFile->obj->funcs.push_back(getFunc(func));
    }

    return objFile;
}

LogosFunc *AntlerConverter::getFunc(LogosParser::FuncImplementationContext* ctx) {
    const auto funcSignature = ctx->funcSignature();
    const auto funcName = funcSignature->VARIABLE()->getText();
    const auto type = getType(funcSignature->TYPE());
    const auto logosUserFunc = new LogosUserFunc(funcName, type);

    const auto args = funcSignature->variableDefintionList();
    if (args) {
        const auto params = args->explicitVarDec();
        for (const auto param : params) {
            const auto argType = getType(param->TYPE());
            const auto logosVarDec = new LogosVarDec(param->VARIABLE()->getText(), argType);
            logosUserFunc->params.push_back(logosVarDec);
        }
    }
    logosUserFunc->stmts = getStmtList(ctx->funcBody()->statementsBlock());
    return logosUserFunc;
}

vector<vector<const LogosType*>> AntlerConverter::getImports(LogosParser::ImportStatementContext* ctx) {
    vector<vector<const LogosType*>> imports;
    if (ctx) {
        vector<const LogosType*> imp;
        for (const auto importPath : ctx->importPath()) {
            for (const auto type : importPath->TYPE()) {
                imp.push_back(getType(type));
            }
            imports.push_back(imp);
        }
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
    const auto logosObject = new LogosObject(new LogosUserType(name));
    return new LogosConstructorExpr(logosObject);
}

LogosFuncCallExpr* AntlerConverter::getFuncCallExpr(LogosParser::FuncCallContext* ctx) {
    const auto funcName = ctx->VARIABLE()->getText();
    const auto logosFunc = new LogosFuncCallExpr(funcName);
    const auto funcArgs = ctx->funcArgList()->funcArg();
    for (const auto funcArg : funcArgs) {
        auto argExpr = getExpr(funcArg->expr());
        logosFunc->args.push_back(argExpr);
    }
    return logosFunc;
}

LogosUnaryExpr* AntlerConverter::getConstantExpr(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstantExpr(&LOGOS_INT, value);
    }
    return nullptr;
}

const LogosType* AntlerConverter::getType(antlr4::tree::TerminalNode* type) {
    if (type->getText() == LogosInt::name) return &LOGOS_INT;
    return &LOGOS_VOID;
}