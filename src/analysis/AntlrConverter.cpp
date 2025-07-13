#include "analysis/AntlrConverter.h"

#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "files/LgsInterfaceFile.h"
#include "LogosLexer.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/LgsCast.h"
#include "exprs/LgsNullValue.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/constants/LgsBoolConst.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include <exprs/unary/LgsArrayExpr.h>
#include <exprs/unary/LgsIterIndex.h>
#include <exprs/unary/LgsFuncCall.h>
#include <exprs/unary/LgsVariable.h>
#include "funcs/LgsParam.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/unary/constants/LgsTypeConst.h"
#include "stmts/LgsBreakStmt.h"
#include "stmts/LgsContinueStmt.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "extern/LgsCLang.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "funcs/LgsMainFunc.h"
#include "loops/LgsInfiniteLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsArray.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/LgsMap.h"
#include "types/LgsNullable.h"
#include "types/LgsUnknownType.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"
#include "utils/LgsUtils.h"
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <types/LgsStr.h>
#include <types/primitives/LgsVoid.h>

LgsFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx) {
    LgsFile* file = nullptr;
    if (const auto mainFileCtx = ctx->mainFile()) {
        file = getMainFile(mainFileCtx);
    }
    if (const auto objFileCtx = ctx->objectFile()) {
        file = getObjectFile(objFileCtx);
    }
    if (const auto interfaceFileCtx = ctx->interfaceFile()) {
        file = getInterfaceFile(interfaceFileCtx);
    }
    if (ctx->extern_()) {
        for (const auto importPath : ctx->extern_()->STRING()) {
            auto basicString = importPath->getText();
            auto str = getStrConst(importPath);
            file->externFiles.push_back(str);
        }
    }
    file->absPath = filePath;
    return file;
}

LgsObjectFile* AntlerConverter::getObjectFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->IDENTIFIER()->getText();
    const auto objFile = new LgsObjectFile(objName, filePath);
    objFile->obj = getObject(ctx->objectBody(), objName, !!ctx->objectDeclaration()->SINGLETON());
    if (!objFile->obj) return nullptr;
    globals.addSymbol(objName, LgsSymbol(objFile->obj), &errHandler);
    return objFile;
}

LgsFile* AntlerConverter::getInterfaceFile(LogosParser::InterfaceFileContext* ctx) {
    const auto interfaceName = ctx->interfaceDeclaration()->IDENTIFIER()->getText();
    const auto interfaceFile = new LgsInterfaceFile(interfaceName, filePath);
    interfaceFile->interface = getInterface(ctx->interfaceBody(), interfaceName);
    globals.addSymbol(interfaceName, LgsSymbol(interfaceFile->interface), &errHandler);
    return interfaceFile;
}

LgsMainFile* AntlerConverter::getMainFile(LogosParser::MainFileContext* ctx) {
    const auto funcImplementations = ctx->funcImpl();
    const auto mainFile = new LgsMainFile(filePath);

    for (const auto enumDeclaration : ctx->enumDeclaration()) {
        auto lgsEnum = getEnum(enumDeclaration);
        mainFile->enums.emplace_back(lgsEnum);
        mainFile->symbolTable.addEnum(lgsEnum);
    }

    for (const auto object : ctx->object()) {
        auto lgsObject = getObject(object->objectBody(), object->IDENTIFIER()->getText(), !!object->SINGLETON());
        if (!lgsObject) continue;
        mainFile->objects.emplace_back(lgsObject);
        mainFile->symbolTable.addSymbol(lgsObject->name, LgsSymbol(lgsObject), &errHandler);
    }

    for (const auto interface : ctx->interface()) {
        auto lgsInterface = getInterface(interface->interfaceBody(), interface->IDENTIFIER()->getText());
        mainFile->interfaces.push_back(lgsInterface);
        mainFile->symbolTable.addSymbol(lgsInterface->name, LgsSymbol(lgsInterface), &errHandler);
    }

    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->IDENTIFIER()->getText();
        if (funcName == LOGOS_MAIN_FUNC) {
            mainFile->funcs[funcName] = getMainFunc(func);
        } else {
            const auto funcImpl = getFuncImpl(func);
            mainFile->funcs[funcName] = funcImpl;
            mainFile->symbolTable.addSymbol(funcImpl->funcType->name, LgsSymbol(funcImpl), &errHandler);
        }
    }

    for (const auto group : ctx->group()) {
        const auto lgsGroup = getGroup(group);
        mainFile->groups.push_back(lgsGroup);
        mainFile->symbolTable.addSymbol(lgsGroup->name, LgsSymbol(lgsGroup), &errHandler);
    }

    return mainFile;
}

LgsAppFile* AntlerConverter::getAppFile(LogosParser::LogosAppFileContext* ctx) {
    vector<LgsVarDec*> varDecs;
    for (const auto& explicitVarDec : ctx->explicitVarDec()) {
        varDecs.emplace_back(getExplicitVarDec(explicitVarDec));
    }
    for (const auto& implicitVarDec : ctx->implicitVarDec()) {
        varDecs.emplace_back(getImplicitVarDec(implicitVarDec));
    }
    const auto file = new LgsAppFile(filePath, varDecs);
    const auto requireEnvs = ctx->requireEnvVars();
    if (!requireEnvs) return file;

    vector<RequireEnvVar> requireEnvVars;
    for (int i = 0; i < requireEnvs->type().size(); ++i) {
        const auto name = requireEnvs->IDENTIFIER()[i]->getText();
        const auto type = getType(requireEnvs->type()[i]);
        const RequireEnvVar requireEnvVar{.name = name, .type = type};
        requireEnvVars.push_back(requireEnvVar);
    }
    file->requireEnvVars = requireEnvVars;
    return file;
}

