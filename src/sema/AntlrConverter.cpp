#include "sema/AntlrConverter.h"

#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosConstant.h"
#include "exprs/LogosOperator.h"
#include "exprs/LogosSelection.h"
#include "object/LogosField.h"
#include "stmts/LogosReturn.h"

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

    for (const auto& func : funcImplementations) {
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
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto obj = new LogosObject(objName);
    for (int i = 0; i < ctx->explicitVarDec().size(); ++i) {
        const auto varDec = ctx->explicitVarDec()[i];
        const auto field = getField(varDec, objName, i);
        obj->fields[field->name] = field;
    }
    for (const auto& func : ctx->funcImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto userFunc = getFunc(func);
        userFunc->parentName = objName;
        obj->funcs[funcName] = userFunc;
    }
    return obj;
}

LogosField* AntlerConverter::getField(LogosParser::ExplicitVarDecContext* varDec, const string& parentName, const size_t position) {
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
        for (const auto& param : params->explicitVarDec()) {
            auto varDec = getExplicitVarDec(param);
            logosUserFunc->params.emplace_back(varDec);
        }
    }
    logosUserFunc->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    return logosUserFunc;
}

LogosStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    vector<LogosStmt*> stmts;
    for (const auto& statement: ctx->statement()) {
        auto stmt = getStmt(statement);
        stmts.emplace_back(stmt);
    }
    return new LogosStmtBlock(stmts);
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

LogosFieldDefinition* AntlerConverter::getFieldDef(LogosParser::FieldDefContext* ctx) {
    vector<string> fields;
    for (const auto& variable : ctx->VARIABLE()) {
        fields.emplace_back(variable->getText());
    }
    const auto expr = getExpr(ctx->expr());
    const auto fieldAssignment = new LogosFieldDefinition(fields, expr);
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

LogosLoop* AntlerConverter::getLoopStatement(LogosParser::LoopStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto loopStmt = new LogosLoop(expr, stmts);
    loopStmt->setPosition(ctx->start, filePath);
    return loopStmt;
}

LogosExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        return getUnaryExpr(unary);
    }
    if (const auto array = ctx->array()) {
        return getArray(array);
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

    if (const auto selection = ctx->selection()) {
        return getSelection(selection);
    }

    if (const auto constructor = ctx->constructor()) {
        return getInstance(constructor);
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCall(funcCall);
    }

    return nullptr;
}

LogosExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LogosBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setPosition(ctx->start, filePath);
    return logosBinaryExpr;
}

LogosExpr* AntlerConverter::getArray(LogosParser::ArrayContext* array) {

}

LogosUnaryExpr* AntlerConverter::getSelectionElementExpr(LogosParser::SelectionElementContext* ctx) {
    if (const auto variable = ctx->VARIABLE()) {
        const auto logosVariable = new LogosVariable(variable->getText());
        logosVariable->setPosition(ctx->start, filePath);
        return logosVariable;
    }

    if (const auto constructor = ctx->constructor()) {
        return getInstance(constructor);
    }

    if (const auto funcCall = ctx->funcCall()) {
        return getFuncCall(funcCall);
    }

    return nullptr;
}

LogosSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* selection) {
    vector<LogosUnaryExpr*> exprs;
    for (const auto& unaryExpr : selection->selectionElement()) {
        auto expr = getSelectionElementExpr(unaryExpr);
        exprs.emplace_back(expr);
    }
    return new LogosSelection(exprs);
}

LogosInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto name = ctx->TYPE()->getText();
    const auto instance = new LogosInstance(name);
    instance->setPosition(ctx->start, filePath);
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

LogosFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto funcCallExpr = new LogosFuncCall(name);
    funcCallExpr->setPosition(ctx->start, filePath);
    const auto funcArgList = ctx->funcArgList();
    if (funcArgList) {
        const auto args = funcArgList->funcArg();
        for (const auto& arg : args) {
            auto argExpr = getExpr(arg->expr());
            funcCallExpr->args.emplace_back(argExpr);
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
