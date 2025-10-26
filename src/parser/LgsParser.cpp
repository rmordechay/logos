#include "parser/LgsParser.h"
#include "exprs/LgsArrayExpr.h"
#include "stmts/LgsAssignment.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsJson.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsCharConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsEnvFile.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsCoroutine.h"
#include "funcs/LgsMainFunc.h"
#include "lgsc/LgsCLang.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "data/LgsTokens.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsNull.h"
#include "exprs/LgsTernaryExpr.h"
#include "files/LgsAppConfigFile.h"
#include "logos/LgsApp.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsGeneric.h"
#include "types/LgsInterface.h"
#include "types/LgsSubType.h"
#include "types/LgsUnknown.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

#define MAX_TOKENS_NUMBER 10000

bool LgsParser::lex() {
    LgsLexer lexer(fileID, filePath, code);
    tokens = lexer.tokenize();
    if (!lexer.errHandler.successful) {
        errHandler.mergeErrors(lexer.errHandler);
        return false;
    }
    if (!tokens.empty()) {
        currentToken = tokens[0];
    }
    return true;
}

LgsFile* LgsParser::parseSrcFile(const bool isTestRun) {
    if (!lex()) return nullptr;
    if (const auto mainFile = parseMainFile()) {
        return mainFile;
    }
    if (const auto objFile = parseObjectFile()) {
        return objFile;
    }
    if (const auto interfaceFile = parseInterfaceFile()) {
        return interfaceFile;
    }
    if (isTestRun) {
        if (const auto testFile = parseTestFile()) {
            return testFile;
        }
    }
    return nullptr;
}