LgsEnvFile* AntlerConverter::getEnvFile(LogosParser::LogosEnvFileContext* ctx) {
    vector<LgsVarDec*> varDecs;
    for (const auto& explicitVarDec : ctx->explicitVarDec()) {
        varDecs.emplace_back(getExplicitVarDec(explicitVarDec));
    }
    for (const auto& implicitVarDec : ctx->implicitVarDec()) {
        varDecs.emplace_back(getImplicitVarDec(implicitVarDec));
    }
    return new LgsEnvFile("EnvFile", filePath, varDecs);
}

LgsObject* AntlerConverter::getObject(LogosParser::ObjectBodyContext* ctx, const string& objName, const bool isSingleton) {
    const auto obj = new LgsObject(objName);
    obj->setLocation(ctx->start, ctx->stop, filePath);
    if (isNameBuiltin(obj->name, &obj->location)) return nullptr;
    obj->isSingleton = isSingleton;
    for (int i = 0; i < ctx->field().size(); ++i) {
        const auto lgsField = getField(ctx->field(i), obj->name);
        lgsField->position = i;
        obj->fields[lgsField->name] = lgsField;
    }
    for (const auto& func : ctx->methodImplementation()) {
        const auto methodName = func->funcSignature()->IDENTIFIER()->getText();
        const auto method = getMethodImpl(func, obj);
        const auto methodAdded = obj->addMethod(method);
        if (!methodAdded) {
            errHandler.handleError(E10056, &obj->location, {obj->name, methodName});
            return nullptr;
        }
    }
    if (ctx->objectImplements()) {
        for (const auto& type : ctx->objectImplements()->IDENTIFIER()) {
            auto implementType = getTypeFromText(type);
            obj->interfaces.push_back(implementType);
        }
    }
    return obj;
}

LgsInterface* AntlerConverter::getInterface(LogosParser::InterfaceBodyContext* ctx, const string& interfaceName) {
    const auto interface = new LgsInterface(interfaceName);
    interface->setLocation(ctx->start, ctx->stop, filePath);
    if (isNameBuiltin(interface->name, &interface->location)) return nullptr;
    for (const auto& funcSignature : ctx->funcSignature()) {
        const auto self = LgsParam(interface, LOGOS_SELF);
        const auto type = getFuncReturnType(funcSignature->type());
        const auto func = new LgsFunc(funcSignature->IDENTIFIER()->getText(), type);
        func->funcType->parentName = interfaceName;
        func->funcType->isMethod = true;
        func->funcType->params.push_back(self);
        setParams(func->funcType, funcSignature->param());
        interface->addMethod(func);
    }
    return interface;
}

LgsMainFunc* AntlerConverter::getMainFunc(LogosParser::FuncImplContext* ctx) {
    const auto mainFunc = new LgsMainFunc();
    const auto funcSignature = ctx->funcSignature();
    mainFunc->setLocation(funcSignature->IDENTIFIER()->getSymbol(), nullptr, filePath);
    const auto statementsBlock = ctx->funcBody()->statementsBlock();
    mainFunc->stmtBlock = getStmtBlock(statementsBlock);
    bool isValid = true;
    const auto paramSize = funcSignature->param().size();
    if (paramSize > 1) {
        isValid = false;
    } else if (paramSize == 1) {
        isValid = setMainArgsParam(mainFunc, funcSignature);
        if (isValid) mainFunc->setArgs();
    }
    if (!isValid) {
        errHandler.handleError(E10039, &mainFunc->location);
    }
    return mainFunc;
}

bool AntlerConverter::setMainArgsParam(const LgsMainFunc* mainFunc, LogosParser::FuncSignatureContext* funcSignature) {
    const auto param = funcSignature->param().front();
    const auto type = param->type();
    const auto variableName = param->IDENTIFIER()->getText();
    const auto expr = getExpr(param->expr());
    auto lgsParam = LgsParam(getType(type), variableName, expr);
    lgsParam.setLocation(param->start, param->stop, filePath);
    const auto arr = lgsParam.type->asArray();
    mainFunc->funcType->params.push_back(lgsParam);
    return arr && arr->baseType->asStr();
}

LgsFunc* AntlerConverter::getFuncImpl(LogosParser::FuncImplContext* ctx) {
    const auto rt = getFuncReturnType(ctx->funcSignature()->type());
    const auto funcSignature = ctx->funcSignature();
    const auto tokenName = funcSignature->IDENTIFIER();
    const auto func = new LgsFunc(tokenName->getText(), rt);
    func->setLocation(tokenName->getSymbol(), nullptr, filePath);
    if (isNameBuiltin(func->funcType->name, &func->location)) return nullptr;
    setParams(func->funcType, funcSignature->param());
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    return func;
}

