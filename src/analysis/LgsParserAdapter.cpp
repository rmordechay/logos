#include "analysis/LgsParserAdapter.h"
#include "funcs/LgsCoroutine.h"
#include "files/LgsEnvFile.h"
#include "files/LgsInterfaceFile.h"
#include "LogosLexer.h"
#include "LogosParser.h"
#include "exprs/unary/LgsCast.h"
#include "exprs/LgsNull.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/unary/constants/LgsCharConst.h"
#include "exprs/unary/constants/LgsFloatConst.h"
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
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/LgsTypeExpr.h"
#include "exprs/unary/LgsVectorExpr.h"
#include "files/LgsAppFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsMainFunc.h"
#include "lgsc/LgsCLang.h"
#include "loops/LgsInfiniteLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsGroup.h"
#include "types/LgsInterface.h"
#include "types/iterables/LgsMap.h"
#include "types/LgsNullable.h"
#include "types/LgsUnknown.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"
#include "utils/LgsUtils.h"
#include <loops/LgsLoopMetaVar.h>
#include <loops/LgsForeachLoop.h>
#include <loops/LgsRangeLoop.h>
#include <loops/LgsWhileLoop.h>
#include <stmts/LgsDeferStmt.h>
#include <types/iterables/LgsStr.h>
#include <types/LgsVoid.h>

LgsFile* LgsParserAdapter::parseFile(const std::string& codeText, const fs::path& filePath) {
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto file = parser.logosFile();
    checkParserErrors(&parser);
    return getLogosFile(file, filePath);
}

LgsFile* LgsParserAdapter::getLogosFile(LogosParser::LogosFileContext* ctx, const fs::path& filePath) {
    LgsFile* file = nullptr;
    if (const auto mainFile = ctx->mainFile()) {
        file = getMainFile(mainFile, filePath);
    } else if (const auto objFile = ctx->objectFile()) {
        file = getObjectFile(objFile, filePath);
    } else if (const auto interfaceFile = ctx->interfaceFile()) {
        file = getInterfaceFile(interfaceFile, filePath);
    } else if (const auto testFile = ctx->testFile()) {
        file = getTestFile(testFile, filePath);
    }
    assert(file);
    if (ctx->extern_()) {
        LgsCLang lgsCLang(paths);
        for (const auto importPath : ctx->extern_()->STRING()) {
            file->externalCPaths.emplace_back(getStrConst(importPath));
            lgsCLang.resolveCFiles(file);
            if (!lgsCLang.errHandler.successful) {
                errHandler.mergeErrors(lgsCLang.errHandler);
            }
        }
    }
    return file;
}

LgsMainFile* LgsParserAdapter::getMainFile(LogosParser::MainFileContext* ctx, const fs::path& filePath) {
    const auto funcs = ctx->func();
    const auto file = new LgsMainFile(fileID, filePath);
    setLocation(file->location, ctx->start);

    for (const auto enumDeclaration : ctx->enumDeclaration()) {
        auto lgsEnum = getEnum(enumDeclaration);
        file->enums.emplace_back(lgsEnum);
        addFileSymbol(file, LgsSymbol(lgsEnum));
    }

    for (const auto object : ctx->object()) {
        auto lgsObject = getObject(object->objectBody(), object->IDENTIFIER(), !!object->SINGLETON());
        if (!lgsObject) continue;
        file->objects.emplace_back(lgsObject);
        addFileSymbol(file, LgsSymbol(lgsObject));
    }

    for (const auto interface : ctx->interface()) {
        auto lgsInterface = getInterface(interface->interfaceBody(), interface->IDENTIFIER());
        file->interfaces.push_back(lgsInterface);
        addFileSymbol(file, LgsSymbol(lgsInterface));
    }

    for (const auto func : funcs) {
        auto funcName = func->funcSignature()->funcSignatureHeader()->IDENTIFIER()->getText();
        if (funcName == LGS_MAIN_FUNC_NAME) {
            file->funcs[funcName] = getMainFunc(func);
        } else {
            const auto lgsFunc = getFunc(func);
            file->funcs[funcName] = lgsFunc;
            addFileSymbol(file, LgsSymbol(lgsFunc));
        }
    }

    for (const auto group : ctx->group()) {
        const auto lgsGroup = getGroup(group);
        file->groups.push_back(lgsGroup);
        addFileSymbol(file, LgsSymbol(lgsGroup));
    }
    return file;
}

LgsObjectFile* LgsParserAdapter::getObjectFile(LogosParser::ObjectFileContext* ctx, const fs::path& filePath) {
    const auto objName = ctx->IDENTIFIER();
    const auto file = new LgsObjectFile(fileID, objName->getText(), filePath);
    setLocation(file->location, ctx->start);
    file->obj = getObject(ctx->objectBody(), objName, !!ctx->SINGLETON());
    globals.addSymbol(LgsSymbol(file->obj), &errHandler);
    return file;
}

LgsFile* LgsParserAdapter::getInterfaceFile(LogosParser::InterfaceFileContext* ctx, const fs::path& filePath) {
    const auto interfaceNameToken = ctx->IDENTIFIER();
    const auto file = new LgsInterfaceFile(fileID, interfaceNameToken->getText(), filePath);
    setLocation(file->location, ctx->start);
    file->interface = getInterface(ctx->interfaceBody(), interfaceNameToken);
    globals.addSymbol(LgsSymbol(file->interface), &errHandler);
    return file;
}

LgsFile* LgsParserAdapter::getTestFile(LogosParser::TestFileContext* ctx, const fs::path& filePath) {
    const auto file = new LgsTestFile(fileID, ctx->IDENTIFIER()->getText(), filePath);
    setLocation(file->location, ctx->start);
    for (const auto& func : ctx->func()) {
        const auto lgsFunc = getFunc(func);
        if (startsWith(lgsFunc->funcType->name, "test")) {
            lgsFunc->funcType->isTest = true;
            file->tests.push_back(lgsFunc);
        } else {
            file->funcs.push_back(lgsFunc);
        }
    }
    return file;
}