LgsAppConfigFile* LgsParser::parseAppConfigFile() {
    if (!lex()) return nullptr;
    const auto configFile = new LgsAppConfigFile(fileID, filePath);
    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        configFile->configs.push_back(varDec);
        if (currentToken.type == T_EOF) break;
        if (currentToken.lexeme == "required") break;
    }
    if (currentToken.lexeme == "required" && peek().lexeme == "envs") {
        consume();
        consume();
        mustMatch(T_LBRACE);
        while (true) {
            const auto var = parseVariable();
            if (!var) break;
            configFile->requiredEnvs.push_back(var);
            if (currentToken.type != T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    }

    if (currentToken.lexeme == "packages") {
        consume();
        mustMatch(T_LBRACE);
        while (true) {
            const auto name = currentToken.lexeme;
            if (!matchAndConsume(T_STRING)) break;
            const auto version = currentToken.lexeme;
            if (!matchAndConsume(T_STRING)) break;
            const auto alias = parseVariable();
            configFile->packages.emplace_back(LgsImportPackage{name, version, alias});
            if (currentToken.type != T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    }
    return configFile;
}

LgsEnvFile* LgsParser::parseEnvFile() {
    if (!lex()) return nullptr;
    if (currentToken.lexeme != "env") {
        addParsingError();
        return nullptr;
    }
    const auto nameToken = consume();
    const auto file = new LgsEnvFile(fileID, filePath);
    setLocation(file->location, &nameToken);
    file->envName = nameToken.lexeme;
    mustMatch(T_IDENTIFIER);
    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        file->varDecs.push_back(varDec);
    }
    if (currentToken.type != T_EOF) assert(0);
    return file;
}

LgsMainFile* LgsParser::parseMainFile() {
    if (filePath.filename() != LGS_MAIN_FILE) return nullptr;
    auto const file = new LgsMainFile(fileID, filePath);
    setLocation(file->location, &currentToken);
    parseExternalImports(file);
    while (!isEOF()) {
        if (const auto obj = parseObject()) {
            file->objects.push_back(obj);
            addFileSymbol(file, LgsSymbol(obj));
        } else if (const auto interface = parseInterface()) {
            file->interfaces.push_back(interface);
            addFileSymbol(file, LgsSymbol(interface));
        } else if (auto lgsEnum = parseEnum()) {
            file->enums.push_back(lgsEnum);
            addFileSymbol(file, LgsSymbol(lgsEnum));
        } else if (const auto mainFunc = parseMainFunc()) {
            file->funcs[mainFunc->funcType->name] = mainFunc;
        } else if (const auto func = parseFunc()) {
            file->funcs[func->funcType->name] = func;
            addFileSymbol(file, LgsSymbol(func));
        } else if (const auto subType = parseSubtype()) {
            file->subtypes.emplace_back(subType);
            addFileSymbol(file, LgsSymbol(subType));
        } else {
            addParsingError();
            break;
        }
    }
    return file;
}

LgsObjectFile* LgsParser::parseObjectFile() {
    const auto isSingleton = currentToken.type == T_SINGLETON;
    if (currentToken.type != T_OBJECT && !isSingleton) return nullptr;
    const auto nameToken = consume();
    auto const file = new LgsObjectFile(fileID, filePath);
    mustMatch(T_IDENTIFIER);
    const auto withBraces = matchAndConsume(T_LBRACE);
    parseExternalImports(file);
    const auto obj = parseObjectBody(nameToken, isSingleton);
    if (isSingleton) {
        obj->singleton = new LgsInstance(obj);
    }
    if (withBraces) mustMatch(T_RBRACE);
    file->location = obj->location;
    file->obj = obj;
    validateTypeName(obj->name, &obj->location);
    {
        std::lock_guard lock(mtx);
        globals.addSymbol(LgsSymbol(file->obj), &errHandler);
    }
    return file;
}

LgsInterfaceFile* LgsParser::parseInterfaceFile() {
    if (!matchAndConsume(T_INTERFACE)) return nullptr;
    const auto nameToken = currentToken;
    mustMatch(T_IDENTIFIER);
    const auto withBraces = matchAndConsume(T_LBRACE);
    const auto interface = parseInterfaceBody(nameToken);
    if (withBraces) mustMatch(T_RBRACE);
    auto const file = new LgsInterfaceFile(fileID, filePath);
    file->location = interface->location;
    file->interface = interface;
    validateTypeName(interface->name, &interface->location);
    {
        std::lock_guard lock(mtx);
        globals.addSymbol(LgsSymbol(file->interface), &errHandler);
    }
    return file;
}

LgsTestFile* LgsParser::parseTestFile() {
    if (currentToken.lexeme != "test") {
        addParsingError();
        return nullptr;
    }
    const auto nameToken = consume();
    auto const file = new LgsTestFile(fileID, filePath);
    setLocation(file->location, &currentToken);
    mustMatch(T_IDENTIFIER);

    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        file->varDecs.push_back(varDec);
    }

    while (true) {
        const auto func = parseFunc();
        if (!func) break;
        if (startsWith(func->funcType->name, "test")) {
            func->isTest = true;
            file->tests.push_back(func);
        } else {
            file->funcs.push_back(func);
        }
        if (currentToken.type == T_EOF) break;
    }

    if (currentToken.type != T_EOF) assert(0);
    validateTestFolder(file);
    return file;
}

void LgsParser::parseExternalImports(LgsFile* file) {
    if (!matchAndConsume(T_EXTERN)) return;
    const auto langName = currentToken;
    mustMatch(T_IDENTIFIER);
    mustMatch(T_LBRACE);
    while (true) {
        const auto strConst = parseStrConst();
        if (!strConst) break;
        file->externalCPaths.push_back(strConst);
        if (currentToken.type == T_RBRACE) break;
    }
    mustMatch(T_RBRACE);
    LgsCLang lgsCLang(paths);
    lgsCLang.resolveCPaths(file);
    errHandler.mergeErrors(lgsCLang.errHandler);
}

LgsObject* LgsParser::parseObject() {
    const auto isSingleton = currentToken.type == T_SINGLETON;
    if (currentToken.type != T_OBJECT && !isSingleton) return nullptr;
    const auto nameToken = consume();
    mustMatch(T_IDENTIFIER);
    mustMatch(T_LBRACE);
    const auto obj = parseObjectBody(nameToken, isSingleton);
    mustMatch(T_RBRACE);
    validateTypeName(obj->name, &obj->location);
    return obj;
}

LgsInterface* LgsParser::parseInterface() {
    if (!matchAndConsume(T_INTERFACE)) return nullptr;
    const auto nameToken = currentToken;
    mustMatch(T_IDENTIFIER);
    mustMatch(T_LBRACE);
    const auto interface = parseInterfaceBody(nameToken);
    mustMatch(T_RBRACE);
    validateTypeName(interface->name, &interface->location);
    return interface;
}

LgsObject* LgsParser::parseObjectBody(const LgsToken& tokenName, const bool isSingleton) {
    auto const obj = new LgsObject(tokenName.lexeme);
    setLocation(obj->location, &tokenName);

    // Generic types
    if (matchAndConsume(T_TYPE)) {
        mustMatch(T_COLON);
        while (true) {
            const auto type = parseGeneric();
            if (!type) break;
            obj->generics.push_back(type);
            const auto ct = currentToken.type;
            const auto nt = peek().type;
            if (ct == T_EOF || ct == T_RBRACE || nt == T_COLON || nt == T_LPAREN || nt == T_ENUM || nt == T_INTERFACE || nt == T_IMPLEMENTS) break;
            mustMatch(T_COMMA);
        }
    }

    // Implements
    if (matchAndConsume(T_IMPLEMENTS)) {
        mustMatch(T_COLON);
        while (true) {
            const auto type = parseType();
            if (!type) break;
            obj->implements.push_back(type);
            const auto ct = currentToken.type;
            const auto nt = peek().type;
            if (ct == T_EOF || ct == T_RBRACE || nt == T_COLON || nt == T_LPAREN || nt == T_ENUM || nt == T_INTERFACE) break;
            mustMatch(T_COMMA);
        }
    }

    while (true) {
        if (const auto field = parseField()) {
            obj->addField(field);
        } else if (const auto enum_ = parseEnum()) {
            obj->enums.push_back(enum_);
        } else if (const auto subtype = parseSubtype()) {
            obj->subtypes.push_back(subtype);
        } else if (const auto ioPair = parseIOPair()) {
            obj->ioPairs.push_back(ioPair);
        } else {
            break;
        }
    }

    // Methods
    while (true) {
        const auto method = parseMethod(obj);
        if (!method) break;
        obj->addMethod(method);
        if (currentToken.type == T_RBRACE || currentToken.type == T_EOF) break;
    }

    if (isSingleton) {
        obj->singleton = new LgsInstance(obj);
    }

    if (currentToken.type != T_EOF && currentToken.type != T_RBRACE) assert(0);
    return obj;
}

LgsInterface* LgsParser::parseInterfaceBody(const LgsToken& tokenName) {
    auto const interface = new LgsInterface(tokenName.lexeme);
    setLocation(interface->location, &tokenName);

    while (true) {
        const auto field = parseField();
        if (field) interface->addField(field);
        else break;
    }

    while (true) {
        const auto funcHeader = parseFuncHeader();
        if (!funcHeader) break;
        funcHeader->parentName = interface->name;
        const auto method = new LgsFunc(funcHeader);
        method->funcType->isPublic = true;
        method->funcType->isVirtual = true;
        method->stmtsBlock = parseStmtsBlock(false);
        interface->addMethod(method);
        if (currentToken.type == T_RBRACE || currentToken.type == T_EOF) break;
    }

    return interface;
}

LgsGeneric* LgsParser::parseGeneric() {
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    const auto generic = new LgsGeneric(currentToken.lexeme);
    setLocation(generic->location, &currentToken);
    consume();
    return generic;
}

LgsField* LgsParser::parseField() {
    const auto oldIndex = currentIndex;
    auto isConst = false;
    auto isOwner = false;
    auto isPublic = false;

    // Qualifiers
    while (true) {
        if (matchAndConsume(T_OWNER)) {
            if (isOwner) addParsingError();
            isOwner = true;
        } else if (matchAndConsume(T_CONST)) {
            if (isConst) addParsingError();
            isConst = true;
        } else if (matchAndConsume(T_PUBLIC)) {
            if (isPublic) addParsingError();
            isPublic = true;
        } else {
            break;
        }
    }

    const auto nameToken = currentToken;
    if (!matchOrReset(T_IDENTIFIER, oldIndex)) return nullptr;
    if (!matchOrReset(T_COLON, oldIndex)) return nullptr;
    const auto type = parseType();
    if (!parsedOrReset(type, oldIndex)) return nullptr;
    LgsExpr* expr = nullptr;
    if (matchAndConsume(T_EQUAL)) {
        expr = parseExpr();
    }

    const auto field = new LgsField(nameToken.lexeme, type, expr);
    setLocation(field->location, &nameToken);
    field->type = type;
    field->isConst = isConst;
    field->isOwner = isOwner;
    field->isPublic = isPublic;
    return field;
}

LgsIOPair* LgsParser::parseIOPair() {
    if (!matchAndConsume(T_IO)) return nullptr;
    mustMatch(T_LPAREN);
    const auto openingFuncName = currentToken;
    mustMatch(T_IDENTIFIER);
    mustMatch(T_COMMA);
    const auto closingFuncName = currentToken;
    mustMatch(T_IDENTIFIER);
    mustMatch(T_RPAREN);
    const auto ioPair = new LgsIOPair(openingFuncName.lexeme, closingFuncName.lexeme);
    setLocation(ioPair->location, &openingFuncName);
    return ioPair;
}

LgsEnum* LgsParser::parseEnum() {
    if (currentToken.type != T_ENUM) return nullptr;
    const auto nameToken = consume();
    mustMatch(T_IDENTIFIER);
    mustMatch(T_LBRACE);
    const auto enum_ = new LgsEnum(nameToken.lexeme);
    setLocation(enum_->location, &nameToken);
    while (true) {
        const auto enumField = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        LgsExpr* strConst = nullptr;
        if (matchAndConsume(T_EQUAL)) {
            strConst = parseStrConst();
            mustParse(strConst);
        }
        const auto field = new LgsField(enumField.lexeme, enum_, strConst);
        setLocation(field->location, &enumField);
        enum_->addField(field);
        if (currentToken.type == T_RBRACE) break;
    }
    mustMatch(T_RBRACE);
    return enum_;
}

LgsSubType* LgsParser::parseSubtype() {
    if (matchAndConsume(T_TYPE)) {
        const auto lType = currentToken;
        mustMatch(T_IDENTIFIER);
        mustMatch(T_EQUAL);
        const auto rType = parseType();
        mustParse(rType);
        const auto subtype = new LgsSubType(lType.lexeme, rType);
        setLocation(subtype->location, &lType);
        return subtype;
    }
    if (currentToken.type == T_IDENTIFIER && peek().type == T_EQUAL) {
        const auto lType = currentToken;
        consume();
        consume();
        const auto rType = parseType();
        mustParse(rType);
        const auto subtype = new LgsSubType(lType.lexeme, rType);
        setLocation(subtype->location, &lType);
        subtype->isWeakType = true;
        return subtype;
    }
    return nullptr;
}

LgsFuncType* LgsParser::parseFuncType() {
    if (!matchAndConsume(T_LPAREN)) return nullptr;
    const auto funcType = new LgsFuncType();
    setLocation(funcType->location, &currentToken);
    while (true) {
        const auto type = parseType();
        if (!type) break;
        funcType->params.emplace_back(type, "");
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
    }
    if (currentToken.type == T_COMMA) consume();
    mustMatch(T_RPAREN);
    mustMatch(T_COLON);
    funcType->rt = parseType();
    mustParse(funcType->rt);
    return funcType;
}

LgsMap* LgsParser::parseMapType() {
    if (!matchAndConsume(T_LBRACE)) return nullptr;
    const auto mapType = new LgsMap();
    setLocation(mapType->location, &currentToken);
    const auto l = parseType();
    mustParse(l);
    mustMatch(T_COLON);
    const auto r = parseType();
    mustParse(r);
    mustMatch(T_RBRACE);
    mapType->typePair->key = l;
    mapType->typePair->value = r;
    return mapType;
}

LgsType* LgsParser::parseType() {
    const auto firstToken = currentToken;
    LgsType* type = nullptr;
    if (firstToken.type == T_LBRACE) {
        type = parseMapType();
    } else if (firstToken.type == T_LPAREN) {
        type = parseFuncType();
    } else if (firstToken.type == T_IDENTIFIER) {
        const auto typeText = firstToken.lexeme;
        if (typeText == LgsBool::name) type = &LGS_BOOL;
        else if (typeText == LgsChar::name) type = &LGS_CHAR;
        else if (typeText == LgsInt::name) type = &LGS_INT;
        else if (typeText == LgsByte::name) type = &LGS_BYTE;
        else if (typeText == LgsUInt::name) type = &LGS_UINT;
        else if (typeText == LgsShort::name) type = &LGS_SHORT;
        else if (typeText == LgsLong::name) type = &LGS_LONG;
        else if (typeText == LgsSize::name) type = &LGS_SIZE;
        else if (typeText == LgsFloat::name) type = &LGS_FLOAT;
        else if (typeText == LgsDouble::name) type = &LGS_DOUBLE;
        else if (typeText == LgsVoid::name) type = &LGS_VOID;
        else if (typeText == LgsStr::name) type = new LgsStr();
        else if (typeText.length() == 4 && typeText.substr(0, 3) == "vec") type = new LgsVec(typeText[3] - '0');
        else type = new LgsUnknown(typeText);
        setLocation(type->location, &firstToken);
        consume();
    }

    // Iterable
    if (type && currentToken.type == T_LBRACK) {
        while (true) {
            if (!matchAndConsume(T_LBRACK)) break;
            if (const auto size = parseUnary()) {
                type = new LgsSArray(type, size);
            } else {
                type = new LgsDArray(type);
            }
            mustMatch(T_RBRACK);
        }
        setLocation(type->location, &firstToken);
    }

    // Nullable
    if (type && matchAndConsume(T_QUEST_MARK)) {
        type = new LgsNullable(type);
        setLocation(type->location, &firstToken);
    }

    return type;
}

LgsFunc* LgsParser::parseFunc() {
    const auto ft = parseFuncHeader();
    if (!ft) return nullptr;
    const auto func = new LgsFunc(ft);
    func->location = ft->location;
    currentFunc = func;
    func->stmtsBlock = parseStmtsBlock();
    currentFunc = nullptr;
    return func;
}

LgsMainFunc* LgsParser::parseMainFunc() {
    if (currentToken.lexeme != LGS_MAIN_FUNC) return nullptr;
    const auto ft = parseFuncHeader();
    if (!ft) return nullptr;
    const auto func = new LgsMainFunc();
    func->location = ft->location;
    func->funcType->params = ft->params;
    currentFunc = func;
    func->stmtsBlock = parseStmtsBlock();
    currentFunc = nullptr;
    return func;
}

LgsFunc* LgsParser::parseMethod(LgsObject* obj) {
    auto isPublic = false;
    if (matchAndConsume(T_PUBLIC)) {
        isPublic = true;
    }
    const auto funcHeader = parseFuncHeader();
    if (!funcHeader) return nullptr;
    funcHeader->parentName = obj->name;
    const auto func = new LgsFunc(funcHeader);
    currentFunc = func;
    func->location = func->funcType->location;
    func->stmtsBlock = parseStmtsBlock();
    func->funcType->isPublic = isPublic;
    if (func->funcType->isMethod) {
        func->funcType->params.insert(func->funcType->params.begin(), LgsParam(obj, LGS_SELF));
    }
    currentFunc = nullptr;
    return func;
}

LgsFuncType* LgsParser::parseFuncHeader() {
    const auto nameToken = currentToken;
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    if (peek().type != T_LPAREN) return nullptr;
    consume();
    consume();
    const auto funcType = new LgsFuncType();
    setLocation(funcType->location, &nameToken);
    funcType->name = nameToken.lexeme;
    parseParams(funcType);
    mustMatch(T_RPAREN);
    funcType->rt = matchAndConsume(T_COLON) ? parseType() : &LGS_VOID;
    return funcType;
}

void LgsParser::parseParams(LgsFuncType* funcType) {
    if (currentToken.type == T_RPAREN) return;
    while (true) {
        const auto paramName = currentToken;
        mustMatch(T_IDENTIFIER);
        mustMatch(T_COLON);
        const auto type = parseType();
        mustParse(type);
        LgsParam param(type, paramName.lexeme);
        if (matchAndConsume(T_EQUAL)) {
            param.expr = parseExpr();
            mustParse(param.expr);
        }
        setLocation(param.location, &paramName);
        funcType->params.push_back(param);
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
    }
    if (currentToken.type == T_COMMA) consume();
}

LgsStmt* LgsParser::parseStmt() {
    if (const auto ifStmt = parseIfStmt()) return ifStmt;
    if (const auto switchStmt = parseSwitch()) return switchStmt;
    if (const auto forLoop = parseForLoop()) return forLoop;
    if (const auto whileLoop = parseWhileLoop()) return whileLoop;
    if (const auto returnStmt = parseReturnStmt()) return returnStmt;
    if (const auto breakStmt = parseBreakStmt()) return breakStmt;
    if (const auto continueStmt = parseContinueStmt()) return continueStmt;
    if (const auto coroutine = parseCoroutine()) return coroutine;
    if (const auto defer = parseDeferStmt()) return defer;
    if (const auto ioStmt = parseIOStmt()) return ioStmt;
    if (const auto varDec = parseVarDec()) return varDec;
    if (const auto assignment = parseAssignment()) return assignment;
    if (const auto expr = parseExpr(false)) return expr;
    return nullptr;
}

LgsStmtsBlock* LgsParser::parseStmtsBlock(const bool withSingleStmt) {
    LgsStmtsBlock* stmtsBlock = nullptr;
    if (matchAndConsume(T_LBRACE)) {
        stmtsBlock = new LgsStmtsBlock();
        setLocation(stmtsBlock->location, &currentToken);
        while (true) {
            const auto stmt = parseStmt();
            if (!stmt) break;
            stmtsBlock->stmts.push_back(stmt);
            if (currentToken.type == T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    } else if (withSingleStmt) {
        if (const auto stmt = parseStmt()) {
            stmtsBlock = new LgsStmtsBlock();
            stmtsBlock->location = stmt->location;
            stmtsBlock->stmts.push_back(stmt);
            stmtsBlock->location = stmt->location;
        }
    }
    return stmtsBlock;
}

LgsVarDec* LgsParser::parseVarDec() {
    const auto oldIndex = currentIndex;
    auto isConst = false;
    auto isOwner = false;

    while (true) {
        if (matchAndConsume(T_OWNER)) {
            if (isOwner) addParsingError();
            isOwner = true;
        } else if (matchAndConsume(T_CONST)) {
            if (isConst) addParsingError();
            isConst = true;
        } else {
            break;
        }
    }

    const auto nameToken = currentToken;
    if (!matchOrReset(T_IDENTIFIER, oldIndex)) return nullptr;

    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    if (matchAndConsume(T_EQUAL)) {
        expr = parseExpr();
    } else if (matchAndConsume(T_COLON)) {
        type = parseType();
        mustParse(type);
        if (matchAndConsume(T_EQUAL)) {
            expr = parseExpr();
            if (!parsedOrReset(expr, oldIndex)) {
                freeType(type);
                return nullptr;
            }
        }
    } else {
        reset(oldIndex);
        return nullptr;
    }

    const auto varDec = new LgsVarDec(nameToken.lexeme, type, expr);
    setLocation(varDec->location, &nameToken);
    varDec->isConst = isConst;
    varDec->isOwner = isOwner;
    return varDec;
}

LgsStmt* LgsParser::parseAssignment() {
    const auto oldIndex = currentIndex;
    LgsExpr* l = nullptr;
    if (const auto selection = parseSelection()) l = selection;
    else if (const auto variable = parseVariable()) l = variable;
    if (l) {
        if (const auto iterIndex = parseIterIndex(l)) l = iterIndex;
    }

    if (!parsedOrReset(l, oldIndex)) return nullptr;
    const auto opToken = currentToken;
    LgsAssignType op = {};
    switch (opToken.type) {
    case T_WALRUS:
        op = ASSIGN;
        break;
    case T_EQUAL_PLUS:
        op = ASSIGN_ADD;
        break;
    case T_EQUAL_MINUS:
        op = ASSIGN_SUB;
        break;
    case T_EQUAL_STAR:
        op = ASSIGN_MUL;
        break;
    case T_EQUAL_SLASH:
        op = ASSIGN_DIV;
        break;
    case T_EQUAL_PERCENT:
        op = ASSIGN_MOD;
        break;
    case T_EQUAL_AMPERSAND:
        op = ASSIGN_AND;
        break;
    case T_EQUAL_PIPE:
        op = ASSIGN_OR;
        break;
    case T_EQUAL_CARET:
        op = ASSIGN_XOR;
        break;
    case T_EQUAL_DOUBLE_RANGLE:
        op = ASSIGN_LSHIFT;
        break;
    case T_EQUAL_DOUBLE_LANGLE:
        op = ASSIGN_RSHIFT;
        break;
    default:
        freeExpr(l);
        reset(oldIndex);
        return nullptr;
    }
    consume();
    const auto r = parseExpr();
    if (!r) {
        freeExpr(l);
        reset(oldIndex);
        return nullptr;
    }
    const auto assignment = new LgsAssignment(op, l, r);
    setLocation(assignment->location, &opToken);
    return assignment;
}

LgsStmt* LgsParser::parseIfStmt() {
    if (!matchAndConsume(T_IF)) return nullptr;
    const auto condExpr = parseExpr(false);
    mustParse(condExpr);
    const auto ifBlock = parseStmtsBlock();
    mustParse(ifBlock);
    const auto ifStmt = new LgsIfStmt(condExpr, ifBlock);
    while (true) {
        if (!matchAndConsume(T_ELSE)) break;
        if (matchAndConsume(T_IF)) {
            const auto elseCond = parseExpr(false);
            mustParse(elseCond);
            const auto stmtsBlock = parseStmtsBlock();
            mustParse(stmtsBlock);
            ifStmt->elseIfs.push_back(std::make_pair(elseCond, stmtsBlock));
        } else {
            ifStmt->elseBlock = parseStmtsBlock();
            mustParse(ifStmt->elseBlock);
            break;
        }
    }
    return ifStmt;
}

LgsSwitch* LgsParser::parseSwitch() {
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_SWITCH)) return nullptr;
    const auto condExpr = parseExpr(false);
    mustParse(condExpr);
    mustMatch(T_LBRACE);
    const auto switchStmt = new LgsSwitch(condExpr);
    setLocation(switchStmt->location, &tokens[oldIndex]);
    while (true) {
        const auto pattern = parseExpr(false);
        if (!pattern) break;
        if (!mustMatch(T_COLON)) break;
        const auto stmtsBlock = parseStmtsBlock();
        if (!mustParse(stmtsBlock)) break;
        switchStmt->patterns.push_back(std::make_pair(pattern, stmtsBlock));
        if (matchAndConsume(T_ELSE)) {
            mustMatch(T_COLON);
            switchStmt->elseBlock = parseStmtsBlock();
            mustParse(switchStmt->elseBlock);
        }
        if (currentToken.type == T_RBRACE) break;
    }
    mustMatch(T_RBRACE);
    return switchStmt;
}

LgsForLoop* LgsParser::parseForLoop() {
    if (matchAndConsume(T_FOR_EVER)) return parseInfiniteLoop();
    const auto forKeyword = currentToken;
    if (!matchAndConsume(T_FOR)) return nullptr;

    // Consume the first loop expr. After this we could have 3 cases:
    // 1. Next token is T_LBRACE -> for expr {...} (expr can be anything)
    // 2. Next token is T_IN -> for var in iter {...} (var must be a variable)
    // 3. Next token is T_COMMA -> for expr1, expr2, ... in iter {...} (expr1, expr2... must be variables)
    const auto firstExpr = parseUnary();
    mustParse(firstExpr);
    if (currentToken.type == T_LBRACE) {
        // This may turn to ForEachLoop in the sema stage depending on the type of firstExpr.
        const auto forLoop = new LgsRangeLoop(nullptr, firstExpr);
        setLocation(forLoop->location, &forKeyword);
        const auto stmtsBlock = parseStmtsBlock();
        mustParse(stmtsBlock);
        forLoop->stmtsBlock = stmtsBlock;
        return forLoop;
    }

    // At this point we are expecting a loop with an 'in' keyword (only variables are allowed).
    const auto firstLoopVar = firstExpr->asVariable();
    if (!mustParse(firstLoopVar)) return nullptr;
    const auto firstVarName = firstLoopVar->name;
    freeExpr(firstExpr);

    // Multiple loop vars
    std::vector loopVars = {firstVarName};
    if (matchAndConsume(T_COMMA)) {
        while (true) {
            const auto nextToken = consume();
            mustMatch(T_IDENTIFIER);
            loopVars.push_back(currentToken.lexeme);
            if (matchAndConsume(T_COMMA)) continue;
            if (currentToken.type == T_IN) break;
        }
    }

    mustMatch(T_IN);
    LgsForLoop* forLoop = nullptr;
    // Determines if it's a range loop or foreach loop
    if (matchAndConsume(T_DOUBLE_DOT)) {
        const auto toExpr = parseUnary();
        forLoop = new LgsRangeLoop(nullptr, toExpr);
    } else {
        const auto fromExpr = parseUnary();
        if (matchAndConsume(T_DOUBLE_DOT)) {
            const auto toExpr = parseUnary();
            forLoop = new LgsRangeLoop(fromExpr, toExpr);
        } else {
            forLoop = new LgsForeachLoop(fromExpr);
        }
    }

    for (const auto& loopVar : loopVars) {
        forLoop->loopVars.emplace_back(new LgsVarDec(loopVar, nullptr));
    }

    const auto stmtsBlock = parseStmtsBlock();
    mustParse(stmtsBlock);
    setLocation(forLoop->location, &forKeyword);
    forLoop->stmtsBlock = stmtsBlock;
    return forLoop;
}

LgsWhileLoop* LgsParser::parseWhileLoop() {
    if (!matchAndConsume(T_WHILE)) return nullptr;
    auto const whileLoop = new LgsWhileLoop();
    setLocation(whileLoop->location, &currentToken);
    whileLoop->condExpr = parseExpr(false);
    mustParse(whileLoop->condExpr);
    const auto stmtsBlock = parseStmtsBlock();
    mustParse(stmtsBlock);
    whileLoop->stmtsBlock = stmtsBlock;
    return whileLoop;
}

LgsInfiniteLoop* LgsParser::parseInfiniteLoop() {
    const auto stmtsBlock = parseStmtsBlock();
    mustParse(stmtsBlock);
    const auto infiniteLoop = new LgsInfiniteLoop();
    setLocation(infiniteLoop->location, &currentToken);
    infiniteLoop->stmtsBlock = stmtsBlock;
    return infiniteLoop;
}

LgsReturn* LgsParser::parseReturnStmt() {
    if (!matchAndConsume(T_RETURN)) return nullptr;
    const auto expr = parseExpr();
    auto const returnStmt = new LgsReturn(expr);
    setLocation(returnStmt->location, &currentToken);
    return returnStmt;
}

LgsStmt* LgsParser::parseContinueStmt() {
    if (!matchAndConsume(T_CONTINUE)) return nullptr;
    const auto continueStmt = new LgsContinue();
    setLocation(continueStmt->location, &currentToken);
    return continueStmt;
}

LgsBreak* LgsParser::parseBreakStmt() {
    if (!matchAndConsume(T_BREAK)) return nullptr;
    const auto breakStmt = new LgsBreak();
    setLocation(breakStmt->location, &currentToken);
    if (matchAndConsume(T_IF)) {
        breakStmt->isBreakIf = true;
    }
    return breakStmt;
}

LgsCoroutine* LgsParser::parseCoroutine() {
    if (!matchAndConsume(T_GO)) return nullptr;
    const auto expr = parseUnary();
    mustParse(expr);
    const auto coroutine = new LgsCoroutine();
    coroutine->location = expr->location;

    if (const auto funcCall = expr->asFuncCall()) {
        coroutine->funcCall = funcCall;
        coroutine->funcCall->isCoroutine = true;
    } else if (const auto selection = expr->asSelection()) {
        coroutine->selection = selection;
        const auto methodCall = coroutine->selection->asMethodCall();
        if (methodCall) methodCall->isCoroutine = true;
        else addParsingError();
    }

    return coroutine;
}

LgsDeferStmt* LgsParser::parseDeferStmt() {
    if (!matchAndConsume(T_DEFER)) return nullptr;
    const auto expr = parseUnary();
    mustParse(expr);
    const auto deferStmt = new LgsDeferStmt();
    deferStmt->location = expr->location;

    if (const auto funcCall = expr->asFuncCall()) {
        deferStmt->funcCall = funcCall;
        deferStmt->funcCall->isDeferred = true;
    } else if (const auto selection = expr->asSelection()) {
        deferStmt->selection = selection;
        const auto methodCall = deferStmt->selection->asMethodCall();
        if (methodCall) methodCall->isDeferred = true;
        else addParsingError();
    }
    return deferStmt;
}

LgsIOStmt* LgsParser::parseIOStmt() {
    if (!matchAndConsume(T_IO)) return nullptr;
    const auto firstExpr = parseExpr(false);
    mustParse(firstExpr);

    const auto ioStmt = new LgsIOStmt();
    ioStmt->location = firstExpr->location;
    ioStmt->varDec = new LgsVarDec("", nullptr);
    ioStmt->varDec->location = ioStmt->location;
    ioStmt->varDec->isConst = true;
    if (const auto var = firstExpr->asVariable()) {
        ioStmt->varDec->name = var->name;
        if (matchAndConsume(T_COLON)) {
            ioStmt->varDec->type = parseType();
            mustParse(ioStmt->varDec->type);
        }
        mustMatch(T_EQUAL);
        ioStmt->varDec->expr = parseExpr(false);
    } else {
        ioStmt->varDec->expr = firstExpr;
    }
    mustParse(ioStmt->varDec->expr);
    ioStmt->stmtsBlock = parseStmtsBlock();
    mustParse(ioStmt->stmtsBlock);
    return ioStmt;
}

LgsJson* LgsParser::parseJson() {
    return nullptr;
}

LgsExpr* LgsParser::parseExpr(const bool withLambda) {
    if (withLambda) {
        if (const auto lambda = parseLambda()) return lambda;
    }
    const auto expr = parseExprWithPrecedence(0);
    if (matchAndConsume(T_THEN)) {
        const auto thenExpr = parseExpr();
        mustMatch(T_ELSE);
        const auto elseExpr = parseExpr();
        mustParse(elseExpr);
        return new LgsTernaryExpr(expr, thenExpr, elseExpr);
    }
    if (matchAndConsume(T_ARROW)) {
        const auto toType = parseType();
        mustParse(toType);
        const auto cast = new LgsCast(expr, toType);
        cast->location = expr->location;
        return cast;
    }
    return expr;
}

LgsExpr* LgsParser::parseExprWithPrecedence(const int minPrecedence) {
    const auto oldIndex = currentIndex;
    auto left = parseUnary();
    if (!parsedOrReset(left, oldIndex)) return nullptr;
    while (true) {
        const auto op = parseBinaryOp();
        if (op.opType == NOOP) break;
        const auto precedence = getBinOpPrecedence(op.opType);
        if (precedence < minPrecedence) {
            currentToken = tokens[--currentIndex];
            break;
        }
        const auto right = parseExprWithPrecedence(precedence + 1);
        if (!right) {
            addParsingError();
            return left;
        }
        left = new LgsBinaryExpr(left, right, op);
    }
    return left;
}

LgsExpr* LgsParser::parseUnary() {
    LgsExpr* expr = nullptr;
    if (matchAndConsume(T_LPAREN)) {
        expr = parseExprWithPrecedence(0);
        mustMatch(T_RPAREN);
        return expr;
    }
    if (const auto constant = parseConstant()) expr = constant;
    else if (const auto metaVar = parseLoopMetaVar()) return metaVar;
    else if (const auto strConst = parseStrConst()) expr = strConst;
    else if (const auto vector = parseVectorExpr()) expr = vector;
    else if (const auto arrayExpr = parseArrayExpr()) expr = arrayExpr;
    else if (const auto hashMap = parseHashMap()) expr = hashMap;
    else if (const auto json = parseJson()) expr = json;
    else if (const auto prefixExpr = parsePrefixExpr()) expr = prefixExpr;
    else if (const auto funcCall = parseFuncCall()) expr = funcCall;
    else if (const auto instance = parseInstance()) expr = instance;
    else if (const auto variable = parseVariable()) expr = variable;
    else return nullptr;

    if (matchAndConsume(T_DOT)) return parseSelection(expr);
    if (const auto iterIndex = parseIterIndex(expr)) return iterIndex;
    if (const auto postfixExpr = parsePostfixExpr(expr)) return postfixExpr;

    if (matchAndConsume(T_QUEST_MARK)) {
        expr->isNullable = true;
    }
    return expr;
}

LgsBinOp LgsParser::parseBinaryOp() {
    LgsBinOp binOp{NOOP, ""};
    switch (currentToken.type) {
    case T_DOUBLE_EQUAL: binOp.opType = EQ; break;
    case T_NOT_EQUAL: binOp.opType = NE; break;
    case T_GE: binOp.opType = GE; break;
    case T_LE: binOp.opType = LE; break;
    case T_LANGLE: binOp.opType = LT; break;
    case T_RANGLE: binOp.opType = GT; break;
    case T_PLUS: binOp.opType = ADD; break;
    case T_MINUS: binOp.opType = SUB; break;
    case T_STAR: binOp.opType = MUL; break;
    case T_SLASH: binOp.opType = DIV; break;
    case T_PERCENT: binOp.opType = MODULO; break;
    case T_AMPERSAND: binOp.opType = BIT_AND; break;
    case T_PIPE: binOp.opType = BIT_OR; break;
    case T_CARET: binOp.opType = BIT_XOR; break;
    case T_DOUBLE_LANGLE: binOp.opType = LSHIFT; break;
    case T_DOUBLE_RANGLE: binOp.opType = RSHIFT; break;
    case T_IN: binOp.opType = IN; break;
    default: break;
    }
    if (binOp.opType != NOOP) {
        binOp.name = currentToken.lexeme;
        consume();
    }
    return binOp;
}

LgsVariable* LgsParser::parseVariable() {
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    const auto var = new LgsVariable(currentToken.lexeme);
    setLocation(var->location, &currentToken);
    if (var->name == LGS_SELF) {
        currentFunc->funcType->isMethod = true;
    }
    consume();
    return var;
}


LgsInstance* LgsParser::parseInstance() {
    if (currentToken.type != T_INSTANCE) return nullptr;
    const auto tokenName = currentToken;
    if (peek().type != T_LBRACE) return nullptr;
    consume();
    consume();
    const auto instance = new LgsInstance(tokenName.lexeme);
    setLocation(instance->location, &tokenName);
    instance->type = new LgsUnknown(instance->name);

    if (!matchAndConsume(T_RBRACE)) {
        while (true) {
            const auto argNameToken = currentToken;
            if (!mustMatch(T_IDENTIFIER)) break;
            if (!mustMatch(T_EQUAL)) break;
            const auto expr = parseExpr();
            if (!mustParse(expr)) continue;
            if (instance->args.find(argNameToken.lexeme) == instance->args.end()) {
                instance->args[argNameToken.lexeme] = expr;
            } else {
                errHandler.addError(E10054, &expr->location, filePath, {argNameToken.lexeme});
            }
            if (currentToken.type == T_RBRACE) break;
            mustMatch(T_COMMA);
        }
        if (currentToken.type == T_COMMA) consume();
        mustMatch(T_RBRACE);
    }

    return instance;
}

LgsFuncCall* LgsParser::parseFuncCall() {
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    const auto nameToken = currentToken;
    if (peek().type != T_LPAREN) return nullptr;
    consume();
    consume();
    const auto funcCall = new LgsFuncCall(nameToken.lexeme);
    setLocation(funcCall->location, &nameToken);

    if (!matchAndConsume(T_RPAREN)) {
        while (true) {
            const auto expr = parseExpr();
            if (!expr) break;
            funcCall->args.push_back(expr);
            if (currentToken.type == T_RPAREN) break;
            mustMatch(T_COMMA);
        }
        if (currentToken.type == T_COMMA) consume();
        mustMatch(T_RPAREN);
    }
    return funcCall;
}

LgsVectorExpr* LgsParser::parseVectorExpr() {
    const auto oldIndex = currentIndex;
    const auto nameToken = currentToken;
    if (nameToken.type != T_VEC2 && nameToken.type != T_VEC3 && nameToken.type != T_VEC4) return nullptr;
    const auto name = nameToken.lexeme;
    consume();
    if (!mustMatch(T_LPAREN)) return nullptr;

    uint8_t dim = 0;
    switch (nameToken.type) {
    case T_VEC2:
        dim = 2;
        break;
    case T_VEC3:
        dim = 3;
        break;
    case T_VEC4:
        dim = 4;
        break;
    default:
        break;
    }

    std::vector<LgsExpr*> args;
    while (true) {
        const auto expr = parseExpr();
        if (!expr) break;
        args.push_back(expr);
        matchAndConsume(T_COMMA);
    }

    if (!matchOrReset(T_RPAREN, oldIndex)) return nullptr;
    auto const vecExpr = new LgsVectorExpr(dim);
    setLocation(vecExpr->location, &nameToken);
    vecExpr->args = args;
    return vecExpr;
}

LgsStrConst* LgsParser::parseStrConst() {
    if (currentToken.type != T_STRING) return nullptr;
    const auto textToken = currentToken;
    const auto strConst = new LgsStrConst(textToken.lexeme);
    setLocation(strConst->location, &textToken);
    extractStrParts(*strConst);
    consume();
    return strConst;
}

LgsLoopMetaVar* LgsParser::parseLoopMetaVar() {
    const auto metaVarToken = currentToken;
    if (matchAndConsume(T_FOR_I)) {
        const auto metaVar = new LgsLoopMetaVar(metaVarToken.lexeme, FOR_I);
        setLocation(metaVar->location, &metaVarToken);
        metaVar->type = &LGS_SIZE;
        return metaVar;
    }
    if (matchAndConsume(T_FOR_IS_FIRST)) {
        const auto metaVar = new LgsLoopMetaVar(metaVarToken.lexeme, FOR_IS_FIRST);
        setLocation(metaVar->location, &metaVarToken);
        metaVar->type = &LGS_BOOL;
        return metaVar;
    }
    if (matchAndConsume(T_FOR_IS_LAST)) {
        const auto metaVar = new LgsLoopMetaVar(metaVarToken.lexeme, FOR_IS_LAST);
        setLocation(metaVar->location, &metaVarToken);
        metaVar->type = &LGS_BOOL;
        return metaVar;
    }
    return nullptr;
}

LgsExpr* LgsParser::parseConstant() {
    const auto tokenStr = currentToken.lexeme;
    LgsExpr* constant = nullptr;
    switch (currentToken.type) {
    case T_INTEGER: {
        std::string result = tokenStr;
        result.erase(remove(result.begin(), result.end(), '_'), result.end());
        char* end;
        const auto longValue = strtol(result.c_str(), &end, 10);
        if (longValue >= INT_MIN && longValue <= INT_MAX) {
            const auto intValue = static_cast<int>(longValue);
            constant = new LgsIntConst(&LGS_INT, intValue);
        } else {
            constant = new LgsIntConst(&LGS_LONG, longValue);
        }
        break;
    }
    case T_LONG: {
        constant = new LgsIntConst(&LGS_LONG, std::stol(tokenStr));
        break;
    }
    case T_FLOAT: {
        const auto value = std::stof(tokenStr);
        constant = new LgsFloatConst(&LGS_FLOAT, value);
        break;
    }
    case T_BOOL: {
        const auto value = tokenStr == LgsBool::trueLiteral;
        constant = new LgsIntConst(&LGS_BOOL, value);
        break;
    }
    case T_NULL: {
        constant = new LgsNull();
        break;
    }
    default:
        return nullptr;
    }
    setLocation(constant->location, &currentToken);
    consume();
    return constant;
}

LgsArrayExpr* LgsParser::parseArrayExpr() {
    const auto oldIndex = currentIndex;
    const auto isSet = matchAndConsume(T_SET);
    if (isSet) mustMatch(T_LBRACK);
    else if (!matchAndConsume(T_LBRACK)) return nullptr;

    std::vector<LgsExpr*> args;
    while (true) {
        const auto expr = parseExpr();
        if (!expr) break;
        args.push_back(expr);
        matchAndConsume(T_COMMA);
    }
    mustMatch(T_RBRACK);

    auto const arrExpr = new LgsArrayExpr();
    if (isSet) {
        arrExpr->type = new LgsSet();
    } else {
        arrExpr->type = new LgsDArray();
    }
    arrExpr->elements = args;
    setLocation(arrExpr->location, &tokens[oldIndex]);
    return arrExpr;
}

LgsHashMap* LgsParser::parseHashMap() {
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_LBRACE)) return nullptr;

    std::vector<LgsPair> pairs;
    if (!matchAndConsume(T_RBRACE)) {
        while (true) {
            const auto key = parseExpr();
            mustParse(key);
            mustMatch(T_COLON);
            const auto value = parseExpr();
            mustParse(value);
            pairs.push_back(LgsPair{key, value});
            if (currentToken.type == T_RBRACE) break;
            mustMatch(T_COMMA);
        }
        if (currentToken.type == T_COMMA) consume();
        mustMatch(T_RBRACE);
    }

    auto const hashMap = new LgsHashMap();
    setLocation(hashMap->location, &tokens[oldIndex]);
    hashMap->pairs = pairs;
    return hashMap;
}

