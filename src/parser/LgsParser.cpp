#include "parser/LgsParser.h"
#include "data/LgsCliErrors.h"
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
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "data/LgsTokens.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsEnvVar.h"
#include "exprs/LgsNull.h"
#include "exprs/LgsTernaryExpr.h"
#include "files/LgsAppConfigFile.h"
#include "lgsc/LgsCLang.h"
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
#include "types/LgsGenericType.h"
#include "types/LgsInterface.h"
#include "types/LgsSelf.h"
#include "types/LgsSubType.h"
#include "types/LgsUnknown.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"
#include "types/primitives/LgsULong.h"
#include <iostream>
#include <unordered_set>

#define MAX_TOKENS_NUMBER 100000
LgsFunc* wrapStmtsBlockWithFunc(LgsStmtsBlock* stmtsBlock);

bool LgsParser::scanTokens() {
    if (code == "") {
        assert(metadata->path != "");
        code = getFileText(metadata->path);
    }
    assert(!code.empty());
    LgsLexer lexer(metadata->path, code);
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
    if (!scanTokens()) return nullptr;
    while (true) {
        if (currentToken.type != T_IMPORT) break;
        parseImports();
    }
    LgsFile* file = nullptr;
    if (const auto mainFile = parseMainFile()) {
        file = mainFile;
    }
    if (const auto objFile = parseObjectFile()) {
        file = objFile;
    }
    if (const auto interfaceFile = parseInterfaceFile()) {
        file = interfaceFile;
    }
    if (isTestRun) {
        if (const auto testFile = parseTestFile()) {
            file = testFile;
        }
    }
    file->symbolTable.cImports = cImports;
    assert(file);
    return file;
}

LgsFile* LgsParser::parseSrcFileHeaders() {
    if (!scanTokens()) return nullptr;
    if (const auto objFile = parseObjectFile()) {
        return objFile;
    }
    if (const auto interfaceFile = parseInterfaceFile()) {
        return interfaceFile;
    }
    return nullptr;
}

LgsEnvFile* LgsParser::parseEnvFile() {
    if (!scanTokens()) return nullptr;
    if (currentToken.lexeme != "env") {
        addParsingError();
        return nullptr;
    }
    const auto nameToken = consume();
    const auto file = new LgsEnvFile(metadata->path);
    setLocation(file->location, &nameToken);
    file->name = nameToken.lexeme;
    mustMatch(T_IDENTIFIER);
    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        file->varDecs.push_back(varDec);
    }
    if (currentToken.type != T_EOF)
        assert(0);
    return file;
}