LgsFunc* AntlerConverter::getMethodImpl(LogosParser::MethodImplementationContext* ctx, LgsObject* obj) {
    const auto rt = getFuncReturnType(ctx->funcSignature()->type());
    const auto funcSignature = ctx->funcSignature();
    const auto nameToken = funcSignature->IDENTIFIER();
    const auto method = new LgsFunc(nameToken->getText(), rt);
    method->setLocation(nameToken->getSymbol(), nullptr, filePath);
    if (isNameBuiltin(method->funcType->name, &method->location)) return nullptr;
    method->funcType->isMethod = true;
    method->funcType->parentName = obj->name;
    auto self = LgsParam(obj, LOGOS_SELF);
    self.isSelf = true;
    method->funcType->params.push_back(self);
    setParams(method->funcType, funcSignature->param());
    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    if (ctx->VISIBILITY()) {
        method->funcType->isPublic = true;
    }
    return method;
}

LgsFunc* AntlerConverter::getAnonymousFunc(LogosParser::AnonnymosFuncContext* ctx) {
    const auto rt = getFuncReturnType(ctx->anonnymosfuncSignature()->type());
    const auto funcSignature = ctx->anonnymosfuncSignature();
    const auto func = new LgsFunc("", rt);
    func->funcType->isAnonymous = true;
    setParams(func->funcType, funcSignature->param());
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setLocation(funcSignature->LPAREN()->getSymbol(), nullptr, filePath);
    return func;
}

void AntlerConverter::setParams(LgsFuncType* funcType, const vector<LogosParser::ParamContext*>& params) {
    for (int i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        if (const auto type = param->type()) {
            auto lgsParam = getParam(funcType, param, type);
            if (isNameBuiltin(lgsParam.name, &lgsParam.location)) return;
            funcType->params.push_back(lgsParam);
        } else if (const auto paramFuncType = param->funcType()) {
            const auto lgsParamFuncType = getFuncType(paramFuncType);
            lgsParamFuncType->name = param->IDENTIFIER()->getText();
            if (isNameBuiltin(lgsParamFuncType->name, &lgsParamFuncType->location)) return;
            auto lgsParam = LgsParam(lgsParamFuncType);
            lgsParam.name = lgsParamFuncType->name;
            if (isNameBuiltin(lgsParam.name, &lgsParam.location)) return;
            lgsParam.setLocation(param->start, param->stop, filePath);
            funcType->params.push_back(lgsParam);
        }
    }
    if (funcType->isVariadic && funcType->hasDefaults) {
        errHandler.handleError(E10043, &funcType->location);
    }
}

LgsParam AntlerConverter::getParam(LgsFuncType* funcType, LogosParser::ParamContext* param, LogosParser::TypeContext* type) {
    const auto variableName = param->IDENTIFIER()->getText();
    const auto expr = getExpr(param->expr());
    auto lgsParam = LgsParam(getType(type), variableName, expr);
    lgsParam.setLocation(param->start, param->stop, filePath);
    if (param->TRIPLE_DOT()) {
        if (lgsParam.expr) errHandler.handleError(E10045, &lgsParam.location);
        lgsParam.isVariadic = true;
        funcType->isVariadic = true;
    } else if (lgsParam.expr) {
        funcType->hasDefaults = true;
    }
    return lgsParam;
}

LgsField* AntlerConverter::getField(LogosParser::FieldContext* ctx, string& parentName) {
    const auto name = ctx->IDENTIFIER()->getText();
    const auto type = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto field = new LgsField(name, &parentName, type, expr);
    field->isPublic = !!ctx->VISIBILITY();
    field->isMutable = ctx->CONST() == nullptr;
    field->setLocation(ctx->start, ctx->stop, filePath);
    return field;
}

LgsStmtBlock* AntlerConverter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    const auto stmtBlock = new LgsStmtBlock();
    if (!ctx) return stmtBlock;
    for (const auto& statement : ctx->statement()) {
        auto stmt = getStmt(statement);
        stmtBlock->stmts.emplace_back(stmt);
    }
    return stmtBlock;
}

LgsStmt* AntlerConverter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto fieldDef = ctx->assignment()) return getAssignment(fieldDef);
    if (const auto implicitVarDec = ctx->implicitVarDec()) return getImplicitVarDec(implicitVarDec);
    if (const auto explicitVarDec = ctx->explicitVarDec()) return getExplicitVarDec(explicitVarDec);
    if (const auto ifStmt = ctx->ifStatement()) return getIfStatement(ifStmt);
    if (const auto patternMatching = ctx->patternMatching()) return getPatternMatching(patternMatching);
    if (const auto loopStmt = ctx->loopStatement()) return getLoopStatement(loopStmt);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (const auto returnStmt = ctx->returnStatement()) return getReturnStmt(returnStmt);
    if (const auto postfixExpr = ctx->postfixExpr()) return getPostfixExpr(postfixExpr);
    if (ctx->breakStmt()) return getBreakStmt(ctx);
    if (ctx->CONTINUE()) return new LgsContinueStmt();
    assert(0);
}