LgsFunc* LgsParser::parseLambda() {
    const auto oldIndex = currentIndex;
    LgsType* rt = nullptr;
    std::vector<LgsParam> params;

    if (currentToken.type == T_IDENTIFIER) { // Single param
        LgsParam param(nullptr, currentToken.lexeme);
        consume();
        if (matchAndConsume(T_COLON)) {
            param.type = parseType();
            mustParse(param.type);
        }
        params.emplace_back(param);
    } else if (matchAndConsume(T_LPAREN)) { // Multiple params
        if (!matchAndConsume(T_RPAREN)) {
            while (true) {
                auto paramName = currentToken.lexeme;
                consume();
                LgsType* paramType = nullptr;
                if (matchAndConsume(T_COLON)) {
                    paramType = parseType();
                    mustParse(paramType);
                }
                params.emplace_back(paramType, paramName);
                if (currentToken.type == T_RPAREN) break;
                mustMatch(T_COMMA);
            }
            mustMatch(T_RPAREN);
        }
    } else {
        return nullptr;
    }

    if (!matchOrReset(T_DARROW, oldIndex)) {
        freeParams(params);
        freeType(rt);
        return nullptr;
    }

    const auto lambda = new LgsFunc("", rt, params);
    currentFunc = lambda;
    setLocation(lambda->location, &tokens[oldIndex]);
    lambda->stmtsBlock = parseStmtsBlock();
    mustParse(lambda->stmtsBlock);
    lambda->isLambda = true;
    currentFunc = nullptr;
    return lambda;
}

