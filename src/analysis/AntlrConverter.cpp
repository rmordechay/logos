#include "analysis/AntlrConverter.h"

#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include "files/LgsInterfaceFile.h"
#include "LogosLexer.h"

#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsOperator.h"
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
#include "exprs/unary/LgsEnumField.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/constants/LgsLongConst.h"
#include "extern/LgsCLang.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/Platform.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsArray.h"
#include "types/LgsGroup.h"
#include "types/LgsMap.h"
#include "types/LgsUnknownType.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "utils/LgsUtils.h"


#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <types/LgsStr.h>
#include <types/primitives/LgsVoid.h>

LgsFile* AntlerConverter::getLogosFile(LogosParser::LogosFileContext* ctx, const path& filePath) {
    this->filePath = filePath;
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
    if (!file->externFiles.empty()) {
        const LgsCLang lgsClang;
        lgsClang.parse(*file, errHandler);
    }
    file->absPath = filePath;
    file->relPath = relative(filePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
    return file;
}

LgsObjectFile* AntlerConverter::getObjectFile(LogosParser::ObjectFileContext* ctx) {
    const auto objName = ctx->objectDeclaration()->TYPE()->getText();
    const auto objFile = new LgsObjectFile(objName, filePath);
    objFile->obj = getObject(ctx->objectBody(), objName, !!ctx->objectDeclaration()->SINGLETON());
    return objFile;
}

LgsFile* AntlerConverter::getInterfaceFile(LogosParser::InterfaceFileContext* ctx) {
    const auto interfaceName = ctx->interfaceDeclaration()->TYPE()->getText();
    const auto interfaceFile = new LgsInterfaceFile(interfaceName, filePath);
    interfaceFile->interface = getInterface(ctx->interfaceBody(), interfaceName);
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
        auto lgsObject = getObject(object->objectBody(), object->TYPE()->getText(), !!object->SINGLETON());
        mainFile->objects.emplace_back(lgsObject);
    }

    for (const auto interface : ctx->interface()) {
        auto lgsInterface = getInterface(interface->interfaceBody(), interface->TYPE()->getText());
        mainFile->interfaces.push_back(lgsInterface);
    }

    for (const auto func : funcImplementations) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        if (funcName == LOGOS_MAIN_FUNC) {
            mainFile->funcs[funcName] = getMainFunc(func);
        } else {
            mainFile->funcs[funcName] = getFuncImpl(func);
        }
    }

    for (const auto group : ctx->group()) {
        const auto lgsGroup = getGroup(group);
        mainFile->groups.push_back(lgsGroup);
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
        const auto name = requireEnvs->VARIABLE()[i]->getText();
        const auto type = getType(requireEnvs->type()[i]);
        const RequireEnvVar requireEnvVar{.name = name, .type = type};
        requireEnvVars.push_back(requireEnvVar);
    }
    file->requireEnvVars = requireEnvVars;
    file->relPath = relative(filePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
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
    const auto file = new LgsEnvFile(filePath, varDecs);
    file->relPath = relative(filePath, paths.rootDir).lexically_relative(LOGOS_SRC_DIR);
    return file;
}

LgsObject* AntlerConverter::getObject(LogosParser::ObjectBodyContext* ctx, const string& objName, const bool isSingleton) {
    const auto obj = new LgsObject(objName, filePath);
    obj->setLocation(ctx->start);
    obj->isSingleton = isSingleton;
    for (int i = 0; i < ctx->field().size(); ++i) {
        const auto field = ctx->field(i);
        const auto lgsField = getField(field);
        obj->fields[lgsField->name] = lgsField;
    }
    for (const auto& func : ctx->methodImplementation()) {
        auto funcName = func->funcSignature()->VARIABLE()->getText();
        const auto method = getMethodImpl(func, obj);
        obj->addMethod(method);
    }
    if (ctx->objectImplements()) {
        for (const auto& type : ctx->objectImplements()->TYPE()) {
            auto implementType = getTypeFromText(type);
            obj->interfaces.push_back(implementType);
        }
    }
    globals.addSymbol(obj->name, LgsSymbol(obj), &errHandler);
    return obj;
}