LgsEnvFile* LgsParserAdapter::getEnvFile(const fs::path& filePath) {
    const auto absFilePath = fs::path(fs::canonical(filePath));
    const auto codeText = getFileText(absFilePath);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    const auto ctx = parser.logosEnvFile();
    std::vector<LgsVarDec*> varDecs;
    for (const auto& explicitVarDec : ctx->explicitVarDec()) {
        varDecs.emplace_back(getExplicitVarDec(explicitVarDec));
    }
    for (const auto& implicitVarDec : ctx->implicitVarDec()) {
        varDecs.emplace_back(getImplicitVarDec(implicitVarDec));
    }
    auto file = new LgsEnvFile(fileID, "EnvFile", absFilePath, varDecs);
    if (!checkParserErrors(&parser)) return file;
    return file;
}

void LgsParserAdapter::setAppConfigs(LgsAppConfigs& appConfigs) {
    if (!fs::exists(paths.appFilePath)) return;
    auto codeText = getFileText(paths.appFilePath);
    antlr4::ANTLRInputStream input(codeText);
    LogosLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    LogosParser parser(&tokens);
    if (!checkParserErrors(&parser)) return;
    const auto ctx = parser.logosAppFile();
    LgsAppFile lgsAppFile(fileID, paths.appFilePath);
    setLocation(lgsAppFile.location, ctx->start);
    for (int i = 0; i < ctx->IDENTIFIER().size(); ++i) {
        const auto varToken = ctx->IDENTIFIER()[i];
        const auto varName = varToken->getText();
        const auto expr = getExpr(ctx->expr()[i]);
        if (!expr) continue;
        if (varName == "name") {
            appConfigs.name = expr->asStrConst()->value;
        }
        if (varName == "version") {
            auto versionStr = expr->asStrConst()->value;
            int consumed = 0;
            auto [major, minor, micro] = appConfigs.version;
            const auto s = std::sscanf(versionStr.c_str(), "%d.%d.%d%n", &major, &minor, &micro, &consumed) == 3;
            if (!s || versionStr[consumed] != '\0') {
                errHandler.addError(E10068, &lgsAppFile.location, {versionStr});
            }
        }
        if (varName == "activeEnv") {
            appConfigs.activeEnv = expr->asStrConst()->value;
        }
        freeExpr(expr);
    }

    const auto requireEnvs = ctx->requireEnvVars();
    if (!requireEnvs) return;
    for (int i = 0; i < requireEnvs->type().size(); ++i) {
        const auto name = requireEnvs->IDENTIFIER()[i]->getText();
        const auto type = getType(requireEnvs->type()[i]);
        const auto varDec = new LgsVarDec(name, nullptr);
        varDec->type = type;
        lgsAppFile.requireEnvVars.push_back(varDec);
    }

    const auto packages = ctx->requirePackages();
    if (!packages) return;
    for (const auto packagePath : packages->STRING()) {
        auto pathText = packagePath->getText();
        cleanStr(pathText);
        lgsAppFile.requirePackages.push_back(pathText);
    }
}

LgsObject* LgsParserAdapter::getObject(LogosParser::ObjectBodyContext* ctx, antlr4::tree::TerminalNode* objName, const bool isSingleton) {
    const auto obj = new LgsObject(objName->getText());
    setLocation(obj->location, objName->getSymbol());
    if (!validateTypeName(obj->name, &obj->location)) return obj;

    // Fields
    for (int i = 0; i < ctx->field().size(); ++i) {
        const auto lgsField = getField(ctx->field(i), i);
        const auto fieldAdded = obj->addField(lgsField);
        if (!fieldAdded) {
            errHandler.addError(E10056, &obj->location, {obj->name, lgsField->name});
        }
    }

    // Methods
    for (const auto& func : ctx->method()) {
        const auto method = getMethod(func, obj);
        const auto methodAdded = obj->addMethod(method);
        if (!methodAdded) {
            errHandler.addError(E10072, &obj->location, {obj->name, method->funcType->pname()});
        }
    }

    // IO Pairs
    for (const auto& ioPair : ctx->ioPair()) {
        const auto lgsIOPair = getIOPair(ioPair);
        obj->ioPairs.push_back(lgsIOPair);
    }

    // Interfaces
    if (ctx->implements()) {
        for (const auto& type : ctx->implements()->IDENTIFIER()) {
            auto implementType = getTypeFromText(type);
            obj->interfaces.push_back(implementType);
        }
    }

    if (isSingleton) {
        obj->singleton = new LgsInstance(obj);
    }

    return obj;
}

LgsInterface* LgsParserAdapter::getInterface(LogosParser::InterfaceBodyContext* ctx, antlr4::tree::TerminalNode* interfaceName) {
    const auto interface = new LgsInterface(interfaceName->getText());
    setLocation(interface->location, interfaceName->getSymbol());
    if (!validateTypeName(interface->name, &interface->location)) return interface;

    if (ctx->implements()) {
        for (const auto& type : ctx->implements()->IDENTIFIER()) {
            auto implementType = getTypeFromText(type);
            interface->interfaces.push_back(implementType);
        }
    }

    for (int i = 0; i < ctx->interfaceField().size(); ++i) {
        const auto interfaceField = ctx->interfaceField()[i];
        const auto field = getInterfaceField(interfaceField);
        field->isOptional = !!interfaceField->QUEST_MARK();
        field->isVirtual = true;
        interface->addField(field);
    }

    for (const auto& interfaceFunc : ctx->interfaceFunc()) {
        const auto type = getFuncReturnType(interfaceFunc->type());
        const auto funcName = interfaceFunc->funcSignatureHeader()->IDENTIFIER();
        const auto func = new LgsFunc(funcName->getText(), type);
        currentFunc = func;
        setLocation(func->location, funcName->getSymbol());
        func->funcType->parentName = interface->name;
        func->funcType->isPublic = true;
        func->funcType->isVirtual = !func->stmtsBlock;
        func->funcType->isOptional = !!interfaceFunc->QUEST_MARK();
        setParams(func->funcType, interfaceFunc->funcSignatureHeader()->param());
        func->stmtsBlock = getStmtBlock(interfaceFunc->statementsBlock());
        currentFunc = nullptr;
        interface->addMethod(func);
    }
    return interface;
}