LgsExpr* LgsParser::parsePrefixExpr() {
    LgsPrefixOperator op;
    const auto opToken = currentToken;
    if (opToken.type == T_NOT) {
        op = NOT_PREFIX;
    } else if (opToken.type == T_MINUS) {
        op = MINUS_PREFIX;
    } else if (opToken.type == T_SLIDER) {
        op = SQRT_PREFIX;
    } else {
        return nullptr;
    }
    consume();
    const auto expr = parseUnary();
    if (!expr) return nullptr;
    auto const prefixExpr = new LgsPrefixExpr(expr, op);
    setLocation(prefixExpr->location, &opToken);
    return prefixExpr;
}

LgsIterIndex* LgsParser::parseIterIndex(LgsExpr* baseExpr) {
    if (!matchAndConsume(T_LBRACK)) return nullptr;
    const auto indexExpr = parseExpr(false);
    mustParse(indexExpr);
    LgsExpr* toExpr = nullptr;
    if (matchAndConsume(T_COLON)) {
        toExpr = parseExpr(false);
    }
    mustMatch(T_RBRACK);
    const auto iterIndex = new LgsIterIndex(baseExpr, indexExpr, toExpr);
    iterIndex->location = baseExpr->location;
    if (currentToken.type == T_LBRACK) return parseIterIndex(iterIndex);
    return iterIndex;
}