LgsInterface* AntlerConverter::getInterface(LogosParser::InterfaceBodyContext* ctx, const string& interfaceName) {
    const auto interface = new LgsInterface(interfaceName);
    interface->setLocation(ctx->start);
    for (const auto& funcSignature : ctx->funcSignature()) {
        const auto self = LgsParam(interface, LOGOS_SELF);
        const auto type = getFuncReturnType(funcSignature->type());
        const auto func = new LgsFunc(funcSignature->VARIABLE()->getText(), type);
        func->funcType.parentName = interfaceName;
        func->funcType.isMethod = true;
        func->funcType.params.push_back(self);
        setParams(&func->funcType, funcSignature->param());
        func->filePath = filePath;
        interface->addMethod(func);
    }
    globals.addSymbol(interface->interfaceName, LgsSymbol(interface), &errHandler);
    return interface;
}

LgsMainFunc* AntlerConverter::getMainFunc(LogosParser::FuncImplContext* ctx) {
    const auto mainFunc = new LgsMainFunc();
    const auto funcSignature = ctx->funcSignature();
    mainFunc->setLocation(funcSignature->VARIABLE()->getSymbol());
    const auto statementsBlock = ctx->funcBody()->statementsBlock();
    mainFunc->stmtBlock = getStmtBlock(statementsBlock);
    bool isValid = true;
    const auto paramSize = funcSignature->param().size();
    if (paramSize > 1) {
        isValid = false;
    } else if (paramSize == 1) {
        isValid = setMainArgsParam(mainFunc, funcSignature);
        if (isValid) {
            mainFunc->args = new LgsArrayExpr(new LgsStr());
            mainFunc->initArgsFunc = new LgsFunc("initArgs", &LGS_VOID, {
                LgsParam(mainFunc->args->type),
                LgsParam(&LGS_INT),
                LgsParam(new LgsStr())
            });
        }
    }
    if (!isValid) {
        errHandler.handleError(E10039, &mainFunc->location);
    }
    return mainFunc;
}

bool AntlerConverter::setMainArgsParam(LgsMainFunc* mainFunc, LogosParser::FuncSignatureContext* funcSignature) {
    const auto param = funcSignature->param().front();
    const auto type = param->type();
    const auto variableName = param->VARIABLE()->getText();
    const auto expr = getExpr(param->expr());
    auto lgsParam = LgsParam(getType(type), variableName, expr);
    lgsParam.setLocation(param->start);
    const auto arr = lgsParam.type->asArray();
    mainFunc->funcType.params.emplace_back(lgsParam);
    return arr && arr->baseType->asStr();
}

LgsFunc* AntlerConverter::getFuncImpl(LogosParser::FuncImplContext* ctx) {
    const auto rt = getFuncReturnType(ctx->funcSignature()->type());
    const auto funcSignature = ctx->funcSignature();
    const auto tokenName = funcSignature->VARIABLE();
    const auto func = new LgsFunc(tokenName->getText(), rt);
    setParams(&func->funcType, funcSignature->param());
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setLocation(tokenName->getSymbol());
    globals.addSymbol(func->funcType.name, LgsSymbol(func), &errHandler);
    return func;
}

LgsFunc* AntlerConverter::getMethodImpl(LogosParser::MethodImplementationContext* ctx, LgsObject* obj) {
    const auto rt = getFuncReturnType(ctx->funcSignature()->type());
    const auto funcSignature = ctx->funcSignature();
    const auto nameToken = funcSignature->VARIABLE();
    auto self = LgsParam(obj, LOGOS_SELF);
    self.isSelf = true;
    const auto method = new LgsFunc(nameToken->getText(), rt);
    method->filePath = obj->path;
    method->funcType.isMethod = true;
    method->funcType.parentName = obj->name;
    method->funcType.params.emplace_back(self);
    setParams(&method->funcType, funcSignature->param());
    if (ctx->VISIBILITY()) {
        method->funcType.isPublic = true;
    }
    method->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    method->setLocation(nameToken->getSymbol());
    return method;
}