LgsFunc* LgsParserAdapter::getFunc(LogosParser::FuncContext* ctx) {
    const auto rt = getFuncReturnType(ctx->funcSignature()->type());
    const auto funcSignature = ctx->funcSignature();
    const auto funcNameToken = funcSignature->funcSignatureHeader()->IDENTIFIER();
    const auto funcName = funcNameToken->getText();
    const auto func = new LgsFunc(funcName, rt);
    currentFunc = func;
    setLocation(func->location, funcNameToken->getSymbol());
    setParams(func->funcType, funcSignature->funcSignatureHeader()->param());
    func->stmtsBlock = getStmtBlock(ctx->statementsBlock());
    currentFunc = nullptr;
    return func;
}

LgsMainFunc* LgsParserAdapter::getMainFunc(LogosParser::FuncContext* ctx) {
    const auto mainFunc = new LgsMainFunc();
    currentFunc = mainFunc;
    const auto funcSignature = ctx->funcSignature();
    setLocation(mainFunc->location, funcSignature->funcSignatureHeader()->IDENTIFIER()->getSymbol());
    mainFunc->stmtsBlock = getStmtBlock(ctx->statementsBlock());
    bool isValid = true;
    const auto paramSize = funcSignature->funcSignatureHeader()->param().size();
    if (paramSize > 1) {
        isValid = false;
    } else if (paramSize == 1) {
        isValid = setMainArgsParam(mainFunc, funcSignature);
        if (isValid) mainFunc->setMainArgs();
    }
    if (!isValid) {
        errHandler.addError(E10039, &mainFunc->location);
    }
    currentFunc = nullptr;
    return mainFunc;
}

LgsFunc* LgsParserAdapter::getLambda(LogosParser::LambdaContext* ctx) {
    const auto func = new LgsFunc(LGS_ANONYMOUS_STR);
    currentFunc = func;
    func->funcType->isLambda = true;
    func->funcType->rt = getType(ctx->rt);
    if (const auto singleParam = ctx->IDENTIFIER()) {
        auto lgsParam = LgsParam(nullptr, singleParam->getText());
        setLocation(lgsParam.location, singleParam->getSymbol());
        func->funcType->params.push_back(lgsParam);
    } else if (const auto params = ctx->lambdaParams()) {
        for (const auto lambdaParam : params->lambdaParam()) {
            const auto param = lambdaParam->IDENTIFIER();
            const auto type = getType(lambdaParam->type());
            auto lgsParam = LgsParam(type, param->getText());
            setLocation(lgsParam.location, param->getSymbol());
            func->funcType->params.push_back(lgsParam);
        }
    }
    func->stmtsBlock = getStmtBlock(ctx->statementsBlock());
    setLocation(func->location, ctx->start);
    currentFunc = nullptr;
    return func;
}

LgsFunc* LgsParserAdapter::getMethod(LogosParser::MethodContext* ctx, LgsType* obj) {
    const auto rt = getFuncReturnType(ctx->funcSignature()->type());
    const auto funcSignature = ctx->funcSignature();
    const auto nameToken = funcSignature->funcSignatureHeader()->IDENTIFIER();
    const auto method = new LgsFunc(nameToken->getText(), rt);
    currentFunc = method;
    setLocation(method->location, nameToken->getSymbol());
    method->funcType->parentName = obj->getName();
    setParams(method->funcType, funcSignature->funcSignatureHeader()->param());
    method->stmtsBlock = getStmtBlock(ctx->statementsBlock());
    if (ctx->VISIBILITY()) {
        method->funcType->isPublic = true;
    }
    if (method->funcType->isMethod) {
        method->funcType->params.insert(method->funcType->params.begin(), LgsParam(obj, LGS_SELF));
    }
    currentFunc = nullptr;
    return method;
}

LgsField* LgsParserAdapter::getField(LogosParser::FieldContext* ctx, const size_t position) {
    const auto name = ctx->IDENTIFIER()->getText();
    const auto type = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto field = new LgsField(name, type, expr);
    field->isPublic = !!ctx->VISIBILITY();
    field->isConst = ctx->CONST() != nullptr;
    field->position = position;
    setLocation(field->location, ctx->start);
    return field;
}

LgsField* LgsParserAdapter::getInterfaceField(LogosParser::InterfaceFieldContext* ctx) {
    const auto name = ctx->IDENTIFIER()->getText();
    const auto type = getType(ctx->type());
    const auto expr = getExpr(ctx->expr());
    const auto field = new LgsField(name, type, expr);
    field->isConst = ctx->CONST() != nullptr;
    setLocation(field->location, ctx->start);
    return field;
}

LgsParam LgsParserAdapter::getParam(LgsFuncType* funcType, LogosParser::ParamContext* param) {
    const auto variableName = param->IDENTIFIER()->getText();
    const auto expr = getExpr(param->expr());
    auto lgsParam = LgsParam(getType(param->type()), variableName, expr);
    setLocation(lgsParam.location, param->start);
    if (param->TRIPLE_DOT()) {
        lgsParam.isVariadic = true;
        funcType->isVariadic = true;
    } else if (lgsParam.expr) {
        funcType->hasDefaults = true;
    }
    return lgsParam;
}

LgsIOPair* LgsParserAdapter::getIOPair(const LogosParser::IoPairContext* ioPair) const {
    const auto lgsIOPair = new LgsIOPair(ioPair->opening->getText(), ioPair->closing->getText());
    setLocation(lgsIOPair->location, ioPair->start);
    return lgsIOPair;
}

LgsStmt* LgsParserAdapter::getDeferStmt(LogosParser::DeferStmtContext* ctx) {
    const auto deferStmt = new LgsDeferStmt();
    if (const auto funcCall = ctx->funcCall()) {
        deferStmt->funcCall = getFuncCall(funcCall);
    } else if (const auto selection = ctx->selection()) {
        deferStmt->selection = getSelection(selection);
    } else {
        assert(0);
    }
    setLocation(deferStmt->location, ctx->start);
    return deferStmt;
}