LgsAssignment* AntlerConverter::getAssignment(LogosParser::AssignmentContext* ctx) {
    LgsExpr* lValue = nullptr;
    if (const auto variable = ctx->IDENTIFIER()) {
        lValue = getVariable(variable);
    } else if (const auto iterIndex = ctx->iterIndex()) {
        lValue = getIterIndex(iterIndex);
    } else if (const auto selection = ctx->selection()) {
        lValue = getSelection(selection);
    } else {
        assert(0);
    }
    const auto assignment = new LgsAssignment(mapAssignType(ctx), lValue, getExpr(ctx->expr()));
    assignment->setLocation(ctx->start, ctx->stop, filePath);
    return assignment;
}

LgsVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->IDENTIFIER()->getText();
    const auto varDec = new LgsVarDec(variableName);
    varDec->setLocation(ctx->start, ctx->stop, filePath);
    if (isNameBuiltin(varDec->name, &varDec->location)) return nullptr;
    varDec->expr = getExpr(ctx->expr());
    varDec->isNullable = !!ctx->QUEST_MARK();
    varDec->isMutable = !ctx->CONST();
    return varDec;
}

LgsVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->IDENTIFIER()->getText();
    const auto varDec = new LgsVarDec(variableName);
    varDec->setLocation(ctx->start, ctx->stop, filePath);
    if (isNameBuiltin(varDec->name, &varDec->location)) return nullptr;
    varDec->isMutable = !ctx->CONST();
    if (ctx->expr()) {
        varDec->expr = getExpr(ctx->expr());
    }
    varDec->type = getType(ctx->type());
    return varDec;
}

LgsStmt* AntlerConverter::getReturnStmt(LogosParser::ReturnStatementContext* ctx) {
    const auto rs = new LgsReturn(getExpr(ctx->expr()));
    rs->setLocation(ctx->start, ctx->stop, filePath);
    return rs;
}

LgsFuncType* AntlerConverter::getFuncType(LogosParser::FuncTypeContext* ctx) {
    const auto rt = getType(ctx->rt);
    const auto funcType = new LgsFuncType();
    funcType->setLocation(ctx->start, ctx->stop, filePath);
    funcType->rt = rt;
    for (const auto paramType : ctx->type()) {
        if (paramType == ctx->rt) continue;
        const auto type = getType(paramType);
        funcType->params.emplace_back(LgsParam(type));
    }
    return funcType;
}

LgsIfStmt* AntlerConverter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto ifStmt = new LgsIfStmt(expr, stmts);
    if (const auto tag = ctx->TAG()) {
        ifStmt->tag = tag->getText().substr(1);
    }
    for (const auto &elseIfStmt : ctx->elseIfStatement()) {
        auto elseIfExpr = getExpr(elseIfStmt->expr());
        auto elseIfStmtBlock = getStmtBlock(elseIfStmt->statementsBlock());
        ifStmt->elseIfConds.emplace_back(elseIfExpr);
        ifStmt->elseIfStmtBlocks.emplace_back(elseIfStmtBlock);
    }
    if (const auto &elseStmt = ctx->elseStatement()) {
        ifStmt->elseStmtBlock = getStmtBlock(elseStmt->statementsBlock());
    }
    ifStmt->setLocation(ctx->start, ctx->stop, filePath);
    return ifStmt;
}

LgsBreakStmt* AntlerConverter::getBreakStmt(LogosParser::StatementContext* ctx) const {
    const auto tag = ctx->breakStmt()->TAG();
    if (tag) return new LgsBreakStmt(tag->getText().substr(1));
    return new LgsBreakStmt();
}

LgsStmt* AntlerConverter::getPatternMatching(LogosParser::PatternMatchingContext* ctx) {
    const auto patternMatching = new LgsPatternMatch(getExpr(ctx->expr()));
    for (const auto& pattern : ctx->pattern()) {
        const auto expr = getExpr(pattern->expr());
        const auto stmtBlock = getStmtBlock(pattern->statementsBlock());
        patternMatching->patterns.emplace_back(expr);
        patternMatching->patternsStmtBlocks.emplace_back(stmtBlock);
    }
    patternMatching->elseStmtBlock = getStmtBlock(ctx->statementsBlock());
    return patternMatching;
}

LgsForLoop* AntlerConverter::getLoopStatement(LogosParser::LoopStatementContext* ctx) {
    LgsForLoop* loopStmt = nullptr;
    if (ctx->iterableExpr) {
        loopStmt = getForeachLoop(ctx);
    } else if (ctx->iterableRange) {
        loopStmt = getRangeLoop(ctx);
    } else {
        loopStmt = getInfiniteLoop(ctx);
    }
    loopStmt->stmtBlock = getStmtBlock(ctx->statementsBlock());
    loopStmt->setLocation(ctx->start, ctx->stop, filePath);
    return loopStmt;
}