LgsFunc* AntlerConverter::getAnonymousFunc(LogosParser::AnonnymosFuncContext* ctx) {
    const auto rt = getFuncReturnType(ctx->anonnymosfuncSignature()->type());
    const auto funcSignature = ctx->anonnymosfuncSignature();
    const auto func = new LgsFunc("", rt);
    func->funcType.isAnonymous = true;
    setParams(&func->funcType, funcSignature->param());
    func->stmtBlock = getStmtBlock(ctx->funcBody()->statementsBlock());
    func->setLocation(funcSignature->LPAREN()->getSymbol());
    return func;
}

void AntlerConverter::setParams(LgsFuncType* funcType, const vector<LogosParser::ParamContext*>& params) {
    for (int i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        if (const auto type = param->type()) {
            auto lgsParam = getParam(funcType, param, type);
            funcType->params.emplace_back(lgsParam);
        } else if (const auto paramFuncType = param->funcType()) {
            const auto lgsParamFuncType = getFuncType(paramFuncType);
            lgsParamFuncType->name = param->VARIABLE()->getText();
            auto lgsParam = LgsParam(lgsParamFuncType);
            lgsParam.name = lgsParamFuncType->name;
            lgsParam.setLocation(param->start);
            funcType->params.emplace_back(lgsParam);
        }
    }
    if (funcType->isVariadic && funcType->hasDefaultParams) {
        errHandler.handleError(E10043, &funcType->location);
    }
}

LgsParam AntlerConverter::getParam(LgsFuncType* funcType, LogosParser::ParamContext* param, LogosParser::TypeContext* type) {
    const auto variableName = param->VARIABLE()->getText();
    const auto expr = getExpr(param->expr());
    auto lgsParam = LgsParam(getType(type), variableName, expr);
    if (param->TRIPLE_DOT()) {
        if (lgsParam.expr) errHandler.handleError(E10045, &lgsParam.location);
        lgsParam.isVariadic = true;
        funcType->isVariadic = true;
    } else if (lgsParam.expr) {
        funcType->hasDefaultParams = true;
    }
    lgsParam.setLocation(param->start);
    return lgsParam;
}

LgsField* AntlerConverter::getField(LogosParser::FieldContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    const auto type = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto field = new LgsField(name, type, expr);
    if (ctx->VISIBILITY()) {
        field->isPublic = true;
    }
    if (ctx->CONST()) {
        field->isConst = true;
    }
    field->setLocation(ctx->start);
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
    if (ctx->breakStmt()) return getBreakStmt(ctx);
    if (ctx->CONTINUE()) return new LgsContinueStmt();
    return nullptr;
}

LgsAssignment* AntlerConverter::getAssignment(LogosParser::AssignmentContext* ctx) {
    const auto assignment = new LgsAssignment();
    assignment->rValue = getExpr(ctx->expr());

    if (const auto variable = ctx->VARIABLE()) {
        assignment->lValue = getVariable(variable->getText(), ctx);
    } else if (const auto iterIndex = ctx->iterIndex()) {
        assignment->lValue = getIterIndex(iterIndex);
    } else if (const auto selection = ctx->selection()) {
        assignment->lValue = getSelection(selection);
    } else {
        assert(0);
    }

    assignment->setLocation(ctx->start);
    return assignment;
}

LgsVarDec* AntlerConverter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto expr = getExpr(ctx->expr(), !!ctx->QUEST_MARK());
    const auto varDec = new LgsVarDec(variableName, expr);
    varDec->setLocation(ctx->start);
    return varDec;
}