LgsStmt* LgsParserAdapter::getStmt(LogosParser::StatementContext* ctx) {
    if (const auto expr = ctx->expr()) return getExpr(expr);
    if (const auto ifStmt = ctx->ifStatement()) return getIfStatement(ifStmt);
    if (const auto fieldDef = ctx->assignment()) return getAssignment(fieldDef);
    if (const auto implicitVarDec = ctx->implicitVarDec()) return getImplicitVarDec(implicitVarDec);
    if (const auto explicitVarDec = ctx->explicitVarDec()) return getExplicitVarDec(explicitVarDec);
    if (const auto patternMatching = ctx->patternMatching()) return getPatternMatching(patternMatching);
    if (const auto loopStmt = ctx->loopStatement()) return getForLoop(loopStmt);
    if (const auto coroutine = ctx->coroutine()) return getCoroutine(coroutine);
    if (const auto deferStmt = ctx->deferStmt()) return getDeferStmt(deferStmt);
    if (const auto returnStmt = ctx->returnStatement()) return getReturnStmt(returnStmt);
    if (const auto breakStmt = ctx->breakStmt()) return getBreakStmt(breakStmt);
    if (const auto ioStmt = ctx->ioStatement()) return getIOStmt(ioStmt);
    if (ctx->CONTINUE()) return getContinueStmt(ctx);
    assert(0);
}

LgsStmtsBlock* LgsParserAdapter::getStmtBlock(LogosParser::StatementsBlockContext* ctx) {
    if (!ctx) return nullptr;
    const auto stmtBlock = new LgsStmtsBlock();
    setLocation(stmtBlock->location, ctx->start);
    for (const auto& statement : ctx->statement()) {
        auto stmt = getStmt(statement);
        stmtBlock->stmts.push_back(stmt);
    }
    return stmtBlock;
}

LgsEnum* LgsParserAdapter::getEnum(LogosParser::EnumDeclarationContext* ctx) {
    const auto lgsEnum = new LgsEnum(ctx->IDENTIFIER()->getText());
    setLocation(lgsEnum->location, ctx->start);
    if (!validateTypeName(lgsEnum->name, &lgsEnum->location)) return lgsEnum;
    std::unordered_set<std::string> seenNames;
    for (size_t i = 0; i < ctx->enumField().size(); ++i) {
        const auto enumField = ctx->enumField()[i];
        const auto enumFieldName = enumField->IDENTIFIER()->getText();
        if (!seenNames.insert(enumFieldName).second) {
            errHandler.addError(E10064, &lgsEnum->location, {enumFieldName, lgsEnum->name});
            break;
        }
        const auto field = new LgsField(enumFieldName, lgsEnum);
        if (enumField->STRING()) {
            field->expr = getStrConst(enumField->STRING());
        }
        setLocation(field->location, ctx->start);
        lgsEnum->fields.push_back(field);
    }
    return lgsEnum;
}

void LgsParserAdapter::setParams(LgsFuncType* funcType, const std::vector<LogosParser::ParamContext*>& params) {
    for (int i = 0; i < params.size(); ++i) {
        const auto param = params[i];
        if (const auto paramFuncType = param->type()->funcType()) {
            const auto lgsParamFuncType = getFuncType(paramFuncType);
            lgsParamFuncType->name = param->IDENTIFIER()->getText();
            auto lgsParam = LgsParam(lgsParamFuncType);
            lgsParam.name = lgsParamFuncType->name;
            setLocation(lgsParam.location, param->start);
            funcType->params.push_back(lgsParam);
            continue;
        }
        auto lgsParam = getParam(funcType, param);
        funcType->params.push_back(lgsParam);
    }
}

bool LgsParserAdapter::setMainArgsParam(const LgsMainFunc* mainFunc, LogosParser::FuncSignatureContext* funcSignature) {
    const auto param = funcSignature->funcSignatureHeader()->param().front();
    const auto type = param->type();
    const auto variableName = param->IDENTIFIER()->getText();
    const auto expr = getExpr(param->expr());
    auto lgsParam = LgsParam(getType(type), variableName, expr);
    setLocation(lgsParam.location, param->start);
    const auto arr = lgsParam.type->asDArray();
    mainFunc->funcType->params.push_back(lgsParam);
    return arr && arr->baseType->asStr();
}