LgsForLoop* AntlerConverter::getRangeLoop(LogosParser::LoopStatementContext* ctx) {
    auto startExpr = getExpr(ctx->iterableRange->start);
    if (!startExpr) {
        startExpr = LGS_INT.getZeroValue();
    }
    const auto endExpr = getExpr(ctx->iterableRange->end);
    const auto rangeLoop = new LgsRangeLoop(startExpr, endExpr);
    const auto loopVarToken = ctx->IDENTIFIER().front();
    const auto loopVarName = loopVarToken->getText();
    auto varDec = new LgsVarDec(loopVarName);
    varDec->setLocation(loopVarToken->getSymbol(), nullptr, filePath);
    if (isNameBuiltin(varDec->name, &varDec->location)) return nullptr;
    varDec->type = &LGS_INT;
    varDec->expr = LGS_INT.getZeroValue();
    varDec->expr->location = varDec->location;
    rangeLoop->loopVars.emplace_back(varDec);
    return rangeLoop;
}

LgsForLoop* AntlerConverter::getForeachLoop(LogosParser::LoopStatementContext* ctx) {
    const auto iterExpr = getUnaryExpr(ctx->iterableExpr);
    const auto foreachLoop = new LgsForeachLoop(iterExpr);
    for (const auto variable : ctx->IDENTIFIER()) {
        const auto loopVarName = variable->getText();
        auto varDec = new LgsVarDec(loopVarName);
        varDec->setLocation(variable->getSymbol(), nullptr, filePath);
        if (isNameBuiltin(varDec->name, &varDec->location)) return nullptr;
        foreachLoop->loopVars.emplace_back(varDec);
    }
    return foreachLoop;
}

LgsForLoop* AntlerConverter::getInfiniteLoop(LogosParser::LoopStatementContext* ctx) {
    const auto rangeLoop = new LgsInfiniteLoop();
    if (!ctx->IDENTIFIER().empty()) {
        const auto idToken = ctx->IDENTIFIER()[0];
        const auto loopVarName = idToken->getText();
        auto varDec = new LgsVarDec(loopVarName);
        varDec->setLocation(idToken->getSymbol(), nullptr, filePath);
        if (isNameBuiltin(varDec->name, &varDec->location)) return nullptr;
        varDec->type = &LGS_INT;
        varDec->expr = LGS_INT.getZeroValue();
        rangeLoop->loopVars.emplace_back(varDec);
    }
    return rangeLoop;
}

LgsEnum* AntlerConverter::getEnum(LogosParser::EnumDeclarationContext* ctx) {
    const auto lgsEnum = new LgsEnum(ctx->IDENTIFIER()->getText());
    lgsEnum->setLocation(ctx->start, ctx->stop, filePath);
    unordered_set<string> seenNames;
    for (size_t i = 0; i < ctx->enumField().size(); ++i) {
        const auto enumField = ctx->enumField()[i];
        const auto enumName = enumField->IDENTIFIER()->getText();
        if (!seenNames.insert(enumName).second) {
            errHandler.handleError(E10011, &lgsEnum->location, {enumName, to_string(lgsEnum->location.lineNumberStart)});
            break;
        }
        string enumText = "";
        if (enumField->STRING()) {
            enumText = enumField->STRING()->getText();
            cleanStr(enumText);
        }
        const auto field = new LgsEnumField(lgsEnum, enumName, enumText);
        field->setLocation(ctx->start, ctx->stop, filePath);
        lgsEnum->fields[enumName] = new LgsField(field->name, &lgsEnum->name, lgsEnum, field);
    }
    return lgsEnum;
}

LgsExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    LgsExpr* expr = nullptr;
    if (ctx->cast) {
        expr = getCast(ctx);
    } else if (ctx->LPAREN() && ctx->RPAREN()) {
        expr = getExpr(ctx->left);
    }  else if (const auto unary = ctx->unaryExpr()) {
        expr = getUnaryExpr(unary);
    } else if (ctx->right){
        expr = getBinaryExpr(ctx);
    }
    return expr;
}

LgsExpr* AntlerConverter::getCast(LogosParser::ExprContext* ctx) {
    LgsExpr* castFromValue;
    if (const auto unary = ctx->unaryExpr()) {
        castFromValue = getUnaryExpr(unary);
    } else {
        castFromValue = getBinaryExpr(ctx);
    }
    LgsType* castToType = getType(ctx->cast);
    return new LgsCast(castToType, castFromValue);
}

LgsUnaryExpr* AntlerConverter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->IDENTIFIER()) return getVariable(variable);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto prefixExpr = ctx->prefixExpr()) return getPrefixExpr(prefixExpr);
    if (const auto postfixExpr = ctx->postfixExpr()) return getPostfixExpr(postfixExpr);
    if (const auto constructor = ctx->constructor()) return getInstance(constructor);
    if (const auto constant = ctx->constant()) return getConstant(constant);
    if (const auto array = ctx->arrayExpr()) return getArrayExpr(array);
    if (const auto hashMap = ctx->hashMap()) return getHashMap(hashMap);
    if (const auto iterIndex = ctx->iterIndex()) return getIterIndex(iterIndex);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (const auto func = ctx->anonnymosFunc()) return getAnonymousFunc(func);
    if (const auto vector = ctx->vector()) return getVector(vector);
    if (const auto null = ctx->NULL_()) return getNullValue(null);
    assert(0);
}

LgsExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LgsBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->opStr = ctx->getText();
    logosBinaryExpr->setLocation(ctx->start, ctx->stop, filePath);
    return logosBinaryExpr;
}