LgsVarDec* AntlerConverter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto variableName = ctx->VARIABLE()->getText();
    const auto varDec = new LgsVarDec(variableName);
    if (ctx->expr()) {
        varDec->expr = getExpr(ctx->expr());
    }
    varDec->type = getType(ctx->type());
    varDec->setLocation(ctx->start);
    return varDec;
}

LgsStmt* AntlerConverter::getReturnStmt(LogosParser::ReturnStatementContext* ctx) {
    const auto rs = new LgsReturn(getExpr(ctx->expr()));
    rs->setLocation(ctx->start);
    return rs;
}

LgsFuncType* AntlerConverter::getFuncType(LogosParser::FuncTypeContext* ctx) {
    const auto rt = getType(ctx->rt);
    const auto funcType = new LgsFuncType();
    funcType->setLocation(ctx->start);
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
    ifStmt->setLocation(ctx->start);
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
        assert(false && "No loop statements found");
    }

    loopStmt->stmtBlock = getStmtBlock(ctx->statementsBlock());
    loopStmt->setLocation(ctx->start);
    return loopStmt;
}

LgsForLoop* AntlerConverter::getRangeLoop(LogosParser::LoopStatementContext* ctx) {
    auto startExpr = getExpr(ctx->iterableRange->start);
    if (!startExpr) {
        startExpr = LGS_INT.getZeroValue();
    }
    const auto endExpr = getExpr(ctx->iterableRange->end);
    const auto rangeLoop = new LgsRangeLoop(startExpr, endExpr);
    const auto loopVarName = ctx->VARIABLE().front()->getText();
    auto varDec = new LgsVarDec(loopVarName);
    varDec->type = &LGS_INT;
    varDec->expr = LGS_INT.getZeroValue();
    rangeLoop->loopVars.emplace_back(varDec);
    return rangeLoop;
}

LgsForLoop* AntlerConverter::getForeachLoop(LogosParser::LoopStatementContext* ctx) {
    const auto iterExpr = getUnaryExpr(ctx->iterableExpr);
    const auto foreachLoop = new LgsForeachLoop(iterExpr);
    for (const auto variable : ctx->VARIABLE()) {
        const auto loopVarName = variable->getText();
        auto varDec = new LgsVarDec(loopVarName);
        foreachLoop->loopVars.emplace_back(varDec);
    }
    return foreachLoop;
}

LgsEnum* AntlerConverter::getEnum(LogosParser::EnumDeclarationContext* ctx) {
    const auto lgsEnum = new LgsEnum(ctx->TYPE()->getText());
    lgsEnum->setLocation(ctx->start);
    unordered_set<string> seenNames;
    for (size_t i = 0; i < ctx->enumField().size(); ++i) {
        const auto enumField = ctx->enumField()[i];
        const auto enumName = enumField->VARIABLE()->getText();
        if (!seenNames.insert(enumName).second) {
            errHandler.handleError(E10011, &lgsEnum->location, {enumName, to_string(lgsEnum->location.lineNumber)});
            break;
        }
        string enumText = "";
        if (enumField->STRING()) {
            enumText = enumField->STRING()->getText();
            cleanStr(enumText);
        }
        const auto field = new LgsEnumField(lgsEnum, enumName, enumText);
        field->type = lgsEnum;
        field->setLocation(ctx->start);
        lgsEnum->fields[enumName] = field;
    }
    return lgsEnum;
}

LgsExpr* AntlerConverter::getExpr(LogosParser::ExprContext* ctx, const bool isNullable) {
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
    if (isNullable) {
        assert(expr && expr->type);
        expr->type->isNullable = true;
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
    if (const auto variable = ctx->VARIABLE()) return getVariable(variable->getText(), ctx);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto vector = ctx->vector()) return getVector(vector);
    if (const auto constructor = ctx->constructor()) return getInstance(constructor);
    if (const auto constant = ctx->constant()) return getConstant(constant);
    if (const auto array = ctx->arrayExpr()) return getArrayExpr(array);
    if (const auto hashMap = ctx->hashMap()) return getHashMap(hashMap);
    if (const auto iterIndex = ctx->iterIndex()) return getIterIndex(iterIndex);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (const auto func = ctx->anonnymosFunc()) return getAnonymousFunc(func);
    if (ctx->NULL_()) return new LgsNull();
    assert(0);
}