LgsAssignType mapAssignType(LogosParser::AssignmentContext* assignment) {
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

LgsAssignment* LgsParserAdapter::getAssignment(LogosParser::AssignmentContext* ctx) {
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
    setLocation(assignment->location, ctx->start);
    return assignment;
}

LgsVarDec* LgsParserAdapter::getVarDec(antlr4::tree::TerminalNode* name, const bool isConst, LgsExpr* expr) const {
    const auto varDec = new LgsVarDec(name->getText(), expr);
    varDec->isConst = isConst;
    setLocation(varDec->location, name->getSymbol());
    return varDec;
}

LgsVarDec* LgsParserAdapter::getImplicitVarDec(LogosParser::ImplicitVarDecContext* ctx) {
    const auto varDec = getVarDec(ctx->IDENTIFIER(), !!ctx->QUEST_MARK(), getExpr(ctx->expr()));
    varDec->isNullable = !!ctx->QUEST_MARK();
    varDec->isConst = !ctx->CONST();
    return varDec;
}

LgsVarDec* LgsParserAdapter::getExplicitVarDec(LogosParser::ExplicitVarDecContext* ctx) {
    const auto varDec = getVarDec(ctx->IDENTIFIER());
    varDec->isConst = !ctx->CONST();
    if (ctx->expr()) {
        varDec->expr = getExpr(ctx->expr());
        varDec->expr->isMutable = varDec->isConst;
    }
    varDec->type = getType(ctx->type());
    return varDec;
}

LgsCoroutine* LgsParserAdapter::getCoroutine(LogosParser::CoroutineContext* ctx) {
    const auto coroutine = new LgsCoroutine();
    if (const auto funcCall = ctx->funcCall()) {
        coroutine->funcCall = getFuncCall(funcCall);
    } else if (const auto selection = ctx->selection()) {
        const auto lgsSelection = getSelection(selection);
        if (!lgsSelection->lastExpr()->asFuncCall()) {
            errHandler.addError(E10021, &lgsSelection->location);
        }
        coroutine->selection = lgsSelection;
    } else {
        assert(0);
    }
    return coroutine;
}

LgsStmt* LgsParserAdapter::getReturnStmt(LogosParser::ReturnStatementContext* ctx) {
    const auto rs = new LgsReturn(getExpr(ctx->expr()));
    setLocation(rs->location, ctx->start);
    return rs;
}

LgsIfStmt* LgsParserAdapter::getIfStatement(LogosParser::IfStatementContext* ctx) {
    const auto expr = getExpr(ctx->expr());
    const auto stmts = getStmtBlock(ctx->statementsBlock());
    const auto ifStmt = new LgsIfStmt(expr, stmts);
    if (const auto tag = ctx->TAG()) {
        ifStmt->tag = tag->getText().substr(1);
    }
    for (const auto &elseIfStmt : ctx->elseIfStatement()) {
        auto elseIfExpr = getExpr(elseIfStmt->expr());
        auto elseIfStmtBlock = getStmtBlock(elseIfStmt->statementsBlock());
        ifStmt->elseIfs.emplace_back(std::make_pair(elseIfExpr, elseIfStmtBlock));
    }
    if (const auto &elseStmt = ctx->elseStatement()) {
        ifStmt->elseBlock = getStmtBlock(elseStmt->statementsBlock());
    }
    setLocation(ifStmt->location, ctx->start);
    return ifStmt;
}

LgsBreak* LgsParserAdapter::getBreakStmt(LogosParser::BreakStmtContext* ctx) const {
    const auto breakStmt = new LgsBreak();
    setLocation(breakStmt->location, ctx->start);
    if (const auto tag = ctx->TAG()) {
        breakStmt->tag = tag->getText().substr(1);
    } else if (ctx->IF()) {
        breakStmt->isBreakIf = true;
    }
    return breakStmt;
}

LgsStmt* LgsParserAdapter::getIOStmt(LogosParser::IoStatementContext* ioStmt) {
    const auto stmtsBlock = getStmtBlock(ioStmt->statementsBlock());
    const auto lgsIOStmt = new LgsIOStmt(stmtsBlock);
    setLocation(lgsIOStmt->location, ioStmt->start);
    lgsIOStmt->varDec = getVarDec(ioStmt->IDENTIFIER(), true);
    if (ioStmt->funcCall()) {
        lgsIOStmt->varDec->expr = getFuncCall(ioStmt->funcCall());
    } else if (ioStmt->selection()) {
        lgsIOStmt->varDec->expr = getSelection(ioStmt->selection());
    } else {
        assert(0);
    }
    return lgsIOStmt;
}

LgsStmt* LgsParserAdapter::getContinueStmt(const LogosParser::StatementContext* ctx) const {
    const auto continueStmt = new LgsContinue();
    setLocation(continueStmt->location, ctx->start);
    return continueStmt;
}

LgsStmt* LgsParserAdapter::getPatternMatching(LogosParser::PatternMatchingContext* ctx) {
    const auto patternMatching = new LgsPattern(getExpr(ctx->expr()));
    for (const auto& pattern : ctx->pattern()) {
        const auto expr = getExpr(pattern->expr());
        const auto stmtBlock = getStmtBlock(pattern->statementsBlock());
        patternMatching->elseIfs.emplace_back(std::make_pair(expr, stmtBlock));
    }
    patternMatching->elseBlock = getStmtBlock(ctx->statementsBlock());
    return patternMatching;
}

LgsForLoop* LgsParserAdapter::getForLoop(LogosParser::LoopStatementContext* ctx) {
    LgsForLoop* loopStmt = nullptr;
    if (ctx->iterableExpr) {
        loopStmt = getForeachLoop(ctx);
    } else if (ctx->rangeLoop()) {
        loopStmt = getRangeLoop(ctx->rangeLoop());
    } else if (ctx->WHILE()) {
        loopStmt = getWhileLoop(ctx);
    } else {
        loopStmt = getInfiniteLoop(ctx);
    }
    setLocation(loopStmt->location, ctx->start);
    loopStmt->stmtsBlock = getStmtBlock(ctx->statementsBlock());
    return loopStmt;
}

LgsForLoop* LgsParserAdapter::getRangeLoop(LogosParser::RangeLoopContext* ctx) {
    LgsRangeLoop* rangeLoop = nullptr;
    if (ctx->expr()) {
        rangeLoop = new LgsRangeLoop(nullptr, getExpr(ctx->expr()));
    } else {
        rangeLoop = new LgsRangeLoop(getExpr(ctx->iterableRange->start), getExpr(ctx->iterableRange->end));
        const auto loopVarToken = ctx->IDENTIFIER();
        const auto loopVarName = loopVarToken->getText();
        rangeLoop->loopVars.emplace_back(getVarDec(loopVarToken, true));
    }
    setLocation(rangeLoop->location, ctx->start);
    return rangeLoop;
}

LgsForLoop* LgsParserAdapter::getForeachLoop(LogosParser::LoopStatementContext* ctx) {
    const auto iterExpr = getUnaryExpr(ctx->iterableExpr);
    const auto foreachLoop = new LgsForeachLoop(iterExpr);
    for (const auto variable : ctx->IDENTIFIER()) {
        const auto loopVarName = variable->getText();
        auto varDec = getVarDec(variable);
        foreachLoop->loopVars.emplace_back(varDec);
    }
    return foreachLoop;
}

LgsForLoop* LgsParserAdapter::getWhileLoop(const LogosParser::LoopStatementContext* ctx) {
    const auto expr = getExpr(ctx->whileExpr);
    const auto whileLoop = new LgsWhileLoop(expr);
    setLocation(whileLoop->location, ctx->start);
    return whileLoop;
}

LgsForLoop* LgsParserAdapter::getInfiniteLoop(const LogosParser::LoopStatementContext* ctx) const {
    const auto rangeLoop = new LgsInfiniteLoop();
    setLocation(rangeLoop->location, ctx->start);
    return rangeLoop;
}

LgsExpr* LgsParserAdapter::getExpr(LogosParser::ExprContext* ctx) {
    if (!ctx) return nullptr;
    LgsExpr* expr = nullptr;
    if (const auto unary = ctx->unaryExpr()) {
        expr = getUnaryExpr(unary);
    } else if (ctx->right){
        expr = getBinaryExpr(ctx);
    }else if (ctx->cast) {
        expr = getCast(ctx);
    } else if (ctx->LPAREN() && ctx->RPAREN()) {
        expr = getExpr(ctx->left);
    }
    return expr;
}

LgsExpr* LgsParserAdapter::getCast(LogosParser::ExprContext* ctx) {
    LgsExpr* castFromValue;
    if (const auto unary = ctx->unaryExpr()) {
        castFromValue = getUnaryExpr(unary);
    } else {
        castFromValue = getBinaryExpr(ctx);
    }
    LgsType* castToType = getType(ctx->cast);
    return new LgsCast(castToType, castFromValue);
}

LgsUnaryExpr* LgsParserAdapter::getJSON(LogosParser::JsonContext* json) {
    assert(0);
}

LgsUnaryExpr* LgsParserAdapter::getUnaryExpr(LogosParser::UnaryExprContext* ctx) {
    if (const auto variable = ctx->IDENTIFIER()) return getVariable(variable);
    if (const auto funcCall = ctx->funcCall()) return getFuncCall(funcCall);
    if (const auto prefixExpr = ctx->prefixExpr()) return getPrefixExpr(prefixExpr);
    if (const auto postfixExpr = ctx->postfixExpr()) return getPostfixExpr(postfixExpr);
    if (const auto constructor = ctx->instance()) return getInstance(constructor);
    if (const auto constant = ctx->constant()) return getConstant(constant);
    if (const auto array = ctx->arrayExpr()) return getArrayExpr(array);
    if (const auto hashMap = ctx->hashMap()) return getHashMap(hashMap);
    if (const auto iterIndex = ctx->iterIndex()) return getIterIndex(iterIndex);
    if (const auto selection = ctx->selection()) return getSelection(selection);
    if (const auto isFirst = ctx->forVariable()) return getLoopMetaVar(isFirst);
    if (const auto func = ctx->lambda()) return getLambda(func);
    if (const auto vector = ctx->vector()) return getVectorExpr(vector);
    if (const auto null = ctx->NULL_()) return getNullValue(null);
    if (const auto json = ctx->json()) return getJSON(json);
    assert(0);
}

LgsOperator mapOperator(LogosParser::ExprContext* expr) {
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
    if (expr->IN()) return IN;
    assert(false);
}

LgsExpr* LgsParserAdapter::getBinaryExpr(LogosParser::ExprContext* ctx) {
    const auto l = getExpr(ctx->left);
    const auto r = getExpr(ctx->right);
    const auto logosBinaryExpr = new LgsBinaryExpr(l->type, l, r, mapOperator(ctx));
    logosBinaryExpr->opStr = ctx->getText();
    setLocation(logosBinaryExpr->location, ctx->start);
    return logosBinaryExpr;
}

LgsUnaryExpr* LgsParserAdapter::getPrefixExpr(LogosParser::PrefixExprContext* ctx) {
    LgsPrefixOperator op;
    if (ctx->NOT()) {
        op = NOT_PREFIX;
    } else if (ctx->MINUS()) {
        op = MINUS_PREFIX;
    } else if (ctx->SLIDER()) {
        op = SQRT_PREFIX;
    } else {
        assert(0);
    }
    const auto expr = getExpr(ctx->expr());
    const auto prefixExpr = new LgsPrefixExpr(expr, op);
    setLocation(prefixExpr->location, ctx->start);
    return prefixExpr;
}

LgsPostfixExpr* LgsParserAdapter::getPostfixExpr(LogosParser::PostfixExprContext* ctx) {
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
    setLocation(postfixExpr->location, ctx->start);
    return postfixExpr;
}

LgsUnaryExpr* LgsParserAdapter::getArrayExpr(LogosParser::ArrayExprContext* ctx) {
    LgsArrayExpr* array = nullptr;
    if (ctx->EXCLA_MARK()) {
        array = new LgsArrayExpr(new LgsSArray());
    } else {
        array = new LgsArrayExpr(new LgsDArray());
    }
    array->type->asIterable()->sizeExpr = new LgsIntConst(&LGS_INT, ctx->expr().size());
    for (const auto expr : ctx->expr()) {
        array->initialElements.emplace_back(getExpr(expr));
    }
    setLocation(array->location, ctx->start);
    return array;
}

LgsUnaryExpr* LgsParserAdapter::getHashMap(LogosParser::HashMapContext* ctx) {
    const auto hashMap = new LgsHashMap();
    for (const auto keyValue : ctx->keyValue()) {
        const auto kExpr = getExpr(keyValue->key);
        const auto vExpr = getExpr(keyValue->value);
        const auto mapEntry = new LgsMapEntry(kExpr, vExpr);
        hashMap->initialElements.emplace_back(mapEntry);
    }
    return hashMap;
}

LgsVariable* LgsParserAdapter::getVariable(antlr4::tree::TerminalNode* ctx) const {
    const auto variable = new LgsVariable(ctx->getText());
    if (variable->name == LGS_SELF) {
        currentFunc->funcType->isMethod = true;
    }
    setLocation(variable->location, ctx->getSymbol());
    return variable;
}

LgsFuncCall* LgsParserAdapter::getFuncCall(LogosParser::FuncCallContext* ctx) {
    const auto name = ctx->IDENTIFIER()->getText();
    std::vector<LgsExpr*> args;
    const auto funcArgsList = ctx->funcArgList();
    if (funcArgsList) {
        args.reserve(funcArgsList->funcArg().size());
        for (const auto& arg : funcArgsList->funcArg()) {
            auto argExpr = getExpr(arg->expr());
            args.push_back(argExpr);
        }
    }
    if (!args.empty() && ctx->TRIPLE_DOT()) {
        args[args.size() - 1]->isSpread = true;
    }
    const auto funcCall = new LgsFuncCall(name, args);
    setLocation(funcCall->location, ctx->start);
    return funcCall;
}

LgsUnaryExpr* LgsParserAdapter::getVectorExpr(LogosParser::VectorContext* ctx) {
    uint8_t dim = 0;
    if (ctx->VEC2()) dim = 2;
    else if (ctx->VEC3()) dim = 3;
    else if (ctx->VEC4()) dim = 4;
    else assert(0);

    const auto lgsVec = new LgsVectorExpr(dim);
    setLocation(lgsVec->location, ctx->start);
    for (const auto& expr : ctx->expr()) {
        lgsVec->args.emplace_back(getExpr(expr));
    }
    return lgsVec;
}

LgsSelection* LgsParserAdapter::getSelection(LogosParser::SelectionContext* ctx) {
    const auto exprs = getSelectionExprs(ctx);
    const auto selection = new LgsSelection(exprs);
    setLocation(selection->location, ctx->start);
    return selection;
}

LgsUnaryExpr* LgsParserAdapter::getFirstSelection(LogosParser::SelectionContext* ctx) {
    const auto firstExpr = ctx->firstSelectionElement();
    if (const auto variable = firstExpr->IDENTIFIER()) {
        if (isupper(variable->getText()[0])) return new LgsTypeExpr(getTypeFromText(variable));
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
        assert(0);
    }
    if (const auto type = firstExpr->STRING()) {
        return getStrConst(type);
    }
    assert(0);
}

std::vector<LgsUnaryExpr*> LgsParserAdapter::getSelectionExprs(LogosParser::SelectionContext* ctx) {
    std::vector exprs = {getFirstSelection(ctx)};
    const auto innerSelections = ctx->innerSelectionElement();
    for (int i = 0; i < innerSelections.size(); ++i) {
        const auto& currentExpr = innerSelections[i];
        if (const auto field = currentExpr->IDENTIFIER()) {
            const auto lgsField = getVariable(field);
            exprs.push_back(lgsField);
        } else if (const auto funcCall = currentExpr->funcCall()) {
            const auto logosMethodCall = getFuncCall(funcCall);
            logosMethodCall->isMethodCall = true;
            exprs.push_back(logosMethodCall);
        } else if (const auto iterIndex = currentExpr->iterIndex()) {
            const auto logosIterIndex = getIterIndex(iterIndex);
            exprs.push_back(logosIterIndex);
        }
    }
    return exprs;
}

LgsInstance* LgsParserAdapter::getInstance(LogosParser::InstanceContext* ctx) {
    const auto instance = new LgsInstance(ctx->IDENTIFIER()->getText());
    setLocation(instance->location, ctx->start);
    instance->type = new LgsUnknown(instance->name);
    const auto args = ctx->instanceArgList();
    if (!args) return instance;
    std::unordered_set<std::string> initializedArgs;
    for (const auto& arg : args->instanceArg()) {
        const auto argExpr = getExpr(arg->expr());
        const auto varDec = getVarDec(arg->IDENTIFIER(), true, argExpr);
        if (isArgsDuplicate(initializedArgs, varDec)) return instance;
        initializedArgs.insert(varDec->name);
        instance->args[varDec->name] = varDec;
    }
    return instance;
}

LgsIterIndex* LgsParserAdapter::getIterIndex(LogosParser::IterIndexContext* ctx) {
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
        setLocation(newIterIndex->location, ctx->start);
        baseExpr = newIterIndex;
    }

    return baseExpr->asIterIndex();
}