LgsUnaryExpr* AntlerConverter::getPrefixExpr(LogosParser::PrefixExprContext* ctx) {
    LgsPrefixOperator op;
    if (ctx->NOT()) {
        op = NOT_PREFIX;
    } else if (ctx->MINUS()) {
        op = MINUS_PREFIX;
    } else {
        assert(0);
    }
    const auto expr = getExpr(ctx->expr());
    const auto prefixExpr = new LgsPrefixExpr(expr, op);
    prefixExpr->setLocation(ctx->start, ctx->stop, filePath);
    return prefixExpr;
}

LgsPostfixExpr* AntlerConverter::getPostfixExpr(LogosParser::PostfixExprContext* ctx) {
    LgsPostfixOperator op;
    if (ctx->INC()) {
        op = INC;
    } else if (ctx->DEC()) {
        op = DEC;
    } else {
        assert(0);
    }
    LgsUnaryExpr* expr = nullptr;
    if (const auto var = ctx->IDENTIFIER()) {
        expr = getVariable(var);
    } else if (const auto selection = ctx->selection()) {
        expr = getSelection(selection);
    } else if (const auto iterIndex = ctx->iterIndex()) {
        expr = getIterIndex(iterIndex);
    } else if (const auto funcCall = ctx->funcCall()) {
        expr = getFuncCall(funcCall);
    } else {
        assert(0);
    }
    const auto postfixExpr = new LgsPostfixExpr(expr, op);
    postfixExpr->setLocation(ctx->start, ctx->stop, filePath);
    return postfixExpr;
}

LgsUnaryExpr* AntlerConverter::getArrayExpr(LogosParser::ArrayExprContext* ctx) {
    const auto array = new LgsArrayExpr();
    const auto arrType = array->type->asArray();
    arrType->isStatic = !!ctx->EXCLA_MARK();
    arrType->iterLen = ctx->expr().size();
    arrType->sizeExpr = new LgsIntConst(arrType->iterLen);
    for (const auto expr : ctx->expr()) {
        array->elements.emplace_back(getExpr(expr));
    }
    array->setLocation(ctx->start, ctx->stop, filePath);
    return array;
}

LgsUnaryExpr* AntlerConverter::getHashMap(LogosParser::HashMapContext* ctx) {
    const auto hashMap = new LgsHashMap();
    for (const auto keyValue : ctx->keyValue()) {
        const auto kExpr = getExpr(keyValue->key);
        const auto vExpr = getExpr(keyValue->value);
        const auto mapEntry = new LgsMapEntry(kExpr, vExpr);
        hashMap->initialElements.emplace_back(mapEntry);
    }
    return hashMap;
}

LgsVariable* AntlerConverter::getVariable(tree::TerminalNode* ctx) const {
    const auto variable = new LgsVariable(ctx->getText());
    variable->setLocation(ctx->getSymbol(), nullptr, filePath);
    return variable;
}

LgsFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->IDENTIFIER()->getText();
    vector<LgsExpr*> args;
    if (ctx->funcArgList()) {
        for (const auto& arg : ctx->funcArgList()->funcArg()) {
            auto argExpr = getExpr(arg->expr());
            args.push_back(argExpr);
        }
    }
    if (!args.empty() && ctx->TRIPLE_DOT()) {
        args[args.size() - 1]->isSpread = true;
    }
    const auto funcCall = new LgsFuncCall(name, args);
    funcCall->setLocation(ctx->start, ctx->stop, filePath);
    return funcCall;
}

LgsUnaryExpr* AntlerConverter::getVector(LogosParser::VectorContext* vector) const {
    if (vector->VEC2()) {

    } else if (vector->VEC3()) {

    } else if (vector->VEC4()) {

    }
    assert(0);
}

LgsInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto instance = new LgsInstance(ctx->IDENTIFIER()->getText());
    instance->setLocation(ctx->start, ctx->stop, filePath);
    const auto args = ctx->constructorArgList();
    if (!args) return instance;
    unordered_set<string> initializedArgs;
    for (const auto& arg : args->constructorArg()) {
        const auto argExpr = getExpr(arg->expr());
        const auto idToken = arg->IDENTIFIER();
        const auto varDec = new LgsVarDec(idToken->getText(), argExpr);
        varDec->setLocation(arg->start, arg->stop, filePath);
        if (isNameBuiltin(varDec->name, &varDec->location)) return instance;
        if (isArgsDuplicate(initializedArgs, varDec)) return instance;
        initializedArgs.insert(varDec->name);
        instance->args[varDec->name] = varDec;
    }
    return instance;
}

LgsIterIndex* AntlerConverter::getIterIndex(LogosParser::IterIndexContext* ctx) {
    LgsUnaryExpr* baseExpr;
    if (const auto variable = ctx->IDENTIFIER()) {
        baseExpr = getVariable(variable);
    } else if (const auto funcCall = ctx->funcCall()) {
        baseExpr = getFuncCall(funcCall);
    } else {
        assert(0);
    }

    for (int i = 0; i < ctx->index().size(); ++i) {
        const auto indexExpr = ctx->index()[i];
        const auto indexExprFrom = indexExpr->from;
        const auto iterIndexFrom = getExpr(indexExprFrom);
        const auto iterIndexTo = getExpr(indexExpr->to);
        const auto index = new LgsIndex{.from = iterIndexFrom, .to = iterIndexTo};
        const auto newIterIndex = new LgsIterIndex(baseExpr, index);
        newIterIndex->setLocation(ctx->start, ctx->stop, filePath);
        baseExpr = newIterIndex;
    }

    return baseExpr->asIterIndex();
}

LgsSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    const auto exprs = getSelectionExprs(ctx);
    const auto selection = new LgsSelection(exprs);
    selection->setLocation(ctx->start, ctx->stop, filePath);
    return selection;
}

vector<LgsUnaryExpr*> AntlerConverter::getSelectionExprs(LogosParser::SelectionContext* ctx) {
    vector exprs = {getFirstSelection(ctx)};
    const auto innerSelections = ctx->innerSelectionElement();
    for (int i = 0; i < innerSelections.size(); ++i) {
        const auto& currentExpr = innerSelections[i];
        if (const auto field = currentExpr->IDENTIFIER()) {
            const auto logosField = getVariable(field);
            exprs.push_back(logosField);
        } else if (const auto funcCall = currentExpr->funcCall()) {
            const auto logosMethodCall = getFuncCall(funcCall);
            // First inner expr takes firstExpr as parent
            const auto prevExpr = exprs[i];
            logosMethodCall->args.insert(logosMethodCall->args.begin(), prevExpr);
            exprs.push_back(logosMethodCall);
        } else if (const auto iterIndex = currentExpr->iterIndex()) {
            const auto logosIterIndex = getIterIndex(iterIndex);
            exprs.push_back(logosIterIndex);
        }
    }
    return exprs;
}

LgsUnaryExpr* AntlerConverter::getFirstSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = ctx->firstSelectionElement();
    if (const auto variable = firstExpr->IDENTIFIER()) {
        return getVariable(variable);
    }
    if (const auto funcCall = firstExpr->funcCall()) {
        return getFuncCall(funcCall);
    }
    if (const auto iterIndex = firstExpr->iterIndex()) {
        return getIterIndex(iterIndex);
    }
    if (const auto selfInstance = firstExpr->SELF_INSTANCE()) {
        return getVariable(selfInstance);
    }
    if (const auto selfClass = firstExpr->SELF_CLASS()) {
        return getTypeConstant(selfClass);
    }
    if (const auto type = firstExpr->STRING()) {
        return getStrConst(type);
    }
    assert(0);
}

LgsUnaryExpr* AntlerConverter::getConstant(LogosParser::ConstantContext* ctx) const {
    LgsUnaryExpr* constant = nullptr;
    if (const auto intToken = ctx->INTEGER()) {
        const auto input = removeUnderscores(intToken->getText());
        char* end;
        const auto longValue = std::strtol(input.c_str(), &end, 10);
        if (longValue >= INT_MIN && longValue <= INT_MAX) {
            const auto intValue = static_cast<int>(longValue);
            constant = new LgsIntConst(intValue);
        } else {
            constant = new LgsLongConst(longValue);
        }
    } else if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        constant = new LgsFloatConst(value);
    } else if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == LgsBool::trueLiteral;
        constant = new LgsBoolConst(value);
    } else if (const auto stringToken = ctx->STRING()) {
        const auto value = stringToken->getText();
        if (value.size() == 1) {
            constant = new LgsCharConst(value[0]);
        } else {
            constant = getStrConst(stringToken);
        }
    }
    constant->setLocation(ctx->start, ctx->stop, filePath);
    return constant;
}

LgsStrConst* AntlerConverter::getStrConst(tree::TerminalNode* type) const {
    auto typeText = type->getText();
    cleanStr(typeText);
    const auto strConst = new LgsStrConst(typeText);
    strConst->setLocation(type->getSymbol(), nullptr, filePath);
    return strConst;
}

LgsTypeConst* AntlerConverter::getTypeConstant(tree::TerminalNode* ctx) const {
    const auto typeConst = new LgsTypeConst(getTypeFromText(ctx));
    typeConst->setLocation(ctx->getSymbol(), nullptr, filePath);
    return typeConst;
}

LgsUnaryExpr* AntlerConverter::getNullValue(const tree::TerminalNode* ctx) const {
    const auto lgsNull = new LgsNullValue();
    lgsNull->setLocation(ctx->getSymbol(), nullptr, filePath);
    return lgsNull;
}

LgsType* AntlerConverter::getType(LogosParser::TypeContext* ctx) {
    if (!ctx) return nullptr;
    LgsType* result = nullptr;
    if (const auto mapType = ctx->mapType()) {
        result = new LgsMap(getType(mapType->key), getType(mapType->value));
    } else if (!ctx->arraySize().empty()) {
        result = getArrayType(ctx);
    } else if (const auto funcType = ctx->funcType()) {
        result = getFuncType(funcType);
    } else {
        result = getTypeFromText(ctx->IDENTIFIER());
        if (ctx->QUEST_MARK()) {
            result = new LgsNullable(result);
        }
    }
    result->setLocation(ctx->start, ctx->stop, filePath);
    return result;
}