LgsExpr* AntlerConverter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LgsBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->setLocation(ctx->start);
    return logosBinaryExpr;
}

LgsUnaryExpr* AntlerConverter::getArrayExpr(LogosParser::ArrayExprContext* ctx) {
    const auto array = new LgsArrayExpr();
    array->arrType->isStatic = !!ctx->EXCLA_MARK();
    array->arrType->iterLen = ctx->expr().size();
    array->arrType->sizeExpr = new LgsIntConst(array->arrType->iterLen);
    for (const auto expr : ctx->expr()) {
        array->initialElements.emplace_back(getExpr(expr));
    }
    array->setLocation(ctx->start);
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

LgsVariable* AntlerConverter::getVariable(const string& varName, const ParserRuleContext* ctx) const {
    const auto variable = new LgsVariable(varName);
    variable->setLocation(ctx->start);
    return variable;
}

LgsUnaryExpr* AntlerConverter::getConst(const string& constName, const ParserRuleContext* ctx) const {
    const auto constVariable = new LgsConst(constName);
    constVariable->setLocation(ctx->start);
    return constVariable;
}

LgsFuncCall* AntlerConverter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->VARIABLE()->getText();
    vector<LgsExpr*> args;
    if (ctx->funcArgList()) {
        for (const auto& arg : ctx->funcArgList()->funcArg()) {
            auto argExpr = getExpr(arg->expr());
            args.push_back(argExpr);
        }
    }
    const auto funcCall = new LgsFuncCall(name, args);
    funcCall->setLocation(ctx->start);
    return funcCall;
}

LgsUnaryExpr* AntlerConverter::getVector(LogosParser::VectorContext* vector) const {
    if (vector->VEC2()) {

    } else if (vector->VEC3()) {

    } else if (vector->VEC4()) {

    }
    assert(0);
}

LgsSelection* AntlerConverter::getSelection(LogosParser::SelectionContext* ctx) {
    const auto exprs = getSelectionInnerExprs(ctx);
    const auto selection = new LgsSelection(exprs);
    selection->setLocation(ctx->start);
    return selection;
}

LgsUnaryExpr* AntlerConverter::getFirstSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = ctx->firstSelectionElement();
    if (const auto variable = firstExpr->VARIABLE()) {
        return getVariable(variable->getText(), ctx);
    }
    if (const auto funcCall = firstExpr->funcCall()) {
        return getFuncCall(funcCall);
    }
    if (const auto iterIndex = firstExpr->iterIndex()) {
        return getIterIndex(iterIndex);
    }
    if (const auto selfInstance = firstExpr->SELF_INSTANCE()) {
        return getVariable(selfInstance->getText(), ctx);
    }
    if (const auto selfClass = firstExpr->SELF_CLASS()) {
        return getTypeConstant(selfClass, ctx);
    }
    if (const auto type = firstExpr->TYPE()) {
        return getTypeConstant(type, ctx);
    }
    if (const auto type = firstExpr->STRING()) {
        return getStrConst(type);
    }
    assert(0);
}

vector<LgsUnaryExpr*> AntlerConverter::getSelectionInnerExprs(LogosParser::SelectionContext* ctx) {
    vector exprs = {getFirstSelection(ctx)};
    const auto innerSelections = ctx->innerSelectionElement();
    exprs.reserve(innerSelections.size());
    for (int i = 0; i < innerSelections.size(); ++i) {
        const auto& currentExpr = innerSelections[i];
        if (const auto field = currentExpr->VARIABLE()) {
            const auto logosField = getVariable(field->getText(), currentExpr);
            exprs.push_back(logosField);
        } else if (const auto funcCall = currentExpr->funcCall()) {
            const auto logosMethodCall = getFuncCall(funcCall);
            // First inner expr takes firstExpr as parent
            const auto prevExpr = i == 0 ? exprs[0] : exprs[i - 1];
            logosMethodCall->args.insert(logosMethodCall->args.begin(), prevExpr);
            exprs.push_back(logosMethodCall);
        } else if (const auto iterIndex = currentExpr->iterIndex()) {
            const auto logosIterIndex = getIterIndex(iterIndex);
            exprs.push_back(logosIterIndex);
        }
    }
    return exprs;
}