LgsUnaryExpr* LgsParserAdapter::getConstant(LogosParser::ConstantContext* ctx) {
    LgsUnaryExpr* constant = nullptr;
    if (const auto intToken = ctx->INTEGER()) {
        const auto input = removeUnderscores(intToken->getText());
        char* end;
        const auto longValue = strtol(input.c_str(), &end, 10);
        if (longValue >= INT_MIN && longValue <= INT_MAX) {
            const auto intValue = static_cast<int>(longValue);
            constant = new LgsIntConst(&LGS_INT, intValue);
        } else {
            constant = new LgsIntConst(&LGS_LONG, longValue);
        }
    } else if (const auto longToken = ctx->LONG()) {
        constant = new LgsIntConst(&LGS_LONG, stol(longToken->getText()));
    } else if (const auto floatToken = ctx->FLOAT()) {
        const auto value = stof(floatToken->getText());
        constant = new LgsFloatConst(&LGS_FLOAT, value);
    } else if (const auto boolToken = ctx->BOOL()) {
        const auto value = boolToken->getText() == LgsBool::trueLiteral;
        constant = new LgsIntConst(&LGS_BOOL, value);
    } else if (const auto strToken = ctx->STRING()) {
        const auto value = strToken->getText();
        if (value.size() == 1) {
            constant = new LgsCharConst(value[0]);
        } else {
            constant = getStrConst(strToken);
        }
    }
    if (constant) {
        setLocation(constant->location, ctx->start);
    }
    return constant;
}