LgsPostfixExpr* LgsParser::parsePostfixExpr(LgsExpr* baseExpr) {
    LgsPostfixOperator op;
    if (matchAndConsume(T_INC)) {
        op = INC;
    } else if (matchAndConsume(T_DEC)) {
        op = DEC;
    } else {
        return nullptr;
    }
    auto const postfixExpr = new LgsPostfixExpr(baseExpr, op);
    postfixExpr->location = postfixExpr->baseExpr->location;
    return postfixExpr;
}

LgsSelection* LgsParser::parseSelection(LgsExpr* firstExpr) {
    const auto oldIndex = currentIndex;
    std::vector<LgsExpr*> exprs;
    if (firstExpr) exprs.push_back(firstExpr);
    while (true) {
        LgsExpr* expr = nullptr;
        if (const auto funcCall = parseFuncCall()) expr = funcCall;
        else if (const auto variable = parseVariable()) expr = variable;
        if (expr) {
            if (const auto iterIndex = parseIterIndex(expr)) expr = iterIndex;
        }
        exprs.push_back(expr);
        if (!matchAndConsume(T_DOT)) break;
    }
    if (exprs.empty()) {
        reset(oldIndex);
        return nullptr;
    }
    if (exprs.size() == 1) {
        if (!firstExpr) freeExpr(exprs.front());
        reset(oldIndex);
        return nullptr;
    }
    auto const selection = new LgsSelection(exprs);
    selection->location = selection->exprs.front()->location;
    return selection;
}