LgsGroup* AntlerConverter::getGroup(LogosParser::GroupContext* ctx) {
    const auto group = new LgsGroup(ctx->IDENTIFIER()->getText());
    group->setLocation(ctx->start, ctx->stop, filePath);
    for (const auto type : ctx->groupTypesList()->type()) {
        const auto lgsType = getType(type);
        group->types.push_back(lgsType);
    }
    for (const auto target : ctx->groupTargetList()->IDENTIFIER()) {
        const auto var = getVariable(target);
        group->targetSymbols.push_back(var);
    }
    globals.addSymbol(group->name, LgsSymbol(group), &errHandler);
    return group;
}

LgsType* AntlerConverter::getArrayType(LogosParser::TypeContext* ctx) {
    LgsType* type = getType(ctx->baseType);
    auto dims = ctx->arraySize();
    for (auto it = dims.rbegin(); it != dims.rend(); ++it) {
        const auto array = new LgsArray(type);
        array->isStatic = !!ctx->EXCLA_MARK();
        if (const auto sizeExpr = (*it)->expr()) {
            array->sizeExpr = getExpr(sizeExpr);
        }
        type = array;
    }
    return type;
}

LgsType* AntlerConverter::getFuncReturnType(LogosParser::TypeContext* ctx) {
    LgsType* result = nullptr;
    if (!ctx) {
        result = &LGS_VOID;
    } else {
        result = getType(ctx);
        result->setLocation(ctx->start, ctx->stop, filePath);
    }
    return result;
}

LgsType* AntlerConverter::getTypeFromText(tree::TerminalNode* typeToken) const {
    const auto typeText = typeToken->getText();
    LgsType* type = nullptr;
    if (typeText == LgsBool::name) {
        type = &LGS_BOOL;
    } else if (typeText == LgsChar::name) {
        type = &LGS_CHAR;
    } else if (typeText == LgsInt::name) {
        type = &LGS_INT;
    } else if (typeText == LgsUInt::name) {
        type = &LGS_UINT;
    } else if (typeText == LgsShort::name) {
        type = &LGS_SHORT;
    } else if (typeText == LgsLong::name) {
        type = &LGS_LONG;
    } else if (typeText == LgsSize::name) {
        type = &LGS_SIZE;
    } else if (typeText == LgsFloat::name) {
        type = &LGS_FLOAT;
    } else if (typeText == LgsVoid::name) {
        type = &LGS_VOID;
    } else if (typeText == LgsStr::name) {
        type = new LgsStr();
    } else {
        type = new LgsUnknownType(typeText);
    }
    type->setLocation(typeToken->getSymbol(), nullptr, filePath);
    return type;
}

LgsAssignType AntlerConverter::mapAssignType(LogosParser::AssignmentContext* assignment) const {
    const auto op = assignment->assignemntOp();
    if (op->WALRUS()) return ASSIGN;
    if (op->EQUAL_PLUS()) return ASSIGN_ADD;
    if (op->EQUAL_MINUS()) return ASSIGN_SUB;
    if (op->EQUAL_STAR()) return ASSIGN_MUL;
    if (op->EQUAL_SLASH()) return ASSIGN_DIV;
    if (op->EQUAL_PERCENT()) return ASSIGN_MOD;
    if (op->EQUAL_DOUBLE_LANGLE()) return ASSIGN_LSHIFT;
    if (op->EQUAL_DOUBLE_RANGLE()) return ASSIGN_RSHIFT;
    if (op->EQUAL_AMPERSAND()) return ASSIGN_AND;
    if (op->EQUAL_PIPE()) return ASSIGN_OR;
    if (op->EQUAL_CARET()) return ASSIGN_XOR;
    assert(false);
}

LgsOperator AntlerConverter::mapOperator(LogosParser::ExprContext* expr) const {
    if (expr->PLUS()) return ADD;
    if (expr->MINUS()) return SUB;
    if (expr->STAR()) return MUL;
    if (expr->SLASH()) return DIV;
    if (expr->PERCENT()) return MOD;
    if (expr->NOT_EQUAL()) return NE;
    if (expr->DOUBLE_EQUAL()) return EQ;
    if (expr->RANGLE()) return GT;
    if (expr->LANGLE()) return LT;
    if (expr->GE()) return GE;
    if (expr->LE()) return LE;
    if (expr->AND()) return AND;
    if (expr->OR()) return OR;
    if (expr->AMPERSAND()) return BIT_AND;
    if (expr->PIPE()) return BIT_OR;
    if (expr->DOUBLE_LANGLE()) return LSHIFT;
    if (expr->DOUBLE_RANGLE()) return RSHIFT;
    if (expr->CARET()) return BIT_XOR;
    assert(false);
}

bool AntlerConverter::isNameBuiltin(const string& name, const Location* location) {
    const auto isLgsBuiltin = name == LgsSizeOf::name || name == LgsPrint::name;
    if (isLgsBuiltin) {
        errHandler.handleError(E10053, location, {name});
        return true;
    }
    return false;
}

bool AntlerConverter::isArgsDuplicate(const unordered_set<string>& initializedArgs, const LgsVarDec* varDec) {
    if (initializedArgs.count(varDec->name)) {
        errHandler.handleError(E10054, &varDec->location, {varDec->name});
        return true;
    }
    return false;
}

void AntlerConverter::cleanStr(string& value) const {
    value.erase(0, 1);
    value.pop_back();
}