LgsStrConst* LgsParserAdapter::getStrConst(antlr4::tree::TerminalNode* ctx) {
    auto text = ctx->getText();
    cleanStr(text);
    const auto strConst = new LgsStrConst(text);
    extractStrParts(*strConst);
    setLocation(strConst->location, ctx->getSymbol());
    return strConst;
}

LgsUnaryExpr* LgsParserAdapter::getNullValue(const antlr4::tree::TerminalNode* ctx) const {
    const auto lgsNull = new LgsNull();
    setLocation(lgsNull->location, ctx->getSymbol());
    return lgsNull;
}

LgsUnaryExpr* LgsParserAdapter::getLoopMetaVar(LogosParser::ForVariableContext* ctx) const {
    LgsLoopMetaVar* var;
    if (ctx->FOR_I()) {
        var = new LgsLoopMetaVar(FOR_I);
    } else if (ctx->FOR_IS_FIRST()) {
        var = new LgsLoopMetaVar(FOR_IS_FIRST);
        var->type = &LGS_BOOL;
    } else if (ctx->FOR_IS_LAST()) {
        var = new LgsLoopMetaVar(FOR_IS_LAST);
        var->type = &LGS_BOOL;
    } else {
        assert(0);
    }
    setLocation(var->location, ctx->start);
    return var;
}