bool LgsParser::validateTypeName(const std::string& typeName, const LgsLocation* location) {
    if (islower(typeName[0])) {
        errHandler.addError(E10033, location, filePath, {typeName});
        return false;
    }
    return true;
}

void LgsParser::addFileSymbol(LgsMainFile* file, const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto globalSymbol = globals.getSymbol(symbolName);
    if (globalSymbol) {
        if (globalSymbol->isBuiltin) {
            return errHandler.addError(E10053, newSymbol.location, filePath, {symbolName});
        }
        return errHandler.addError(E10011, newSymbol.location, filePath, {symbolName});
    }
    file->symbolTable.addSymbol(newSymbol, &errHandler);
}

void LgsParser::setLocation(LgsLocation& location, const LgsToken* token) const {
    location.fileID = fileID;
    location.lineStart = token->location.lineStart;
    location.columnStart = token->location.columnStart;
}

void LgsParser::extractStrParts(LgsStrConst& strConst) {
    size_t start = 0;
    std::string replaced = strConst.value;
    while (true) {
        const auto open = replaced.find("${", start);
        if (open == std::string::npos) break;
        const auto close = replaced.find('}', open);
        if (close == std::string::npos) break;
        if (close <= open + 2) {
            addParsingError();
            return;
        }
        const auto part = replaced.substr(open + 2, close - 2);
        LgsParser parser(fileID, filePath, paths, globals, part);
        const auto expr = parser.parseExpr();
        strConst.parts.push_back(expr);
        replaced.replace(open, close + 1, LGS_STR_FMT_PLACEHOLDER);
        start = open + strlen(LGS_STR_FMT_PLACEHOLDER);
    }
    if (replaced != strConst.value) {
        strConst.formatedStr = replaced;
    }
}