LgsMainFile* LgsParser::parseMainFile() {
    if (metadata->path.filename() != LGS_MAIN_FILE) return nullptr;
    const auto file = new LgsMainFile(metadata->path);
    setLocation(file->location, &currentToken);
    while (!isEOF()) {
        if (const auto obj = parseObject()) {
            file->objects.push_back(obj);
            if (obj->singleton) {
                globals.table.addSymbol(LgsSymbol(obj), &errHandler, metadata->path);
            } else {
                addFileSymbol(file, LgsSymbol(obj));
            }
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

LgsAppConfigFile* LgsParser::parseAppConfigFile() {
    if (!scanTokens()) return nullptr;
    const auto file = new LgsAppConfigFile(metadata->path);
    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        file->configs.push_back(varDec);
        if (currentToken.type == T_EOF) break;
        if (currentToken.lexeme == "required") break;
    }

    if (currentToken.lexeme == "required" && peek().lexeme == LGS_ENVS_DIR) {
        consume(2);
        mustMatch(T_LBRACE);
        if (!matchAndConsume(T_RBRACE)) {
            while (true) {
                const auto var = currentToken;
                if (!mustMatch(T_IDENTIFIER)) break;
                if (!mustMatch(T_COLON)) break;
                const auto type = parseType();
                mustParse(type);
                auto varDec = new LgsVarDec(var.lexeme, type, nullptr);
                setLocation(varDec->location, &var);
                file->requiredEnvs.push_back(varDec);
                if (currentToken.type == T_RBRACE) break;
            }
            mustMatch(T_RBRACE);
        }
    }

    if (currentToken.lexeme == "packages") {
        consume();
        mustMatch(T_LBRACE);
        while (true) {
            const auto importName = currentToken;
            if (!matchAndConsume(T_STRING)) break;
            LgsImportPackage importPackage;
            parsePackageString(importPackage, importName);
            importPackage.alias = parseVariable();
            file->packages.emplace_back(importPackage);
            if (currentToken.type != T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    }
    return file;
}

LgsObjectFile* LgsParser::parseObjectFile() {
    const auto isSingleton = currentToken.type == T_SINGLETON;
    if (currentToken.type != T_OBJECT && !isSingleton) return nullptr;
    const auto nameToken = consume();
    const auto file = new LgsObjectFile(metadata->path);
    mustMatch(T_IDENTIFIER);
    const auto withBraces = matchAndConsume(T_LBRACE);
    const auto obj = parseObjectBody(nameToken, isSingleton);
    if (!mustParse(obj)) return file;
    if (withBraces) mustMatch(T_RBRACE);
    validateTypeName(obj->name, &obj->location);
    file->obj = obj;
    file->location = obj->location;
    for (const auto innerObj : obj->objects) {
        file->symbolTable.addSymbol(LgsSymbol(innerObj), &errHandler, metadata->path);
    }
    {
        std::lock_guard lock(mtx);
        globals.table.addSymbol(LgsSymbol(file->obj), &errHandler, metadata->path);
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
    const auto file = new LgsInterfaceFile(metadata->path);
    file->location = interface->location;
    file->interface = interface;
    validateTypeName(interface->name, &interface->location);
    {
        std::lock_guard lock(mtx);
        globals.table.addSymbol(LgsSymbol(file->interface), &errHandler, metadata->path);
    }
    return file;
}

LgsTestFile* LgsParser::parseTestFile() {
    if (currentToken.lexeme != "test") {
        addParsingError();
        return nullptr;
    }
    const auto nameToken = consume();
    auto const file = new LgsTestFile(metadata->path);
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
        if (func->funcType->name.starts_with("test")) {
            func->isTest = true;
            file->tests.push_back(func);
        } else {
            file->funcs.push_back(func);
        }
        if (currentToken.type == T_EOF) break;
    }

    if (currentToken.type != T_EOF)
        assert(0);
    validateTestFolder(file);
    return file;
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
            const auto type = parseBaseGeneric();
            if (!type) break;
            obj->generics.push_back(type);
            const auto ct = currentToken.type;
            const auto nt = peek().type;
            if (ct == T_EOF || ct == T_RBRACE || nt == T_COLON || nt == T_LPAREN ||
                nt == T_ENUM || nt == T_INTERFACE || nt == T_IMPLEMENTS) break;
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
            if (ct == T_EOF || ct == T_RBRACE || nt == T_COLON ||
                nt == T_LPAREN || nt == T_ENUM || nt == T_INTERFACE) break;
            mustMatch(T_COMMA);
        }
    }

    auto fieldPosition = 0;
    while (true) {
        if (const auto field = parseField(fieldPosition)) {
            fieldPosition++;
            if (headersOnly && !field->isPublic) continue;
            field->parentType = obj;
            obj->addField(field);
        } else if (const auto innerObj = parseObject()) {
            obj->objects.push_back(innerObj);
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
        if (headersOnly && !method->funcType->isPublic) continue;
        obj->addMethod(method);
        if (currentToken.type == T_RBRACE || currentToken.type == T_EOF) break;
    }

    if (isSingleton) {
        obj->singleton = new LgsInstance(obj);
    }

    if (!headersOnly && currentToken.type != T_EOF && currentToken.type != T_RBRACE) {
        assert(0);
    }
    return obj;
}

LgsInterface* LgsParser::parseInterfaceBody(const LgsToken& tokenName) {
    auto const interface = new LgsInterface(tokenName.lexeme);
    setLocation(interface->location, &tokenName);

    auto fieldPosition = 0;
    while (true) {
        if (const auto field = parseField(fieldPosition)) {
            fieldPosition++;
            field->isVirtual = true;
            interface->addField(field);
        } else {
            break;
        }
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

LgsGenericType* LgsParser::parseBaseGeneric() {
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    const auto generic = new LgsGenericType(currentToken.lexeme);
    setLocation(generic->location, &currentToken);
    consume();
    return generic;
}

LgsField* LgsParser::parseField(const size_t fieldPosition) {
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
    field->setType(type);
    field->position = fieldPosition;
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
    auto position = 0;
    while (true) {
        const auto enumField = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        LgsExpr* expr = nullptr;
        if (matchAndConsume(T_EQUAL)) {
            expr = parseExpr();
            mustParse(expr);
        }
        const auto field = new LgsField(enumField.lexeme, enum_, expr);
        field->isEnumField = true;
        field->position = position++;
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
        consume(2);
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
    const auto startToken = currentToken;
    LgsType* type = nullptr;
    if (startToken.type == T_LBRACE) {
        type = parseMapType();
    } else if (startToken.type == T_LPAREN) {
        type = parseFuncType();
    } else if (currentToken.type == T_SELF_CLASS) {
        type = new LgsSelf(startToken.lexeme);
        consume();
    } else if (startToken.type == T_IDENTIFIER) {
        const auto typeText = startToken.lexeme;
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
        setLocation(type->location, &startToken);
        consume();
    }

    // Iterable
    if (type && currentToken.type == T_LBRACK) {
        while (true) {
            if (!matchAndConsume(T_LBRACK)) break;
            if (const auto size = parseUnary(false)) {
                type = new LgsSArray(type, size);
            } else {
                type = new LgsDArray(type);
            }
            mustMatch(T_RBRACK);
        }
        setLocation(type->location, &startToken);
    }

    // Nullable
    if (type && matchAndConsume(T_QUEST_MARK)) {
        type = new LgsNullable(type);
        setLocation(type->location, &startToken);
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
    if (!headersOnly) {
        func->stmtsBlock = parseStmtsBlock();
    }
    func->funcType->isPublic = isPublic;
    if (func->funcType->isMethod) {
        func->funcType->params.insert(func->funcType->params.begin(), LgsParam(obj, LGS_SELF));
        func->funcType->params.front().isSelf = true;
    }
    currentFunc = nullptr;
    return func;
}

LgsFuncType* LgsParser::parseFuncHeader() {
    const auto nameToken = currentToken;
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    std::vector<LgsGenericType*> generics;
    if (peek().type == T_LANGLE) {
        consume(2);
        while (true) {
            const auto type = parseBaseGeneric();
            if (!type) break;
            generics.push_back(type);
            if (currentToken.type == T_RANGLE) break;
        }
        mustMatch(T_RANGLE);
        mustMatch(T_LPAREN);
    } else if (peek().type != T_LPAREN) {
        return nullptr;
    } else {
        consume(2);
    }

    const auto funcType = new LgsFuncType();
    setLocation(funcType->location, &nameToken);
    funcType->name = nameToken.lexeme;
    funcType->generics = generics;
    parseParams(funcType);
    mustMatch(T_RPAREN);
    funcType->rt = matchAndConsume(T_COLON) ? parseType() : &LGS_VOID;
    return funcType;
}

void LgsParser::parseParams(LgsFuncType* funcType) {
    if (currentToken.type == T_RPAREN) return;
    auto paramIndex = 0;
    while (true) {
        const auto paramName = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        if (currentToken.type == T_COLON) {
            consume();
        } else if (currentToken.type != T_LPAREN) {
            addParsingError();
            break;
        }
        const auto type = parseType();
        mustParse(type);
        LgsParam param(type, paramName.lexeme);
        param.index = paramIndex;
        setLocation(param.location, &paramName);
        if (matchAndConsume(T_TRIPLE_DOT)) {
            if (funcType->isVariadic) addParsingError();
            param.isVariadic = true;
            funcType->isVariadic = true;
        } else if (funcType->isVariadic) {
            // Normal param cannot come after variadic param
            addParsingError();
        } else if (matchAndConsume(T_EQUAL)) {
            param.expr = parseExpr();
            mustParse(param.expr);
            funcType->hasDefaults = true;
        }
        paramIndex++;
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
    if (const auto assignOrExpr = parseAssignOrExpr()) return assignOrExpr;
    return nullptr;
}

LgsStmtsBlock* LgsParser::parseStmtsBlock(const bool withSingleStmt) {
    LgsStmtsBlock* stmtsBlock = nullptr;
    if (matchAndConsume(T_LBRACE)) {
        stmtsBlock = new LgsStmtsBlock();
        setLocation(stmtsBlock->location, &currentToken);
        if (!matchAndConsume(T_RBRACE)) {
            while (true) {
                if (const auto stmt = parseStmt()) {
                    stmtsBlock->stmts.push_back(stmt);
                } else {
                    break;
                }
                if (currentToken.type == T_RBRACE) break;
            }
            mustMatch(T_RBRACE);
        }
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
    if (isConst || isOwner) {
        mustMatch(T_IDENTIFIER);
    } else if (!matchOrReset(T_IDENTIFIER, oldIndex)) {
        return nullptr;
    }

    LgsExpr* expr = nullptr;
    LgsType* type = nullptr;
    if (matchAndConsume(T_EQUAL)) {
        expr = parseExpr();
    } else if (matchAndConsume(T_COLON)) {
        type = parseType();
        mustParse(type);
        if (matchAndConsume(T_EQUAL)) {
            expr = parseExpr();
            mustParse(expr);
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

LgsAssignType LgsParser::parseAssignType() {
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
        return ASSIGN_UNKNOWN;
    }
    consume();
    return op;
}

LgsStmt* LgsParser::parseAssignOrExpr() {
    const auto oldIndex = currentIndex;
    const auto varDec = parseVarDec();
    if (varDec) return varDec;

    // Assignment
    const auto l = parseExpr();
    if (!parsedOrReset(l, oldIndex)) return nullptr;
    const auto opToken = currentToken;
    const auto op = parseAssignType();
    if (op != ASSIGN_UNKNOWN) {
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
    // Return expr
    return l;
}

LgsStmt* LgsParser::parseIfStmt() {
    if (!matchAndConsume(T_IF)) return nullptr;
    if (currentToken.type == T_LBRACE) return parseBoolSwitch();
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
    const auto condExpr = parseUnary(false);
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

LgsStmt* LgsParser::parseBoolSwitch() {
    const auto startToken = currentToken;
    mustMatch(T_LBRACE);
    const auto condExpr = parseExpr(false);
    mustParse(condExpr);
    mustMatch(T_COLON);
    const auto ifBlock = parseStmtsBlock();
    mustParse(ifBlock);
    const auto ifStmt = new LgsIfStmt(condExpr, ifBlock);
    setLocation(ifStmt->location, &startToken);
    ifStmt->isSwitchBool = true;
    while (true) {
        const auto pattern = parseExpr(false);
        if (!pattern) break;
        mustMatch(T_COLON);
        const auto stmtsBlock = parseStmtsBlock();
        mustParse(stmtsBlock);
        if (currentToken.type == T_RBRACE) break;
    }
    mustMatch(T_RBRACE);
    return ifStmt;
}

LgsForLoop* LgsParser::parseForLoop() {
    if (matchAndConsume(T_FOR_EVER)) return parseInfiniteLoop();
    const auto forKeyword = currentToken;
    if (!matchAndConsume(T_FOR)) return nullptr;

    // Consume the first loop expr. After this we could have 3 cases:
    // 1. Next token is T_LBRACE -> for expr {...} (expr can be anything)
    // 2. Next token is T_IN -> for var in iter {...} (var must be a variable)
    // 3. Next token is T_COMMA -> for expr1, expr2, ... in iter {...} (expr1, expr2... must be variables)
    const auto firstExpr = parseUnary(false);
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
        const auto toExpr = parseUnary(false);
        assert(!toExpr->asInstance());
        forLoop = new LgsRangeLoop(nullptr, toExpr);
    } else {
        const auto fromExpr = parseUnary(false);
        assert(!fromExpr->asInstance());
        if (matchAndConsume(T_DOUBLE_DOT)) {
            const auto toExpr = parseUnary(false);
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
    whileLoop->condExpr = parseUnary(false);
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
    const auto goToken = currentToken;
    if (!matchAndConsume(T_GO)) return nullptr;

    LgsExpr* expr = nullptr;
    if (const auto stmtsBlock = parseStmtsBlock(false)) {
        const auto fc = new LgsFuncCall("");
        setLocation(fc->location, &goToken);
        fc->func = wrapStmtsBlockWithFunc(stmtsBlock);
        fc->setType(&LGS_VOID);
        expr = fc;
    } else {
        expr = parseUnary(false);
    }
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
    const auto deferToken = currentToken;
    if (!matchAndConsume(T_DEFER)) return nullptr;

    LgsExpr* expr = nullptr;
    if (const auto stmtsBlock = parseStmtsBlock(false)) {
        const auto fc = new LgsFuncCall("");
        setLocation(fc->location, &deferToken);
        fc->func = wrapStmtsBlockWithFunc(stmtsBlock);
        fc->setType(&LGS_VOID);
        expr = fc;
    } else {
        expr = parseUnary(false);
    }
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
            ioStmt->varDec->setType(parseType());
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

LgsExpr* LgsParser::parseExpr(const bool withLambda) {
    if (withLambda) {
        if (const auto lambda = parseLambda()) return lambda;
    }
    const auto startIndex = currentToken;
    const auto expr = parseExprWithPrecedence(0);
    if (matchAndConsume(T_THEN)) {
        const auto thenExpr = parseExpr();
        mustMatch(T_ELSE);
        const auto elseExpr = parseExpr();
        mustParse(elseExpr);
        const auto ternaryExpr = new LgsTernaryExpr(expr, thenExpr, elseExpr);
        setLocation(ternaryExpr->location, &startIndex);
        return ternaryExpr;
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
        auto const it = LGS_BINARY_OPS.find(currentToken.type);
        if (it == LGS_BINARY_OPS.end()) break;
        consume();
        const auto& [opType, _] = it->second;
        const auto precedence = getBinOpPrecedence(opType);
        if (precedence < minPrecedence) {
            currentToken = tokens[--currentIndex];
            break;
        }
        const auto right = parseExprWithPrecedence(precedence + 1);
        if (!right) {
            addParsingError();
            return left;
        }
        left = new LgsBinaryExpr(left, right, it->second);
    }
    return left;
}

LgsExpr* LgsParser::parseUnary(const bool withInstance) {
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
    else if (const auto envVar = parseEnvVar()) expr = envVar;
    else if (const auto arrayExpr = parseArrayExpr()) expr = arrayExpr;
    else if (const auto hashMap = parseHashMap()) expr = hashMap;
    else if (const auto json = parseJson()) expr = json;
    else if (const auto prefixExpr = parsePrefixExpr()) expr = prefixExpr;
    else if (const auto funcCall = parseFuncCall()) expr = funcCall;
    else if (withInstance && ((expr = parseInstance()))) {
    } else if (const auto variable = parseVariable()) expr = variable;
    else return nullptr;

    if (matchAndConsume(T_DOT)) return parseSelection(expr);
    if (const auto iterIndex = parseIterIndex(expr)) return iterIndex;
    if (const auto postfixExpr = parsePostfixExpr(expr)) return postfixExpr;

    if (matchAndConsume(T_QUEST_MARK)) {
        expr->isNullable = true;
    }
    return expr;
}

LgsVariable* LgsParser::parseVariable() {
    LgsVariable* var = nullptr;
    if (currentToken.type == T_IDENTIFIER) {
        var = new LgsVariable(currentToken.lexeme);
    } else if (currentToken.type == T_SELF_INSTANCE) {
        var = new LgsVariable(currentToken.lexeme);
        currentFunc->funcType->isMethod = true;
    } else {
        return nullptr;
    }
    consume();
    setLocation(var->location, &currentToken);
    return var;
}

void LgsParser::parseArgs(LgsInstance* instance) {
    if (currentToken.type == T_RBRACE) return;
    std::unordered_set<std::string> seen;
    while (true) {
        const auto argNameToken = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        if (!mustMatch(T_EQUAL)) break;
        const auto expr = parseExpr();
        if (!mustParse(expr)) continue;
        auto argName = argNameToken.lexeme;
        if (!seen.insert(argName).second) {
            addError(E10054, &expr->location, {argName});
            break;
        }
        instance->args.emplace(argName, LgsInstanceArg{argName, expr});
        if (currentToken.type == T_RBRACE) break;
        mustMatch(T_COMMA);
    }
    if (currentToken.type == T_COMMA) consume();
}

void LgsParser::parseArgs(LgsFuncCall* funcCall) {
    if (currentToken.type == T_RPAREN) return;
    std::unordered_set<std::string> seen;
    while (true) {
        std::string argName = "";
        if (currentToken.type == T_IDENTIFIER && peek().type == T_EQUAL) {
            funcCall->isNamed = true;
            argName = currentToken.lexeme;
            consume(2);
            const auto expr = parseExpr();
            if (!mustParse(expr)) break;
            if (!seen.insert(argName).second) {
                addError(E10054, &expr->location, {argName});
                break;
            }
            funcCall->args.emplace_back(LgsFuncArg{argName, expr});
        } else {
            const auto expr = parseExpr();
            if (!mustParse(expr)) break;
            funcCall->args.emplace_back(LgsFuncArg{argName, expr});
        }
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
    }
    if (currentToken.type == T_COMMA) consume();
}

LgsInstance* LgsParser::parseInstance() {
    const auto tokenName = currentToken;
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_IDENTIFIER)) return nullptr;
    std::vector<LgsType*> generics;
    if (matchAndConsume(T_LANGLE)) {
        if (!parseGenericArgs(generics)) {
            reset(oldIndex);
            return nullptr;
        }
    }

    if (!matchOrReset(T_LBRACE, oldIndex)) return nullptr;
    const auto instance = new LgsInstance(tokenName.lexeme);
    setLocation(instance->location, &tokenName);
    instance->setType(new LgsUnknown(instance->name));
    instance->generics = generics;
    parseArgs(instance);
    mustMatch(T_RBRACE);
    return instance;
}

LgsFuncCall* LgsParser::parseFuncCall() {
    const auto oldIndex = currentIndex;
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    const auto nameToken = currentToken;
    std::vector<LgsType*> generics;
    if (peek().type == T_LANGLE) {
        consume();
        if (!parseGenericArgs(generics)) {
            reset(oldIndex);
            return nullptr;
        }
    } else if (peek().type != T_LPAREN) {
        return nullptr;
    } else {
        consume(2);
    }

    const auto funcCall = new LgsFuncCall(nameToken.lexeme);
    setLocation(funcCall->location, &nameToken);
    funcCall->generics = generics;
    if (matchAndConsume(T_RPAREN)) return funcCall;

    std::unordered_set<std::string> seen;
    while (true) {
        std::string argName = "";
        if (currentToken.type == T_IDENTIFIER && peek().type == T_EQUAL) {
            funcCall->isNamed = true;
            argName = currentToken.lexeme;
            consume(2);
            const auto expr = parseExprOrStmtsBlock();
            if (!mustParse(expr)) break;
            if (!seen.insert(argName).second) {
                addError(E10054, &expr->location, {argName});
                break;
            }
            funcCall->args.emplace_back(LgsFuncArg{argName, expr});
        } else {
            const auto expr = parseExprOrStmtsBlock();
            if (!mustParse(expr)) break;
            funcCall->args.emplace_back(LgsFuncArg{argName, expr});
        }
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
    }

    if (currentToken.type == T_COMMA) consume();
    mustMatch(T_RPAREN);
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
    case T_VEC2: dim = 2; break;
    case T_VEC3: dim = 3; break;
    case T_VEC4: dim = 4; break;
    default: break;
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

LgsExpr* LgsParser::parseExprOrStmtsBlock() {
    // The order is important. First check for empty block, then expr, then non-empty block.
    if (currentToken.type == T_LBRACE && peek().type == T_RBRACE) {
        consume(2);
        const auto func = wrapStmtsBlockWithFunc(new LgsStmtsBlock());
        return func;
    }
    if (LgsExpr* expr = parseExpr()) {
        return expr;
    }
    if (const auto stmtsBlock = parseStmtsBlock()) {
        const auto func = wrapStmtsBlockWithFunc(stmtsBlock);
        return func;
    }
    return nullptr;
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

LgsMetaVar* LgsParser::parseLoopMetaVar() {
    const auto metaVarToken = currentToken;
    if (matchAndConsume(T_FOR_I)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_I);
        setLocation(metaVar->location, &metaVarToken);
        metaVar->setType(&LGS_SIZE);
        return metaVar;
    }
    if (matchAndConsume(T_FOR_IS_FIRST)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_IS_FIRST);
        setLocation(metaVar->location, &metaVarToken);
        metaVar->setType(&LGS_BOOL);
        return metaVar;
    }
    if (matchAndConsume(T_FOR_IS_LAST)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_IS_LAST);
        setLocation(metaVar->location, &metaVarToken);
        metaVar->setType(&LGS_BOOL);
        return metaVar;
    }
    return nullptr;
}

LgsExpr* LgsParser::parseConstant() {
    const auto tokenStr = currentToken.lexeme;
    LgsExpr* constant = nullptr;
    switch (currentToken.type) {
    case T_INT: {
        std::string result = tokenStr;
        result.erase(std::ranges::remove(result, '_').begin(), result.end());
        constant = determineIntConst(result, 10);
        break;
    }
    case T_HEX: {
        constant = determineIntConst(tokenStr, 16);
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
        arrExpr->setType(new LgsSet());
    } else {
        arrExpr->setType(new LgsDArray());
    }
    arrExpr->elements = args;
    setLocation(arrExpr->location, &tokens[oldIndex]);
    return arrExpr;
}


LgsHashMap* LgsParser::parseHashMap() {
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_LBRACE)) return nullptr;
    std::vector<LgsPair> pairs;
    const auto freePairs = [&pairs]() {
        for (auto [l, r] : pairs) {
            freeExpr(l);
            freeExpr(r);
        }
    };
    if (!matchAndConsume(T_RBRACE)) {
        while (true) {
            const auto key = parseExpr();
            if (!parsedOrReset(key, oldIndex)) {
                freePairs();
                return nullptr;
            }
            if (!matchOrReset(T_COLON, oldIndex)) {
                freePairs();
                return nullptr;
            }
            const auto value = parseExpr();
            if (!mustParse(value)) break;
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
    std::vector<LgsParam> params;

    if (currentToken.type == T_IDENTIFIER) { // Single param
        LgsParam param(nullptr, currentToken.lexeme);
        consume();
        if (matchAndConsume(T_COLON)) {
            param.setType(parseType());
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
                if (currentToken.type == T_RPAREN || currentToken.type != T_COMMA) break;
            }
            if (currentToken.type == T_COMMA) consume();
            if (currentToken.type == T_RPAREN) consume();
        }
    } else {
        return nullptr;
    }

    LgsType* rt = nullptr;
    if (matchAndConsume(T_COLON)) {
        rt = parseType();
        mustParse(rt);
    }

    if (!matchOrReset(T_DARROW, oldIndex)) {
        freeParams(params);
        freeType(rt);
        return nullptr;
    }

    const auto lambda = new LgsFunc(LGS_ANONYMOUS_NAME, rt, params);
    lambda->isLambda = true;
    setLocation(lambda->location, &tokens[oldIndex]);

    currentFunc = lambda;
    lambda->stmtsBlock = parseStmtsBlock();
    mustParse(lambda->stmtsBlock);
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

LgsExpr* LgsParser::parseEnvVar() {
    const auto name = currentToken;
    if (!matchAndConsume(T_DOLLAR_IDENTIFIER)) return nullptr;
    const auto envVar = new LgsEnvVar(name.lexeme.substr(1));
    setLocation(envVar->location, &name);
    return envVar;
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
    assert(firstExpr);
    const auto oldIndex = currentIndex;
    std::vector<LgsExpr*> exprs;
    LgsVariable* importVar = nullptr;
    if (isImportName(firstExpr)) {
        importVar = firstExpr->asVariable();
    } else {
        exprs.push_back(firstExpr);
    }

    while (true) {
        LgsExpr* expr = nullptr;
        if (const auto funcCall = parseFuncCall()) {
            funcCall->inSelection = true;
            expr = funcCall;
        } else if (const auto variable = parseVariable()) {
            expr = variable;
        }
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
        assert(exprs.front() == firstExpr);
        freeExpr(exprs.front());
        reset(oldIndex);
        return nullptr;
    }

    auto const selection = new LgsSelection(exprs);
    selection->location = firstExpr->location;
    selection->importVar = importVar;
    return selection;
}

LgsJson* LgsParser::parseJson() {
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_JSON)) return nullptr;
    const auto json = new LgsJson();
    setLocation(json->location, &tokens[oldIndex]);
    if (currentToken.type == T_LBRACE) {
        json->jsonType = JSON_OBJECT;
        json->jsonObject = parseJsonObject();
    } else if (currentToken.type == T_LBRACK) {
        json->jsonType = JSON_ARRAY;
        json->jsonArray = parseJsonArray();
    } else {
        parseJsonPrimitive(json);
    }
    return json;
}

LgsJsonObject* LgsParser::parseJsonObject() {
    mustMatch(T_LBRACE);
    const auto jsonObject = new LgsJsonObject();
    if (!matchAndConsume(T_RBRACE)) {
        while (true) {
            const auto keyToken = currentToken;
            if (!mustMatch(T_STRING)) break;
            if (!mustMatch(T_COLON)) break;
            const auto valueJson = parseJsonValue();
            jsonObject->entries[keyToken.lexeme] = valueJson;
            if (currentToken.type == T_RBRACE) break;
            mustMatch(T_COMMA);
        }
        if (currentToken.type == T_COMMA) consume();
        mustMatch(T_RBRACE);
    }
    return jsonObject;
}

LgsJsonArray* LgsParser::parseJsonArray() {
    mustMatch(T_LBRACK);
    const auto jsonArray = new LgsJsonArray();
    while (true) {
        const auto valueJson = parseJsonValue();
        if (!valueJson) break;
        jsonArray->entries.push_back(valueJson);
        if (currentToken.type == T_RBRACK) break;
        mustMatch(T_COMMA);
    }
    if (currentToken.type == T_COMMA) consume();
    mustMatch(T_RBRACK);
    return jsonArray;
}

LgsJson* LgsParser::parseJsonValue() {
    const auto json = new LgsJson();
    setLocation(json->location, &currentToken);
    if (currentToken.type == T_LBRACE) {
        json->jsonType = JSON_OBJECT;
        json->jsonObject = parseJsonObject();
    } else if (currentToken.type == T_LBRACK) {
        json->jsonType = JSON_ARRAY;
        json->jsonArray = parseJsonArray();
    } else {
        parseJsonPrimitive(json);
    }
    return json;
}

bool LgsParser::parseGenericArgs(std::vector<LgsType*>& types) {
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_LANGLE)) return false;
    while (true) {
        const auto type = parseType();
        if (!type) break;
        types.push_back(type);
        if (currentToken.type == T_RANGLE) break;
    }
    if (types.empty()) {
        reset(oldIndex);
        return false;
    }
    if (!matchOrReset(T_RANGLE, oldIndex)) {
        freeTypes(types);
        return false;
    }
    return true;
}

void LgsParser::parsePackageString(LgsImportPackage& pkg, const LgsToken& importToken) {
    const auto importName = importToken.lexeme;
    const auto colonPos = importName.find(':');
    if (colonPos == std::string::npos) {
        errHandler.addError(E60000, {importName});
        return;
    }

    // URL
    const auto urlPart = importName.substr(0, colonPos);
    if (urlPart.starts_with("http:")) {
        errHandler.addError(E60001, {urlPart});
        return;
    }
    if (!urlPart.starts_with("https://")) {
        pkg.url = "https://" + urlPart;
    } else {
        pkg.url = urlPart;
    }

    // Version
    const auto version = importName.substr(colonPos + 1);
    if (!pkg.version.setVersion(version)) {
        errHandler.addError(E10068, &importToken.location, metadata->path, {version});
        return;
    }

    // Name
    const auto lastSlash = urlPart.find_last_of('/');
    if (lastSlash != std::string::npos) {
        pkg.name = urlPart.substr(lastSlash + 1);
    } else {
        pkg.name = urlPart;
    }
}

void LgsParser::parseJsonPrimitive(LgsJson* json) {
    if (const auto strConst = parseStrConst()) {
        json->jsonType = JSON_STRING;
        json->strConst = strConst;
    } else if (const auto constant = parseConstant()) {
        if (const auto intConst = constant->asIntConst()) {
            json->jsonType = JSON_INT;
            json->intConst = intConst;
        } else if (const auto floatConst = constant->asFloatConst()) {
            json->jsonType = JSON_FLOAT;
            json->floatConst = floatConst;
        } else if (constant->asNull()) {
            json->jsonType = JSON_NULL;
            json->null = constant->asNull();
        }
    }
}

void LgsParser::parseImports() {
    const auto importToken = currentToken;
    if (!matchAndConsume(T_IMPORT)) return;
    if (currentToken.lexeme == LGS_C) {
        return parseCImports();
    }
    while (true) {
        const auto var = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        fileImports[var.lexeme] = nullptr;
        if (importToken.location.lineStart != peek().location.lineStart) break;
        mustMatch(T_COMMA);
    }
}

void LgsParser::parseCImports() {
    const auto cToken = currentToken;
    consume();
    while (true) {
        const auto strConst = parseStrConst();
        if (!strConst) break;
        cImports.push_back(strConst);
        if (cToken.location.lineStart != peek().location.lineStart) break;
        mustMatch(T_COMMA);
    }
}

bool LgsParser::validateTypeName(const std::string& typeName, const LgsLocation* location) {
    if (islower(typeName[0])) {
        errHandler.addError(E10033, location, metadata->path, {typeName});
        return false;
    }
    return true;
}

void LgsParser::addFileSymbol(LgsMainFile* file, const LgsSymbol& newSymbol) {
    auto symbolName = *newSymbol.name;
    const auto globalSymbol = globals.table.getSymbol(symbolName);
    if (globalSymbol) {
        if (globalSymbol->isBuiltin) {
            errHandler.addError(E10053, newSymbol.location, metadata->path, {symbolName});
        }
        return;
    }
    file->symbolTable.addSymbol(newSymbol, &errHandler, metadata->path);
}

void LgsParser::setLocation(LgsLocation& location, const LgsToken* token) const {
    location.filepath = &metadata->path;
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
        LgsParser parser(metadata, paths, globals);
        parser.code = part;
        parser.scanTokens();
        const auto expr = parser.parseExpr();
        strConst.parts.push_back(expr);
        replaced.replace(open, close + 1, LGS_STR_FMT_PLACEHOLDER);
        start = open + strlen(LGS_STR_FMT_PLACEHOLDER);
    }
    if (replaced == strConst.value) return;
    strConst.formatedStr = replaced;
}

void LgsParser::validateTestFolder(const LgsFile* testFile) {
    bool foundTestsFolder = false;
    auto currentPath = testFile->path.parent_path();
    while (currentPath != paths.rootPath && currentPath.has_parent_path()) {
        if (currentPath.filename() == "tests") {
            foundTestsFolder = true;
            break;
        }
        currentPath = currentPath.parent_path();
    }
    if (!foundTestsFolder) {
        addError(E10079, &testFile->location, {testFile->path.filename()});
    }
}

bool LgsParser::isImportName(LgsExpr* expr) const {
    if (const auto variable = expr->asVariable()) {
        if (!globals.table.imports.contains(variable->name)) return false;
        variable->isImportName = true;
        return true;
    }
    return false;
}

LgsExpr* LgsParser::determineIntConst(const std::string& tokenStr, const int base) const {
    char* end = nullptr;
    errno = 0;
    const auto v = strtoull(tokenStr.c_str(), &end, base);
    LgsExpr* expr = nullptr;
    if (errno == ERANGE) {
        expr = new LgsIntConst(&LGS_ULONG, static_cast<int64_t>(UINT64_MAX));
    } else if (v <= static_cast<unsigned long long>(INT_MAX)) {
        expr = new LgsIntConst(&LGS_INT, static_cast<int64_t>(v));
    } else if (v <= static_cast<unsigned long long>(UINT_MAX)) {
        expr = new LgsIntConst(&LGS_UINT, static_cast<int64_t>(v));
    } else if (v <= static_cast<unsigned long long>(LONG_MAX)) {
        expr = new LgsIntConst(&LGS_LONG, static_cast<int64_t>(v));
    } else {
        expr = new LgsIntConst(&LGS_ULONG, static_cast<int64_t>(v));
    }
    setLocation(expr->location, &currentToken);
    return expr;
}

int LgsParser::getBinOpPrecedence(const LgsBinOpType opType) {
    switch (opType) {
    case BIT_OR:
        return 1;
    case BIT_XOR:
        return 2;
    case BIT_AND:
        return 3;
    case EQ:
    case NE:
        return 4;
    case LT:
    case GT:
    case LE:
    case GE:
    case IN:
        return 5;
    case LSHIFT:
    case RSHIFT:
        return 6;
    case ADD:
    case SUB:
        return 7;
    case MUL:
    case DIV:
    case MODULO:
        return 8;
    case NOOP:
    default:
        return 0;
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

LgsToken LgsParser::consume(const size_t times) {
    if (!isEOF()) {
        for (size_t i = 0; i < times; ++i) {
            currentIndex++;
            currentToken = tokens[currentIndex];
        }
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
    return errHandler.addError(E10085, &token.location, metadata->path, {});
}

void LgsParser::recursionGuard() {
    if (recursionCount++ < MAX_TOKENS_NUMBER) return;
    assert(0);
}

void LgsParser::addError(const LgsBaseMsg& lgsErr, const LgsLocation* location, const std::vector<std::string>& args) {
    errHandler.addError(lgsErr, location, metadata->path, args);
}

LgsFunc* wrapStmtsBlockWithFunc(LgsStmtsBlock* stmtsBlock) {
    const auto func = new LgsFunc(LGS_ANONYMOUS_NAME, nullptr);
    func->location = stmtsBlock->location;
    func->stmtsBlock = stmtsBlock;
    func->funcType->isLambda = true;
    func->funcType->rt = &LGS_VOID;
    return func;
}