LgsInstance* AntlerConverter::getInstance(LogosParser::ConstructorContext* ctx) {
    const auto instance = new LgsInstance(ctx->TYPE()->getText());
    instance->setLocation(ctx->start);
    const auto args = ctx->constructorArgList();
    if (!args) return instance;
    for (const auto& arg : args->constructorArg()) {
        const auto argExpr = getExpr(arg->expr());
        auto varDec = new LgsVarDec(arg->VARIABLE()->getText(), argExpr);
        varDec->setLocation(arg->start);
        instance->args.push_back(varDec);
    }
    return instance;
}

LgsIterIndex* AntlerConverter::getIterIndex(LogosParser::IterIndexContext* ctx) {
    LgsUnaryExpr* baseExpr;
    if (const auto variable = ctx->VARIABLE()) {
        baseExpr = getVariable(variable->getText(), ctx);
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
        iterIndexFrom->setLocation(indexExprFrom->start);
        const auto index = new LgsIndex{.from = iterIndexFrom, .to = iterIndexTo};
        const auto newIterIndex = new LgsIterIndex(baseExpr, index);
        newIterIndex->setLocation(ctx->start);
        baseExpr = newIterIndex;
    }

    return baseExpr->asIterIndex();
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
    constant->setLocation(ctx->start);
    return constant;
}

LgsStrConst* AntlerConverter::getStrConst(tree::TerminalNode* type) const {
    auto typeText = type->getText();
    cleanStr(typeText);
    const auto strConst = new LgsStrConst(typeText);
    strConst->setLocation(type->getSymbol());
    return strConst;
}

LgsTypeConst* AntlerConverter::getTypeConstant(tree::TerminalNode* type, const LogosParser::SelectionContext* ctx) const {
    const auto typeConst = new LgsTypeConst(getTypeFromText(type));
    typeConst->setLocation(ctx->start);
    return typeConst;
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
        result = getTypeFromText(ctx->TYPE());
        if (ctx->QUEST_MARK()) {
            result->isNullable = true;
        }
    }
    result->setLocation(ctx->start);
    return result;
}

LgsGroup* AntlerConverter::getGroup(LogosParser::GroupContext* ctx) {
    const auto group = new LgsGroup(ctx->TYPE()->getText());
    group->setLocation(ctx->start);
    for (const auto type : ctx->groupTypesList()->type()) {
        const auto lgsType = getType(type);
        group->types.push_back(lgsType);
    }
    for (const auto target : ctx->groupTargetList()->VARIABLE()) {
        const auto var = getVariable(target->getText(), ctx);
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

LgsType* AntlerConverter::getTypeFromText(tree::TerminalNode* typeToken) const {
    const auto typeText = typeToken->getText();
    LgsType* type = nullptr;
    if (typeText == LgsBool::name) {
        type = &LGS_BOOL;
    } else if (typeText == LgsChar::name) {
        type = &LGS_CHAR;
    } else if (typeText == LgsInt::name) {
        type = &LGS_INT;
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
    type->setLocation(typeToken->getSymbol());
    return type;
}

LgsType* AntlerConverter::getFuncReturnType(LogosParser::TypeContext* ctx) {
    LgsType* result = nullptr;
    if (!ctx) {
        result = &LGS_VOID;
    } else {
        result = getType(ctx);
        result->setLocation(ctx->start);
    }
    return result;
}

void AntlerConverter::cleanStr(string& value) const {
    value.erase(0, 1);
    value.pop_back();
}