int LgsParser::getBinOpPrecedence(const LgsBinOpType opType) {
    switch (opType) {
    case BIT_OR: return 1;
    case BIT_XOR: return 2;
    case BIT_AND: return 3;
    case EQ:
    case NE: return 4;
    case LT:
    case GT:
    case LE:
    case GE:
    case IN: return 5;
    case LSHIFT:
    case RSHIFT: return 6;
    case ADD:
    case SUB: return 7;
    case MUL:
    case DIV:
    case MODULO: return 8;
    case NOOP:
    default: return 0;
    }
}

bool LgsParser::isEOF() {
    recursionGuard();
    return currentToken.type == T_EOF;
}

void LgsParser::reset(const size_t index) {
    currentIndex = index;
    currentToken = tokens[currentIndex];
}

LgsToken LgsParser::consume() {
    if (!isEOF()) {
        currentIndex++;
        currentToken = tokens[currentIndex];
    }
    return tokens[currentIndex];
}

LgsToken LgsParser::peek(const size_t i) {
    recursionGuard();
    const auto index = currentIndex + i;
    if (tokens.size() <= index) return tokens.back();
    return tokens[index];
}

bool LgsParser::matchAndConsume(const LgsTokenType token) {
    if (currentToken.type == token) {
        consume();
        return true;
    }
    return false;
}

