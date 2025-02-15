#include "sema/AntlrConverter.h"

#include "stmts/LogosFieldDef.h"

LogosFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx, const filesystem::path& filePath) {
    LogosFile* logosFile = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        logosFile = getMainFile(mainFileCtx);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        logosFile = getObjFile(objFileCtx);
    }
    logosFile->path = filePath;
    return logosFile;
}

LogosMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx) {
    const auto funcImplementations = ctx->funcImplementation();
    const auto mainFile = new LogosMainFile(filePath);

    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNCTION) {
            const auto mainFunc = new LogosUserFunc(LOGOS_MAIN_FUNCTION, &LOGOS_INT);
            mainFile->mainFunc = mainFunc;
            const auto statementsBlock = func->funcBody()->statementsBlock();
            mainFunc->stmtBlock = getStmtBlock(statementsBlock);

        } else {
            auto logosFunc = getFunc(func);
            mainFile->funcs.emplace_back(logosFunc);
        }
    }
    return mainFile;
}

LogosObjectFile* AntlerConverter::getObjFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LogosObjectFile(objName, filePath);
    objFile->obj = getObject(ctx);
    return objFile;
}

LogosObject* AntlerConverter::getObject(LogosParser::ObjectFileContext* ctx) {
    const auto name = ctx->objectDeclaration()->TYPE()->getText();
    const auto obj = new LogosObject(name);
    for (int i = 0; i < ctx->explicitVarDec().size(); ++i) {
        const auto varDec = ctx->explicitVarDec()[i];
        const auto field = getField(varDec, name, i);
        obj->fields[field->name] = field;
    }
    for (const auto func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto userFunc = getFunc(func);
        obj->funcs[funcName] = userFunc;
    }
    return obj;
}

LogosField* AntlerConverter::getField(LogosParser::ExplicitVarDecContext* varDec, const string& parentName, const int position) {
    const auto name = varDec->VARIABLE()->getText();
    const auto type = getType(varDec->TYPE());
    const auto expr = getExpr(varDec->expr());
    return new LogosField(name, parentName, type, expr, position);
}

LogosUserFunc* AntlerConverter::getFunc(LogosParser::FuncImplementationContext* ctx) {
    const auto funcSignature = ctx->funcSignature();
    const auto funcName = funcSignature->VARIABLE()->getText();
    const auto type = getType(funcSignature->TYPE());
    const auto logosUserFunc = new LogosUserFunc(funcName, type);

    const auto params = funcSignature->paramList();
    if (params) {
        for (const auto param : params->explicitVarDec()) {
            auto varDec = getExplicitVarDec(param);
            logosUserFunc->params.push_back(varDec);
        }
    }
    logosUserFunc->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    return logosUserFunc;
}

LogosStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto fieldDef = ctx->fieldDef()) {
        return getFieldDef(fieldDef);
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
    if (const auto returnStmt = ctx->returnStatement()) {
        return new LogosReturn(getExpr(returnStmt->expr()));
    }
    return nullptr;
}

LogosStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    vector<LogosStmt*> stmts;
    for (const auto statement: ctx->statement()) {
        stmts.push_back(getStmt(statement));
    }
    return new LogosStmtBlock(stmts);
}

LogosFieldDef* AntlerConverter::getFieldDef(LogosParser::FieldDefContext* ctx) {
    vector<string> fields;
    for (const auto variable : ctx->VARIABLE()) {
        fields.emplace_back(variable->getText());
    }
    const auto expr = getExpr(ctx->expr());
    const auto fieldAssignment = new LogosFieldDef(fields, expr);
    fieldAssignment->setPosition(ctx->start, filePath);
    return fieldAssignment;
}

LogosVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto logosVarDec = new LogosVarDec(variableName, nullptr, logosExpr);
    logosVarDec->setPosition(ctx->start, filePath);
    return logosVarDec;
}

LogosVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto logosExpr = getExpr(ctx->expr());
    const auto userType = getType(ctx->TYPE());
    const auto logosVarDec = new LogosVarDec(variableName, userType, logosExpr);
    logosVarDec->setPosition(ctx->start, filePath);
    return logosVarDec;
}

LogosIf* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto ifStmt = new LogosIf(expr, stmts);
    ifStmt->setPosition(ctx->start, filePath);
    return ifStmt;
}

LogosExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    if (const auto selection = ctx->selection()) {
        return getSelection(selection);
    }
    return getBinaryExpr(ctx);
}

LogosUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->VARIABLE()) {
        const auto logosVariable = new LogosVariable(variable->getText());
        logosVariable->setPosition(ctx->start, filePath);
        return logosVariable;
    }

    if (const auto constant = ctx->constant()) {
        return getConstant(constant);
    }

    if (const auto constructor = ctx->constructorCall()) {
        return getConstructor(constructor);
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCall(funcCall);
    }

    return nullptr;
}

LogosSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* selection) {
    vector<LogosUnaryExpr*> exprs;
    for (const auto unaryExpr : selection->unaryExpr()) {
        auto expr = getUnaryExpr(unaryExpr);
        exprs.push_back(expr);
    }
    return new LogosSelection(exprs);
}

LogosExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setPosition(ctx->start, filePath);
    return logosBinaryExpr;
}

LogosConstructor* AntlerConverter::getConstructor(LogosParser::ConstructorCallContext* ctx) {
    const auto name = ctx->TYPE()->getText();
    const auto constructorExpr = new LogosConstructor(name);
    constructorExpr->setPosition(ctx->start, filePath);
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

LogosFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LogosFuncCall(name);
    funcCallExpr->setPosition(ctx->start, filePath);
    const auto funcArgList = ctx->funcArgList();
    if (funcArgList) {
        const auto args = funcArgList->funcArg();
        for (const auto arg : args) {
            auto argExpr = getExpr(arg->expr());
            funcCallExpr->args.push_back(argExpr);
        }
    }
    return funcCallExpr;
}

LogosUnaryExpr* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) {
    if (const auto intToken = ctx->INTEGER()) {
        const auto value = stoi(intToken->getText());
        return new LogosConstant(&LOGOS_INT, value);
    }
    return nullptr;
}

LogosType* AntlerConverter::getType(antlr4::tree::TerminalNode* type) {
    if (!type) return &LOGOS_VOID;
    if (type->getText() == INT_TYPE_NAME) return &LOGOS_INT;
    return &LOGOS_VOID;
}