LgsType* LgsParserAdapter::getType(LogosParser::TypeContext* ctx) {
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
    setLocation(result->location, ctx->start);
    return result;
}

LgsGroup* LgsParserAdapter::getGroup(LogosParser::GroupContext* ctx) {
    const auto group = new LgsGroup(ctx->IDENTIFIER()->getText());
    setLocation(group->location, ctx->start);
    for (const auto type : ctx->groupTypesList()->type()) {
        const auto lgsType = getType(type);
        group->types.push_back(lgsType);
    }
    for (const auto target : ctx->groupTargetList()->IDENTIFIER()) {
        const auto var = getVariable(target);
        group->targetSymbols.push_back(var);
    }
    globals.addSymbol(LgsSymbol(group), &errHandler);
    return group;
}

LgsFuncType* LgsParserAdapter::getFuncType(LogosParser::FuncTypeContext* ctx) {
    const auto rt = getType(ctx->rt);
    const auto funcType = new LgsFuncType();
    setLocation(funcType->location, ctx->start);
    funcType->rt = rt;
    for (const auto paramType : ctx->type()) {
        if (paramType == ctx->rt) continue;
        const auto type = getType(paramType);
        funcType->params.emplace_back(LgsParam(type));
    }
    return funcType;
}

LgsType* LgsParserAdapter::getArrayType(LogosParser::TypeContext* ctx) {
    LgsType* type = getType(ctx->baseType);
    auto dims = ctx->arraySize();
    for (auto it = dims.rbegin(); it != dims.rend(); ++it) {
        LgsIterable* array;
        if (ctx->EXCLA_MARK()) {
            array = new LgsSArray(type);
        } else {
            array = new LgsDArray(type);
        }
        if (const auto sizeExpr = (*it)->expr()) {
            array->sizeExpr = getExpr(sizeExpr);
        }
        type = array;
    }
    return type;
}

LgsType* LgsParserAdapter::getTypeFromText(antlr4::tree::TerminalNode* ctx) const {
    const auto typeText = ctx->getText();
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
    } else if (typeText == LgsDouble::name) {
        type = &LGS_DOUBLE;
    } else if (typeText == LgsVoid::name) {
        type = &LGS_VOID;
    } else if (typeText == LgsStr::name) {
        type = new LgsStr();
    } else if (typeText.length() == 4 && typeText.substr(0, 3) == "vec") {
        type = new LgsVec(typeText[3] - '0');
    } else {
        type = new LgsUnknown(typeText);
    }
    setLocation(type->location, ctx->getSymbol());
    return type;
}

LgsType* LgsParserAdapter::getFuncReturnType(LogosParser::TypeContext* ctx) {
    LgsType* result = nullptr;
    if (!ctx) {
        result = &LGS_VOID;
    } else {
        result = getType(ctx);
        setLocation(result->location, ctx->start);
    }
    return result;
}

void LgsParserAdapter::addFileSymbol(LgsMainFile* file, const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto globalSymbol = globals.getSymbol(symbolName);
    if (globalSymbol) {
        if (globalSymbol->isBuiltin) {
            return errHandler.addError(E10053, newSymbol.location, {symbolName});
        }
        return errHandler.addError(E10011, newSymbol.location, {symbolName});
    }
    file->symbolTable.addSymbol(newSymbol, &errHandler);
}

bool LgsParserAdapter::isArgsDuplicate(const std::unordered_set<std::string>& initializedArgs, LgsVarDec* varDec) {
    if (initializedArgs.count(varDec->name)) {
        errHandler.addError(E10054, &varDec->location, {varDec->name});
        return true;
    }
    return false;
}

bool LgsParserAdapter::validateTypeName(const std::string& typeName, const LgsLocation* location) {
    if (islower(typeName[0])) {
        errHandler.addError(E10033, location, {typeName});
        return false;
    }
    return true;
}

void LgsParserAdapter::extractStrParts(LgsStrConst& strConst) {
    size_t start = 0;
    std::string replaced = strConst.value;
    while (true) {
        const auto open = replaced.find('{', start);
        if (open == std::string::npos) break;
        const auto close = replaced.find('}', open);
        if (close == std::string::npos) break;
        if (close > open + 1) {
            const auto part = replaced.substr(open + 1, close - open - 1);
            antlr4::ANTLRInputStream input(part);
            LogosLexer lexer(&input);
            antlr4::CommonTokenStream tokens(&lexer);
            LogosParser parser(&tokens);
            const auto expr = getExpr(parser.expr());
            strConst.templateParts.push_back(expr);
        }
        replaced.replace(open, close - open + 1, LGS_STR_FMT_PLACEHOLDER);
        start = open + strlen(LGS_STR_FMT_PLACEHOLDER);
    }
    if (replaced != strConst.value) {
        strConst.formatedStr = strdup(replaced.c_str());
    }
}

bool LgsParserAdapter::checkParserErrors(LogosParser* parser) {
    if (parser->getNumberOfSyntaxErrors() > 0) {
        std::lock_guard lock(mtx);
        errHandler.setUnsuccessful();
        return false;
    }
    return true;
}

void LgsParserAdapter::setLocation(LgsLocation& location, const antlr4::Token* start) const {
    location.lineStart = start->getLine();
    location.posInLine = start->getCharPositionInLine() + 1;
    location.fileID = fileID;
}