bool LgsParser::matchOrReset(const LgsTokenType t2, const size_t resetIndex) {
    recursionGuard();
    if (currentToken.type == t2) {
        consume();
        return true;
    }
    reset(resetIndex);
    return false;
}

bool LgsParser::mustMatch(const LgsTokenType t2) {
    recursionGuard();
    if (currentToken.type == t2) {
        consume();
        return true;
    }
    addParsingError();
    return false;
}

bool LgsParser::mustParse(const void* value) {
    recursionGuard();
    if (value) return true;
    addParsingError();
    return false;
}

bool LgsParser::parsedOrReset(const void* value, const size_t resetIndex) {
    recursionGuard();
    if (value) return true;
    reset(resetIndex);
    return false;
}

void LgsParser::addParsingError() {
    const auto token = tokens[currentIndex];
    return errHandler.addError(E10085, &token.location, filePath, {});
}

void LgsParser::recursionGuard() {
    if (recursionCount++ >= MAX_TOKENS_NUMBER) {
        std::cout << "recursion" << '\n';
        exit(EXIT_FAILURE);
    }
}

void LgsParser::validateTestFolder(const LgsFile* testFile) {
    bool foundTestsFolder = false;
    auto currentPath = testFile->absPath.parent_path();
    while (currentPath != paths.rootPath && currentPath.has_parent_path()) {
        if (currentPath.filename() == "tests") {
            foundTestsFolder = true;
            break;
        }
        currentPath = currentPath.parent_path();
    }
    if (!foundTestsFolder) {
        errHandler.addError(E10079, &testFile->location, filePath, {testFile->absPath.filename()});
    }
}
