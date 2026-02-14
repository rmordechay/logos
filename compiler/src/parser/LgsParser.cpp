#include "parser/LgsParser.h"
#include <unordered_set>
#include "LgsTokens.h"
#include "errors/LgsPlmErrors.h"
#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsEnvVar.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsMatrixExpr.h"
#include "exprs/LgsMetaSelection.h"
#include "exprs/LgsModuleExpr.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsCharConst.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "exprs/constants/LgsUIntConst.h"
#include "files/LgsAppConfigFile.h"
#include "files/LgsEnvFile.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsCoroutine.h"
#include "funcs/LgsMainFunc.h"
#include "lgsc/LgsCCompiler.h"
#include "logos/LgsApp.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "parser/LgsLexer.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsImport.h"
#include "stmts/LgsIOPair.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsReturn.h"
#include "stmts/LgsSwitch.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsGenericType.h"
#include "types/LgsInterface.h"
#include "types/LgsNullable.h"
#include "types/LgsSelf.h"
#include "types/LgsSubType.h"
#include "types/LgsUnknown.h"
#include "types/iterables/LgsMatrix.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsByte.h"
#include "types/primitives/LgsDouble.h"
#include "types/primitives/LgsLong.h"
#include "types/primitives/LgsShort.h"
#include "types/primitives/LgsSize.h"
#include "types/primitives/LgsUInt.h"

LgsFunc* wrapStmtsBlockWithLambda(LgsStmtsBlock* stmtsBlock);

#define MAX_TOKENS_NUMBER 100000

bool LgsParser::scanTokens() {
    if (lgsCode == "") {
        lgsCode = getFileText(filePath);
    }
    if (lgsCode.empty()) return false;
    LgsLexer lexer(filePath, lgsCode);
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
    } else if (const auto objFile = parseObjectFile()) {
        file = objFile;
    } else if (const auto interfaceFile = parseInterfaceFile()) {
        file = interfaceFile;
    } else if (isTestRun) {
        if (const auto testFile = parseTestFile()) {
            file = testFile;
        }
    }
    assert(file);
    file->symbolTable.importPaths = importPaths;
    return file;
}

LgsFile* LgsParser::parseSrcFileHeaders() {
    if (!scanTokens()) return nullptr;
    while (true) {
        if (currentToken.type != T_IMPORT) break;
        parseImports();
    }
    LgsFile* file = nullptr;
    if (const auto objFile = parseObjectFile()) {
        file = objFile;
    }
    if (const auto interfaceFile = parseInterfaceFile()) {
        file = interfaceFile;
    }
    assert(file);
    file->symbolTable.importPaths = importPaths;
    return nullptr;
}

LgsMainFile* LgsParser::parseMainFile() {
    if (filePath.filename() != LGS_MAIN_FILE) return nullptr;
    const auto startToken = currentToken;
    const auto mainFile = new LgsMainFile(filePath);
    while (!isEOF()) {
        if (const auto obj = parseObject()) {
            mainFile->objects.push_back(obj);
            if (obj->singleton) continue;
            mainFile->symbolTable.addSymbol(LgsSymbol(obj), &errHandler, filePath);
        } else if (const auto interface = parseInterface()) {
            mainFile->interfaces.push_back(interface);
            mainFile->symbolTable.addSymbol(LgsSymbol(interface), &errHandler, filePath);
        } else if (const auto varDec = parseVarDec()) {
            mainFile->varDecs.push_back(varDec);
            mainFile->symbolTable.addSymbol(LgsSymbol(varDec), &errHandler, filePath);
            if (!varDec->expr) addParsingError();
        } else if (auto lgsEnum = parseEnum()) {
            mainFile->enums.push_back(lgsEnum);
            mainFile->symbolTable.addSymbol(LgsSymbol(lgsEnum), &errHandler, filePath);
        } else if (const auto mainFunc = parseMainFunc()) {
            mainFile->funcs[mainFunc->funcType->name] = mainFunc;
        } else if (const auto func = parseFunc()) {
            mainFile->funcs[func->funcType->name] = func;
            mainFile->symbolTable.addSymbol(LgsSymbol(func), &errHandler, filePath);
        } else if (const auto subType = parseSubtype()) {
            mainFile->subtypes.emplace_back(subType);
            mainFile->symbolTable.addSymbol(LgsSymbol(subType), &errHandler, filePath);
        } else {
            addParsingError();
            break;
        }
    }
    return mainFile;
}

LgsAppConfigFile* LgsParser::parseAppConfigFile() {
    if (!scanTokens()) return nullptr;
    const auto file = new LgsAppConfigFile(filePath);
    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        file->configs.push_back(varDec);
        if (currentToken.type == T_EOF) break;
        if (currentToken.lexeme == "required") break;
    }

    if (currentToken.lexeme == "requiredEnvs") {
        consume();
        mustMatch(T_LBRACE);
        if (!matchAndConsume(T_RBRACE)) {
            while (true) {
                const auto var = currentToken;
                if (!mustMatch(T_IDENTIFIER)) break;
                if (!mustMatch(T_COLON)) break;
                const auto type = parseType();
                mustParse(type);
                auto varDec = new LgsVarDec(var.lexeme, type, nullptr);
                setLocation(varDec->location, &var, &currentToken);
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
            LgsImportPkg importPackage;
            parsePackageString(importPackage, importName);
            importPackage.alias = parseVariable();
            file->packages.emplace_back(importPackage);
            if (currentToken.type != T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    }


    if (currentToken.lexeme == "libs") {
        consume();
        mustMatch(T_LBRACE);
        while (true) {
            const auto lib = parseStrConst();
            if (!lib) break;
            file->libs.push_back(lib);
            if (currentToken.type != T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    }

    if (currentToken.lexeme == "searchPaths") {
        consume();
        mustMatch(T_LBRACE);
        while (true) {
            const auto searchPath = parseStrConst();
            if (!searchPath) break;
            file->searchPaths.push_back(searchPath);
            if (currentToken.type != T_RBRACE) break;
        }
        mustMatch(T_RBRACE);
    }
    assert(currentToken.type == T_EOF);
    return file;
}

LgsObjectFile* LgsParser::parseObjectFile() {
    const auto isSingleton = currentToken.type == T_SINGLETON;
    if (currentToken.type != T_OBJECT && !isSingleton) return nullptr;
    const auto nameToken = consume();
    const auto objectFile = new LgsObjectFile(filePath);
    mustMatch(T_IDENTIFIER);
    const auto withBraces = matchAndConsume(T_LBRACE);
    const auto obj = parseObjectBody(nameToken, isSingleton);
    if (!mustParse(obj)) return objectFile;
    if (withBraces) mustMatch(T_RBRACE);
    objectFile->obj = obj;
    for (const auto innerObj : obj->objects) {
        objectFile->symbolTable.addSymbol(LgsSymbol(innerObj), &errHandler, filePath);
    }
    {
        std::lock_guard lock(mtx);
        globals.addSymbol(LgsSymbol(objectFile->obj), &errHandler, filePath);
    }
    return objectFile;
}

LgsInterfaceFile* LgsParser::parseInterfaceFile() {
    if (!matchAndConsume(T_INTERFACE)) return nullptr;
    const auto nameToken = currentToken;
    const auto interfaceFile = new LgsInterfaceFile(filePath);
    mustMatch(T_IDENTIFIER);
    const auto withBraces = matchAndConsume(T_LBRACE);
    const auto interface = parseInterfaceBody(nameToken);
    if (withBraces) mustMatch(T_RBRACE);
    interfaceFile->interface = interface;
    {
        std::lock_guard lock(mtx);
        globals.addSymbol(LgsSymbol(interfaceFile->interface), &errHandler, filePath);
    }
    return interfaceFile;
}

LgsEnvFile* LgsParser::parseEnvFile() {
    if (!scanTokens()) return nullptr;
    if (currentToken.lexeme != "env") {
        addParsingError();
        return nullptr;
    }
    const auto nameToken = consume();
    const auto file = new LgsEnvFile(filePath);
    file->name = nameToken.lexeme;
    mustMatch(T_IDENTIFIER);
    while (true) {
        const auto varDec = parseVarDec();
        if (!varDec) break;
        file->varDecs.push_back(varDec);
    }
    assert(currentToken.type == T_EOF);
    return file;
}

LgsTestFile* LgsParser::parseTestFile() {
    if (currentToken.lexeme != "test") {
        addParsingError();
        return nullptr;
    }
    const auto nameToken = consume();
    auto const file = new LgsTestFile(filePath);
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
    return obj;
}

LgsInterface* LgsParser::parseInterface() {
    if (!matchAndConsume(T_INTERFACE)) return nullptr;
    const auto nameToken = currentToken;
    mustMatch(T_IDENTIFIER);
    mustMatch(T_LBRACE);
    const auto interface = parseInterfaceBody(nameToken);
    mustMatch(T_RBRACE);
    return interface;
}

LgsObject* LgsParser::parseObjectBody(const LgsToken& tokenName, const bool isSingleton) {
    auto const obj = new LgsObject(tokenName.lexeme);

    // Generic types
    if (matchAndConsume(T_TYPE)) {
        mustMatch(T_COLON);
        while (true) {
            const auto type = parseGenericType();
            if (!type) break;
            obj->generics.push_back(type);
            const auto ct = currentToken.type;
            const auto nt = peek().type;
            if (ct == T_EOF || ct == T_RBRACE || nt == T_COLON || nt == T_LPAREN || nt == T_ENUM || nt == T_INTERFACE ||
                nt == T_IMPLEMENTS) {
                break;
            }
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
            if (ct == T_EOF || ct == T_RBRACE || nt == T_COLON || nt == T_LPAREN || nt == T_ENUM || nt == T_INTERFACE) {
                break;
            }
            mustMatch(T_COMMA);
        }
    }

    // First field is level, second metadata
    auto fieldPosition = 2;
    while (true) {
        if (const auto field = parseField(fieldPosition)) {
            fieldPosition++;
            if (headersOnly && !field->isPublic) continue;
            field->parentType = obj;
            obj->fields.push_back(field);
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
        std::lock_guard lock(mtx);
        globals.addSymbol(LgsSymbol(obj), &errHandler, filePath);
    }

    if (!headersOnly && currentToken.type != T_EOF && currentToken.type != T_RBRACE) {
        assert(0);
    }
    setLocation(obj->location, &tokenName, &currentToken);
    return obj;
}

LgsInterface* LgsParser::parseInterfaceBody(const LgsToken& tokenName) {
    auto const interface = new LgsInterface(tokenName.lexeme);

    auto fieldPosition = 0;
    while (true) {
        if (const auto field = parseField(fieldPosition)) {
            fieldPosition++;
            field->isVirtual = true;
            interface->fields.push_back(field);
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
        method->funcType->addSelf(interface);
        method->stmtsBlock = parseStmtsBlock(false);
        if (!method->stmtsBlock) {
            method->funcType->isVirtual = true;
        }
        if (method->stmtsBlock && method->stmtsBlock->isMacro) addParsingError();
        interface->addMethod(method);
        if (currentToken.type == T_RBRACE || currentToken.type == T_EOF) break;
    }
    setLocation(interface->location, &tokenName, &currentToken);
    return interface;
}

LgsField* LgsParser::parseField(const size_t fieldPosition) {
    const auto oldIndex = currentIndex;
    std::optional<bool> isPublic = std::nullopt;

    // Qualifiers
    while (true) {
        if (matchAndConsume(T_PUBLIC)) {
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
    setLocation(field->location, &nameToken, &currentToken);
    field->setType(type);
    field->position = fieldPosition;
    if (isPublic.has_value()) field->isPublic = isPublic.value();
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
    setLocation(ioPair->location, &openingFuncName, &currentToken);
    return ioPair;
}

LgsType* LgsParser::parseType() {
    const auto startToken = currentToken;
    LgsType* type = nullptr;
    if (startToken.type == T_LBRACE) {
        type = parseMapType();
    } else if (startToken.type == T_LPAREN) {
        type = parseFuncType();
    } else if (currentToken.type == T_SELF_CLASS) {
        type = new LgsSelf();
        consume();
    } else if (currentToken.type == T_VEC2) {
        type = new LgsVec(2);
        consume();
    } else if (currentToken.type == T_VEC3) {
        type = new LgsVec(3);
        consume();
    } else if (currentToken.type == T_VEC4) {
        type = new LgsVec(4);
        consume();
    } else if (currentToken.type == T_MATRIX) {
        const auto [rows, columns] = extractMatDims(currentToken);
        type = new LgsMatrix(rows, columns);
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
        else type = new LgsUnknown(typeText);
        consume();
    }
    if (!type) return nullptr;
    if (currentToken.type == T_LANGLE) {
        type->genericArgs = parseGenericArgs();
    }
    setLocation(type->location, &startToken, &currentToken);

    // Nullable
    if (type && matchAndConsume(T_QUEST_MARK)) {
        type = new LgsNullable(type);
        setLocation(type->location, &startToken, &currentToken);
    }

    // Array
    auto isSized = false;
    auto isUnsized = false;
    if (type && currentToken.type == T_LBRACK) {
        std::vector<LgsExpr*> sizes;
        while (matchAndConsume(T_LBRACK)) {
            if (const auto size = parseUnary(false)) {
                sizes.push_back(size);
                if (isUnsized) addError(E10029, startToken.location);
                isSized = true;
            } else {
                type = new LgsDArray(type);
                if (isSized) addError(E10029, startToken.location);
                isUnsized = true;
            }
            mustMatch(T_RBRACK);
        }

        if (!sizes.empty()) {
            std::ranges::reverse(sizes);
            for (const auto& size : sizes) {
                type = new LgsSArray(type, size);
                setLocation(type->location, &startToken, &currentToken);
            }
        }
    }

    // Nullable
    if (type && matchAndConsume(T_QUEST_MARK)) {
        type = new LgsNullable(type);
        setLocation(type->location, &startToken, &currentToken);
    }

    return type;
}

LgsEnum* LgsParser::parseEnum() {
    if (currentToken.type != T_ENUM) return nullptr;
    const auto nameToken = consume();
    mustMatch(T_IDENTIFIER);
    mustMatch(T_LBRACE);
    const auto enum_ = new LgsEnum(nameToken.lexeme);
    auto position = 0;
    while (true) {
        const auto enumField = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        LgsExpr* expr = nullptr;
        if (matchAndConsume(T_EQUAL)) {
            expr = parseExpr();
            mustParse(expr);
        }
        position++;
        const auto fieldType = new LgsEnum(enum_->name, enumField.lexeme, position);
        const auto field = new LgsField(enumField.lexeme, fieldType, expr);
        field->position = position;
        setLocation(field->location, &enumField, &currentToken);
        enum_->fields.push_back(field);
        if (currentToken.type == T_RBRACE) break;
    }
    mustMatch(T_RBRACE);
    setLocation(enum_->location, &nameToken, &currentToken);
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
        setLocation(subtype->location, &lType, &currentToken);
        return subtype;
    }
    if (currentToken.type == T_IDENTIFIER && peek().type == T_EQUAL) {
        const auto lType = currentToken;
        consume(2);
        const auto rType = parseType();
        mustParse(rType);
        const auto subtype = new LgsSubType(lType.lexeme, rType);
        setLocation(subtype->location, &lType, &currentToken);
        subtype->isWeakType = true;
        return subtype;
    }
    return nullptr;
}

LgsFuncType* LgsParser::parseFuncType() {
    if (!matchAndConsume(T_LPAREN)) return nullptr;
    const auto startToken = currentToken;
    const auto funcType = new LgsFuncType();
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
    setLocation(funcType->location, &startToken, &startToken);
    return funcType;
}

LgsMap* LgsParser::parseMapType() {
    if (!matchAndConsume(T_LBRACE)) return nullptr;
    const auto startToken = currentToken;
    const auto mapType = new LgsMap();
    const auto l = parseType();
    mustParse(l);
    mustMatch(T_COLON);
    const auto r = parseType();
    mustParse(r);
    mustMatch(T_RBRACE);
    mapType->pairType->key = l;
    mapType->pairType->value = r;
    setLocation(mapType->location, &startToken, &currentToken);
    return mapType;
}

LgsGenericType* LgsParser::parseGenericType() {
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    const auto startToken = currentToken;
    const auto generic = new LgsGenericType(currentToken.lexeme);
    consume();
    setLocation(generic->location, &startToken, &currentToken);
    return generic;
}

std::vector<LgsType*> LgsParser::parseGenericArgs() {
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_LANGLE)) return {};
    std::vector<LgsType*> types;
    while (true) {
        const auto type = parseType();
        if (!type) break;
        types.push_back(type);
        if (currentToken.type == T_RANGLE) break;
        mustMatch(T_COMMA);
    }
    if (types.empty()) {
        reset(oldIndex);
        return {};
    }
    if (!matchOrReset(T_RANGLE, oldIndex)) {
        freeTypes(types);
        return {};
    }
    return types;
}

LgsFunc* LgsParser::parseFunc() {
    const auto ft = parseFuncHeader();
    if (!ft) return nullptr;
    const auto func = new LgsFunc(ft);
    func->location = ft->location;
    currentFunc = func;
    func->stmtsBlock = parseStmtsBlock();
    if (func->stmtsBlock->isMacro) addParsingError();
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
    if (func->stmtsBlock->isMacro) addParsingError();
    currentFunc = nullptr;
    return func;
}

LgsFunc* LgsParser::parseMethod(LgsObject* obj) {
    auto isPublic = false;
    if (matchAndConsume(T_PUBLIC)) {
        isPublic = true;
    }
    const auto& funcHeader = parseFuncHeader();
    if (!funcHeader) return nullptr;
    funcHeader->parentName = obj->name;
    const auto func = new LgsFunc(funcHeader);
    currentFunc = func;
    func->location = func->funcType->location;
    funcHeader->isPublic = isPublic;
    funcHeader->addSelf(obj);
    if (!headersOnly) {
        func->stmtsBlock = parseStmtsBlock();
        if (!func->stmtsBlock || func->stmtsBlock->isMacro) {
            addParsingError(&func->location);
        }
    }
    currentFunc = nullptr;
    return func;
}

LgsFuncType* LgsParser::parseFuncHeader() {
    const auto nameToken = currentToken;
    if (currentToken.type != T_IDENTIFIER) return nullptr;
    std::vector<LgsGenericType*> genericsTypes;
    if (peek().type == T_LANGLE) {
        consume(2);
        while (true) {
            const auto type = parseGenericType();
            if (!type) break;
            genericsTypes.push_back(type);
            if (currentToken.type == T_RANGLE) break;
            mustMatch(T_COMMA);
        }
        mustMatch(T_RANGLE);
        if (genericsTypes.empty()) addParsingError();
    } else if (peek().type == T_LPAREN) {
        consume();
    } else {
        return nullptr;
    }

    const auto funcType = new LgsFuncType(nameToken.lexeme);
    funcType->genericTypes = genericsTypes;
    parseParams(funcType);
    mustMatch(T_RPAREN);
    funcType->rt = matchAndConsume(T_COLON) ? parseType() : &LGS_VOID;
    setLocation(funcType->location, &nameToken, &currentToken);
    return funcType;
}

void LgsParser::parseParams(LgsFuncType* funcType) {
    if (!matchAndConsume(T_LPAREN)) return;
    if (currentToken.type == T_RPAREN) return;
    while (true) {
        // Name
        const auto paramName = currentToken;
        if (!mustMatch(T_IDENTIFIER)) break;
        if (currentToken.type == T_COLON) {
            consume();
        } else if (currentToken.type != T_LPAREN) {
            addParsingError();
            break;
        }

        // Type
        const auto type = parseType();
        mustParse(type);
        LgsParam param(type, paramName.lexeme);

        // Variadic or expr
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

        setLocation(param.location, &paramName, &currentToken);
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
    return nullptr;
}

LgsStmtsBlock* LgsParser::parseStmtsBlock(const bool withSingleStmt) {
    LgsStmtsBlock* stmtsBlock = nullptr;
    const auto startToken = currentToken;
    const auto isMacro = matchAndConsume(T_STAR_LBRACE);
    if (isMacro || matchAndConsume(T_LBRACE)) {
        stmtsBlock = new LgsStmtsBlock();
        stmtsBlock->isMacro = isMacro;
        if (!matchAndConsume(T_RBRACE)) {
            while (true) {
                if (const auto stmt = parseStmt()) {
                    stmtsBlock->stmts.push_back(LgsStmtWrapper(stmt));
                } else if (const auto obj = parseObject()) {
                    stmtsBlock->stmts.push_back(LgsStmtWrapper(obj));
                } else if (const auto expr = parseExpr()) {
                    stmtsBlock->stmts.push_back(LgsStmtWrapper(expr));
                } else {
                    break;
                }
                if (currentToken.type == T_RBRACE) break;
            }
            if (isMacro) mustMatch(T_STAR_RBRACE);
            else mustMatch(T_RBRACE);
        }
        setLocation(stmtsBlock->location, &currentToken, &startToken);
    } else if (withSingleStmt) {
        if (const auto expr = parseExpr()) {
            stmtsBlock = new LgsStmtsBlock();
            stmtsBlock->location = expr->location;
            stmtsBlock->stmts.push_back(LgsStmtWrapper(expr));
            stmtsBlock->location = expr->location;
        } else if (const auto stmt = parseStmt()) {
            stmtsBlock = new LgsStmtsBlock();
            stmtsBlock->location = stmt->location;
            stmtsBlock->stmts.push_back(LgsStmtWrapper(stmt));
            stmtsBlock->location = stmt->location;
        } else {
            return nullptr;
        }
        setLocation(stmtsBlock->location, &currentToken, &startToken);
    }
    return stmtsBlock;
}

LgsVarDec* LgsParser::parseVarDec() {
    const auto oldIndex = currentIndex;
    auto isMut = false;
    while (true) {
        if (matchAndConsume(T_MUT)) {
            if (isMut) addParsingError();
            isMut = true;
        } else {
            break;
        }
    }

    const auto nameToken = currentToken;
    if (isMut) {
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
    setLocation(varDec->location, &nameToken, &currentToken);
    varDec->isMutable = isMut;
    return varDec;
}

LgsStmt* LgsParser::parseAssignment() {
    const auto oldIndex = currentIndex;
    // Left expr
    const auto l = parseExpr();
    if (!parsedOrReset(l, oldIndex)) return nullptr;

    // Operation
    if (!LGS_BINARY_OPS_DICT.contains(currentToken.type) && currentToken.type != T_WALRUS) {
        freeExpr(l);
        reset(oldIndex);
        return nullptr;
    }
    const auto opToken = currentToken;
    consume();

    // Right expr
    const auto r = parseExpr();
    if (!r) {
        freeExpr(l);
        reset(oldIndex);
        return nullptr;
    }

    LgsAssignment* assignment;
    if (currentToken.type != T_WALRUS) {
        assignment = new LgsAssignment(l, r);
    } else {
        const auto op = LGS_BINARY_OPS_DICT.at(opToken.type);
        const auto binExpr = new LgsBinaryExpr(l, r, op);
        assignment = new LgsAssignment(binExpr);
    }
    setLocation(assignment->location, &opToken, &currentToken);
    return assignment;
}

LgsStmt* LgsParser::parseIfStmt() {
    const auto startToken = currentToken;
    if (!matchAndConsume(T_IF)) return nullptr;
    if (currentToken.type == T_LBRACE) return parseBoolSwitch();
    const auto condExpr = parseExpr(false, false);
    mustParse(condExpr);
    const auto ifBlock = parseStmtsBlock();
    mustParse(ifBlock);
    const auto ifStmt = new LgsIfStmt(condExpr, ifBlock);
    auto isMacro = ifBlock->isMacro;
    while (true) {
        if (!matchAndConsume(T_ELSE)) break;
        if (matchAndConsume(T_IF)) {
            const auto elseCond = parseExpr(false, false);
            mustParse(elseCond);
            const auto stmtsBlock = parseStmtsBlock();
            mustParse(stmtsBlock);
            // Make sure either all blocks are macro or none of them.
            if (isMacro && !stmtsBlock->isMacro) addParsingError();
            else if (!isMacro && stmtsBlock->isMacro) addParsingError();
            isMacro = isMacro || stmtsBlock->isMacro;
            ifStmt->elseIfs.push_back(std::make_pair(elseCond, stmtsBlock));
        } else {
            ifStmt->elseBlock = parseStmtsBlock();
            mustParse(ifStmt->elseBlock);
            if (isMacro && !ifStmt->elseBlock->isMacro) addParsingError();
            break;
        }
    }
    setLocation(ifStmt->location, &startToken, &currentToken);
    return ifStmt;
}

LgsSwitch* LgsParser::parseSwitch() {
    const auto startToken = currentToken;
    if (!matchAndConsume(T_SWITCH)) return nullptr;
    const auto condExpr = parseUnary(false);
    mustParse(condExpr);
    mustMatch(T_LBRACE);
    const auto switchStmt = new LgsSwitch(condExpr);
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
    setLocation(switchStmt->location, &startToken, &currentToken);
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
    setLocation(ifStmt->location, &startToken, &currentToken);
    return ifStmt;
}

LgsForLoop* LgsParser::parseForLoop() {
    if (matchAndConsume(T_FOR_EVER)) return parseInfiniteLoop();
    const auto forKeyword = currentToken;
    if (!matchAndConsume(T_FOR)) return nullptr;

    // Consume the first loop expr. After this we may have 3 cases:
    // 1. Next token is T_LBRACE -> for expr {...} (expr can be anything)
    // 2. Next token is T_IN -> for var in iter {...} (var must be a variable)
    // 3. Next token is T_COMMA -> for expr1, expr2, ... in iter {...} (expr1, expr2... must be variables)
    const auto firstExpr = parseUnary(false);
    mustParse(firstExpr);
    if (currentToken.type == T_LBRACE) {
        // This may turn to ForEachLoop in the sema stage depending on the type of firstExpr.
        const auto forLoop = new LgsRangeLoop(nullptr, firstExpr);
        setLocation(forLoop->location, &forKeyword, &currentToken);
        forLoop->stmtsBlock = parseStmtsBlock();
        if (forLoop->stmtsBlock->isMacro) addParsingError();
        mustParse(forLoop->stmtsBlock);
        return forLoop;
    }

    // At this point we are expecting a loop with an 'in' keyword (only variables are allowed).
    const auto firstLoopVar = firstExpr->asVariable();
    assert(firstLoopVar);
    const auto firstVarName = firstLoopVar->name;
    freeExpr(firstExpr); // We only need the name of the variable

    // Multiple loop vars
    std::vector loopVars = {firstVarName};
    if (matchAndConsume(T_COMMA)) {
        while (true) {
            const auto var = currentToken;
            mustMatch(T_IDENTIFIER);
            loopVars.push_back(var.lexeme);
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

    forLoop->stmtsBlock = parseStmtsBlock();
    mustParse(forLoop->stmtsBlock);
    if (forLoop->stmtsBlock->isMacro) addParsingError();
    setLocation(forLoop->location, &forKeyword, &currentToken);
    return forLoop;
}

LgsWhileLoop* LgsParser::parseWhileLoop() {
    const auto startToken = currentToken;
    if (!matchAndConsume(T_WHILE)) return nullptr;
    auto const whileLoop = new LgsWhileLoop();
    whileLoop->condExpr = parseUnary(false);
    mustParse(whileLoop->condExpr);
    whileLoop->stmtsBlock = parseStmtsBlock();
    mustParse(whileLoop->stmtsBlock);
    if (whileLoop->stmtsBlock->isMacro) addParsingError();
    setLocation(whileLoop->location, &startToken, &currentToken);
    return whileLoop;
}

LgsInfiniteLoop* LgsParser::parseInfiniteLoop() {
    const auto startToken = currentToken;
    const auto infiniteLoop = new LgsInfiniteLoop();
    infiniteLoop->stmtsBlock = parseStmtsBlock();
    mustParse(infiniteLoop->stmtsBlock);
    if (infiniteLoop->stmtsBlock->isMacro) addParsingError();
    setLocation(infiniteLoop->location, &startToken, &currentToken);
    return infiniteLoop;
}

LgsReturn* LgsParser::parseReturnStmt() {
    const auto returnToken = currentToken;
    if (!matchAndConsume(T_RETURN)) return nullptr;
    const auto expr = parseExpr();
    if (expr) {
        expr->isReturnExpr = true;
    }
    auto const returnStmt = new LgsReturn(expr);
    setLocation(returnStmt->location, &returnToken, &currentToken);
    return returnStmt;
}

LgsStmt* LgsParser::parseContinueStmt() {
    if (!matchAndConsume(T_CONTINUE)) return nullptr;
    const auto continueStmt = new LgsContinue();
    setLocation(continueStmt->location, &currentToken, &currentToken);
    return continueStmt;
}

LgsBreak* LgsParser::parseBreakStmt() {
    const auto startToken = currentToken;
    if (!matchAndConsume(T_BREAK)) return nullptr;
    const auto breakStmt = new LgsBreak();
    if (matchAndConsume(T_IF)) {
        breakStmt->isBreakIf = true;
    }
    setLocation(breakStmt->location, &startToken, &currentToken);
    return breakStmt;
}

LgsCoroutine* LgsParser::parseCoroutine() {
    const auto goToken = currentToken;
    if (!matchAndConsume(T_GO)) return nullptr;

    LgsExpr* expr = nullptr;
    if (const auto stmtsBlock = parseStmtsBlock(false)) {
        if (stmtsBlock->isMacro) addParsingError();
        const auto fc = new LgsFuncCall("");
        setLocation(fc->location, &goToken, &currentToken);
        fc->func = wrapStmtsBlockWithLambda(stmtsBlock);
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
    } else if (const auto selection = expr->asSelection()) {
        coroutine->selection = selection;
        const auto methodCall = coroutine->selection->asMethodCall();
        if (!methodCall) addParsingError();
    }

    return coroutine;
}

LgsDeferStmt* LgsParser::parseDeferStmt() {
    const auto deferToken = currentToken;
    if (!matchAndConsume(T_DEFER)) return nullptr;

    LgsExpr* expr = nullptr;
    if (const auto stmtsBlock = parseStmtsBlock(false)) {
        if (stmtsBlock->isMacro) addParsingError();
        const auto fc = new LgsFuncCall("");
        setLocation(fc->location, &deferToken, &currentToken);
        fc->func = wrapStmtsBlockWithLambda(stmtsBlock);
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
        const auto& methodCall = deferStmt->selection->asMethodCall();
        if (!methodCall) addParsingError();
        methodCall->isDeferred = true;
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
    if (ioStmt->stmtsBlock->isMacro) addParsingError();
    return ioStmt;
}

LgsExpr* LgsParser::parseExpr(const bool withLambda, const bool withInstance) {
    const auto startToken = currentToken;
    if (startToken.type == T_RBRACE || startToken.type == T_RPAREN || startToken.type == T_RANGLE) {
        return nullptr;
    }
    if (withLambda) {
        if (const auto lambda = parseLambda()) return lambda;
    }
    const auto expr = parseExprWithPrecedence(0, withInstance);
    if (matchAndConsume(T_THEN)) {
        const auto thenExpr = parseExpr(withInstance);
        mustMatch(T_ELSE);
        const auto elseExpr = parseExpr(withInstance);
        mustParse(elseExpr);
        const auto ternaryExpr = new LgsTernaryExpr(expr, thenExpr, elseExpr);
        setLocation(ternaryExpr->location, &startToken, &currentToken);
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

LgsExpr* LgsParser::parseExprWithPrecedence(const int minPrecedence, const bool withInstance) {
    const auto startToken = currentToken;
    const auto oldIndex = currentIndex;
    auto left = parseUnary(withInstance);
    if (!parsedOrReset(left, oldIndex)) return nullptr;
    while (true) {
        const LgsBinOp* op;
        const auto it = LGS_BINARY_OPS_DICT.find(currentToken.type);
        if (it != LGS_BINARY_OPS_DICT.end()) {
            op = &it->second;
        } else if (currentToken.lexeme == "X" && peek().type != T_DOT) {
            op = &CROSS_OP;
        } else {
            break;
        }
        const auto opToken = currentToken;
        consume();
        const auto precedence = getBinOpPrecedence(op->opType);
        if (precedence < minPrecedence) {
            currentToken = tokens[--currentIndex];
            break;
        }
        const auto right = parseExprWithPrecedence(precedence + 1, withInstance);
        if (!right) {
            addParsingError();
            return left;
        }
        left = new LgsBinaryExpr(left, right, *op);
        setLocation(left->location, &opToken, &currentToken);
    }
    return left;
}

LgsExpr* LgsParser::parseUnary(const bool withInstance) {
    LgsExpr* expr = nullptr;
    if (matchAndConsume(T_LPAREN)) {
        expr = parseExprWithPrecedence(0, withInstance);
        mustMatch(T_RPAREN);
        return expr;
    }

    if (const auto metaVar = parseLoopMetaVar()) return metaVar;
    if (const auto constant = parseConstant()) expr = constant;
    else if (const auto charConst = parseCharConst()) expr = charConst;
    else if (const auto strConst = parseStrConst()) expr = strConst;
    else if (const auto vector = parseVectorExpr()) expr = vector;
    else if (const auto matrix = parseMatrixExpr()) expr = matrix;
    else if (const auto envVar = parseEnvVar()) expr = envVar;
    else if (const auto arrayExpr = parseArrayExpr()) expr = arrayExpr;
    else if (const auto hashMap = parseHashMap()) expr = hashMap;
    else if (const auto prefixExpr = parsePrefixExpr()) expr = prefixExpr;
    else if (const auto funcCall = parseFuncCall()) expr = funcCall;
    else if (const auto moduleExpr = parseModuleExpr()) expr = moduleExpr;
    else if (withInstance && ((expr = parseInstance()))) {}
    else if (const auto variable = parseVariable()) expr = variable;
    else return nullptr;

    if (matchAndConsume(T_DOT)) expr = parseSelection(expr);
    else if (matchAndConsume(T_DOUBLE_COLON)) expr = parseMetaSelection(expr);
    else if (const auto iterIndex = parseIterIndex(expr)) expr = iterIndex;
    else if (const auto postfixExpr = parsePostfixExpr(expr)) expr = postfixExpr;

    if (matchAndConsume(T_QUEST_MARK)) {
        const auto nullableExpr = new LgsNullableExpr(expr);
        nullableExpr->location = expr->location;
        expr = nullableExpr;
    } else if (matchAndConsume(T_EXCLA_MARK)) {
        expr->hasUnwrap = true;
    }
    return expr;
}

LgsExpr* LgsParser::parseArgExprOrLambda() {
    // The order is important. First check for empty block, then expr, then non-empty block.
    if (currentToken.type == T_LBRACE && peek().type == T_RBRACE) {
        consume(2);
        return wrapStmtsBlockWithLambda(new LgsStmtsBlock());
    }
    if (const auto expr = parseExpr()) {
        return expr;
    }
    if (const auto stmtsBlock = parseStmtsBlock()) {
        if (stmtsBlock->isMacro) addParsingError();
        return wrapStmtsBlockWithLambda(stmtsBlock);
    }
    return nullptr;
}

LgsVariable* LgsParser::parseVariable() {
    const auto startToken = currentToken;
    LgsVariable* var = nullptr;
    if (currentToken.type == T_IDENTIFIER) {
        var = new LgsVariable(currentToken.lexeme);
    } else if (currentToken.type == T_SELF_INSTANCE) {
        var = new LgsVariable(currentToken.lexeme);
        currentFunc->funcType->hasSelf = true;
    } else if (currentToken.type == T_SELF_CLASS) {
        var = new LgsVariable(currentToken.lexeme);
    } else {
        return nullptr;
    }
    consume();
    setLocation(var->location, &startToken, &startToken);
    return var;
}

LgsModuleExpr* LgsParser::parseModuleExpr() {
    const auto startToken = currentToken;
    if (startToken.type != T_IDENTIFIER) return nullptr;
    if (!importAppNames.contains(startToken.lexeme)) return nullptr;
    consume();
    const auto moduleExpr = new LgsModuleExpr(startToken.lexeme);
    setLocation(moduleExpr->location, &startToken, &startToken);
    return moduleExpr;
}

LgsInstance* LgsParser::parseInstance() {
    const auto tokenName = currentToken;
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_IDENTIFIER)) return nullptr;
    auto generics = parseGenericArgs();
    if (!matchOrReset(T_LBRACE, oldIndex)) {
        freeTypes(generics);
        return nullptr;
    }
    const auto instance = new LgsInstance(tokenName.lexeme);
    instance->setType(new LgsUnknown(instance->name));
    instance->generics = generics;
    parseArgs(instance);
    mustMatch(T_RBRACE);
    setLocation(instance->location, &tokenName, &currentToken);
    return instance;
}

LgsFuncCall* LgsParser::parseFuncCall() {
    const auto nameToken = currentToken;
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_IDENTIFIER)) return nullptr;

    // Generic args
    auto genericsArgs = parseGenericArgs();
    if (!matchOrReset(T_LPAREN, oldIndex)) {
        freeTypes(genericsArgs);
        return nullptr;
    }

    const auto funcCall = new LgsFuncCall(nameToken.lexeme);
    setLocation(funcCall->location, &nameToken, &currentToken);
    funcCall->genericArgs = genericsArgs;
    if (matchAndConsume(T_RPAREN)) return funcCall;

    // Arguments
    std::unordered_set<std::string> seen;
    while (true) {
        std::string argName = "";
        if (currentToken.type == T_IDENTIFIER && peek().type == T_EQUAL) {
            funcCall->isNamed = true;
            argName = currentToken.lexeme;
            consume(2);
            const auto exprOrStmt = parseArgExprOrLambda();
            if (!exprOrStmt) break;
            if (!seen.insert(argName).second) {
                addError(E10054, exprOrStmt->location, {argName});
                break;
            }
            funcCall->args.emplace_back(exprOrStmt, argName);
        } else {
            const auto exprOrStmt = parseArgExprOrLambda();
            if (!exprOrStmt) break;
            funcCall->args.emplace_back(exprOrStmt, argName);
        }
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
        if (currentToken.type == T_RPAREN || currentToken.type == T_RBRACE) break;
    }
    mustMatch(T_RPAREN);
    return funcCall;
}

LgsStrConst* LgsParser::parseStrConst() {
    if (currentToken.type != T_STRING) return nullptr;
    const auto textToken = currentToken;
    const auto strConst = new LgsStrConst(textToken.lexeme);
    extractStrParts(strConst);
    consume();
    setLocation(strConst->location, &textToken, &currentToken);
    return strConst;
}

LgsCharConst* LgsParser::parseCharConst() {
    if (currentToken.type != T_STRING) return nullptr;
    const auto textToken = currentToken;
    if (textToken.lexeme.length() != 1) return nullptr;
    const auto expr = new LgsCharConst(textToken.lexeme[0]);
    setLocation(expr->location, &textToken, &currentToken);
    consume();
    return expr;
}

LgsMetaVar* LgsParser::parseLoopMetaVar() {
    const auto metaVarToken = currentToken;
    if (matchAndConsume(T_FOR_I)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_I);
        setLocation(metaVar->location, &metaVarToken, &currentToken);
        metaVar->setType(&LGS_SIZE);
        return metaVar;
    }
    if (matchAndConsume(T_FOR_IS_FIRST)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_IS_FIRST);
        setLocation(metaVar->location, &metaVarToken, &currentToken);
        metaVar->setType(&LGS_BOOL);
        return metaVar;
    }
    if (matchAndConsume(T_FOR_IS_LAST)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_IS_LAST);
        setLocation(metaVar->location, &metaVarToken, &currentToken);
        metaVar->setType(&LGS_BOOL);
        return metaVar;
    }
    if (matchAndConsume(T_FOR_ELEMENT)) {
        const auto metaVar = new LgsMetaVar(metaVarToken.lexeme, FOR_ELEMENT);
        setLocation(metaVar->location, &metaVarToken, &currentToken);
        return metaVar;
    }
    return nullptr;
}

LgsExpr* LgsParser::parseConstant() {
    const auto startToken = currentToken;
    const auto tokenStr = currentToken.lexeme;
    LgsExpr* constant = nullptr;
    switch (currentToken.type) {
    case T_INT: {
        auto result = tokenStr;
        result.erase(std::ranges::remove(result, '_').begin(), result.end());
        constant = determineIntConst(result, 10);
        break;
    }
    case T_UINT: {
        auto str = tokenStr;
        if (tokenStr.ends_with("U")) str.pop_back();
        uint64_t v = 0;
        if (str[0] == '-') {
            addError(E10110, startToken.location);
        } else {
            errno = 0;
            char* end = nullptr;
            v = strtoull(str.c_str(), &end, 10);
            if (errno == ERANGE || *end != '\0') {
                addError(E10110, startToken.location);
            }
        }
        constant = new LgsUIntConst(&LGS_UINT, v);
        break;
    }
    case T_HEX: {
        std::string result = tokenStr;
        result.erase(std::ranges::remove(result, '_').begin(), result.end());
        constant = determineIntConst(result, 16);
        break;
    }
    case T_BINARY: {
        std::string result = tokenStr;
        result.erase(std::ranges::remove(result, '_').begin(), result.end());
        constant = determineIntConst(result, 2);
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
    case T_DOUBLE: {
        auto str = tokenStr;
        if (tokenStr.ends_with("D")) str.pop_back();
        constant = new LgsFloatConst(&LGS_DOUBLE, std::stod(str));
        break;
    }
    case T_BOOL: {
        const auto value = tokenStr == LgsBool::trueLiteral;
        constant = new LgsIntConst(&LGS_BOOL, value);
        break;
    }
    case T_NULL: {
        constant = new LgsNullableExpr();
        break;
    }
    default:
        return nullptr;
    }
    consume();
    setLocation(constant->location, &startToken, &currentToken);
    if (constant->asNullableExpr() && currentToken.type == T_QUEST_MARK) {
        addError(E10012, startToken.location);
    }
    return constant;
}

LgsArrayExpr* LgsParser::parseArrayExpr() {
    const auto startToken = currentToken;
    if (!matchAndConsume(T_LBRACK)) return nullptr;
    std::vector<LgsExpr*> args;
    while (true) {
        const auto expr = parseExpr();
        if (!expr) break;
        args.push_back(expr);
        if (currentToken.type == T_RBRACK) break;
        mustMatch(T_COMMA);
    }
    mustMatch(T_RBRACK);
    const auto arrExpr = new LgsArrayExpr();
    arrExpr->type = new LgsDArray();
    arrExpr->elements = args;
    setLocation(arrExpr->location, &startToken, &currentToken);
    return arrExpr;
}

LgsVectorExpr* LgsParser::parseVectorExpr() {
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
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
    }

    mustMatch(T_RPAREN);
    auto const vecExpr = new LgsVectorExpr(dim);
    setLocation(vecExpr->location, &nameToken, &currentToken);
    vecExpr->elements = args;
    return vecExpr;
}

LgsMatrixExpr* LgsParser::parseMatrixExpr() {
    const auto nameToken = currentToken;
    const auto name = nameToken.lexeme;
    if (!matchAndConsume(T_MATRIX)) return nullptr;
    if (!mustMatch(T_LPAREN)) return nullptr;

    std::vector<LgsArrayExpr*> args;
    while (true) {
        const auto expr = parseArrayExpr();
        if (!expr) break;
        args.push_back(expr);
        if (currentToken.type == T_RPAREN) break;
        mustMatch(T_COMMA);
    }

    mustMatch(T_RPAREN);
    const auto [rows, columns] = extractMatDims(nameToken);
    auto const matExpr = new LgsMatrixExpr(rows, columns);
    setLocation(matExpr->location, &nameToken, &currentToken);
    matExpr->elements = args;
    return matExpr;
}

LgsHashMap* LgsParser::parseHashMap() {
    const auto startToken = currentToken;
    const auto oldIndex = currentIndex;
    if (!matchAndConsume(T_LBRACE)) return nullptr;
    std::vector<LgsPair*> pairs;
    const auto freePairs = [&pairs] {
        for (const auto pair : pairs) {
            freeExpr(pair->key);
            freeExpr(pair->value);
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
            pairs.push_back(new LgsPair(key, value));
            if (currentToken.type == T_RBRACE) break;
            mustMatch(T_COMMA);
        }
        if (currentToken.type == T_COMMA) consume();
        mustMatch(T_RBRACE);
    }

    auto const hashMap = new LgsHashMap();
    setLocation(hashMap->location, &startToken, &currentToken);
    hashMap->elements = pairs;
    return hashMap;
}


LgsFunc* LgsParser::parseLambda() {
    const auto startToken = currentToken;
    const auto oldIndex = currentIndex;
    std::vector<LgsParam> params;
    if (currentToken.type == T_IDENTIFIER) {
        // Single param
        LgsParam param(nullptr, currentToken.lexeme);
        consume();
        if (matchAndConsume(T_COLON)) {
            param.setType(parseType());
            mustParse(param.type);
        }
        params.emplace_back(param);
    } else if (matchAndConsume(T_LPAREN)) {
        // Multiple params
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
                if (!matchAndConsume(T_COMMA)) break;
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

    const auto lambda = new LgsFunc("", rt, params);
    currentFunc = lambda;
    lambda->funcType->isLambda = true;
    lambda->stmtsBlock = parseStmtsBlock();
    mustParse(lambda->stmtsBlock);
    if (lambda->stmtsBlock->isMacro) addParsingError();
    currentFunc = nullptr;
    setLocation(lambda->location, &startToken, &currentToken);
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
    setLocation(prefixExpr->location, &opToken, &currentToken);
    return prefixExpr;
}

LgsExpr* LgsParser::parseEnvVar() {
    const auto name = currentToken;
    if (!matchAndConsume(T_DOLLAR_IDENTIFIER)) return nullptr;
    const auto envVar = new LgsEnvVar(name.lexeme.substr(1));
    setLocation(envVar->location, &name, &currentToken);
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
    const auto startIndex = currentIndex;
    std::vector exprs = {firstExpr};
    while (true) {
        LgsExpr* expr = nullptr;
        if (const auto funcCall = parseFuncCall()) {
            funcCall->inSelection = true;
            expr = funcCall;
        } else if (const auto instance = parseInstance()) {
            expr = instance;
        } else if (const auto variable = parseVariable()) {
            expr = variable;
        }
        if (expr) {
            if (const auto iterIndex = parseIterIndex(expr)) expr = iterIndex;
        }
        if (matchAndConsume(T_DOUBLE_COLON)) {
            expr = parseMetaSelection(expr);
        }
        exprs.push_back(expr);
        if (!matchAndConsume(T_DOT)) break;
    }

    if (exprs.empty()) {
        reset(startIndex);
        return nullptr;
    }

    if (exprs.size() == 1) {
        assert(exprs.front() == firstExpr);
        freeExpr(exprs.front());
        reset(startIndex);
        return nullptr;
    }
    auto const selection = new LgsSelection(exprs);
    selection->location = firstExpr->location;
    return selection;
}

LgsMetaSelection* LgsParser::parseMetaSelection(LgsExpr* baseExpr) {
    const auto startIndex = currentToken;
    LgsExpr* expr = nullptr;
    if (const auto funcCall = parseFuncCall()) {
        expr = funcCall;
    } else if (const auto variable = parseVariable()) {
        expr = variable;
    }
    const auto metaSelection = new LgsMetaSelection(baseExpr, expr);
    metaSelection->location = baseExpr->location;
    setLocation(metaSelection->location, &startIndex, &startIndex);
    return metaSelection;
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
            addError(E10054, expr->location, {argName});
            break;
        }
        instance->args.emplace(argName, LgsInstanceArg{argName, expr});
        if (currentToken.type == T_RBRACE) break;
        mustMatch(T_COMMA);
    }
    if (currentToken.type == T_COMMA) consume();
}

void LgsParser::parsePackageString(LgsImportPkg& pkg, const LgsToken& importToken) {
    const auto importName = importToken.lexeme;
    const auto colonPos = importName.find(':');
    if (colonPos == std::string::npos) {
        errHandler.addError(E60000, {importName});
        return;
    }

    // URL
    const auto pkgPath = importName.substr(0, colonPos);
    if (pkgPath.starts_with("http:")) {
        errHandler.addError(E60001, {pkgPath});
        return;
    }
    pkg.path = pkgPath;
    // Version
    const auto version = importName.substr(colonPos + 1);
    if (!pkg.version.setVersion(version)) {
        errHandler.addError(E10068, &importToken.location, filePath, {version});
        return;
    }

    // Name
    const auto lastSlash = pkgPath.find_last_of('/');
    if (lastSlash != std::string::npos) {
        pkg.name = pkgPath.substr(lastSlash + 1);
    } else {
        pkg.name = pkgPath;
    }
}

void LgsParser::parseImports() {
    const auto importToken = currentToken;
    if (!matchAndConsume(T_IMPORT)) return;
    if (currentToken.lexeme == LGS_C) {
        const auto cToken = currentToken;
        consume();
        while (true) {
            if (currentToken.type != T_STRING) break;
            const auto importStmt = new LgsImport(LGS_C_IMPORT, currentToken.lexeme);
            setLocation(importStmt->location, &importToken, &currentToken);
            importPaths.emplace_back(importStmt);
            consume();
            if (cToken.location.lineStart != peek().location.lineStart) break;
            mustMatch(T_COMMA);
        }
    } else {
        while (true) {
            const auto var = currentToken;
            if (!mustMatch(T_IDENTIFIER)) break;
            const auto importStmt = new LgsImport(LGS_IMPORT, currentToken.lexeme);
            setLocation(importStmt->location, &importToken, &currentToken);
            importPaths.emplace_back(importStmt);
            if (importToken.location.lineStart != peek().location.lineStart) break;
            mustMatch(T_COMMA);
        }
    }
}

void LgsParser::setLocation(LgsLocation& location, const LgsToken* startToken, const LgsToken* endToken) const {
    location.filepath = &filePath;
    location.lineStart = startToken->location.lineStart;
    location.columnStart = startToken->location.columnStart;
    location.lineEnd = endToken->location.lineEnd;
    location.columnEnd = endToken->location.columnEnd;
}

void LgsParser::extractStrParts(LgsStrConst* strConst) {
    size_t start = 0;
    std::string replaced = strConst->value;
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
        LgsParser parser(filePath, paths, globals);
        parser.lgsCode = part;
        parser.scanTokens();
        const auto expr = parser.parseExpr();
        strConst->parts.push_back(expr);
        replaced.replace(open, close + 1, LGS_STR_FMT_PLACEHOLDER);
        start = open + strlen(LGS_STR_FMT_PLACEHOLDER);
    }
    if (replaced == strConst->value) return;
    strConst->formatedStr = replaced;
}

std::pair<size_t, size_t> LgsParser::extractMatDims(const LgsToken& matToken) {
    const auto matName = matToken.lexeme;
    // Matrix type is presented as 'MatNxM' where N and M are numbers
    const auto xPos = matName.find('x');
    const auto rowsStr = matName.substr(3, xPos - 3);
    const auto colsStr = matName.substr(xPos + 1);
    assert(std::ranges::all_of(rowsStr.begin(), rowsStr.end(), ::isdigit));
    assert(std::ranges::all_of(colsStr.begin(), colsStr.end(), ::isdigit));
    const auto rows = std::stoi(rowsStr);
    const auto columns = std::stoi(colsStr);
    if (rows == 0 || columns == 0) {
        addError(E10112, matToken.location);
    }
    return std::make_pair(rows, columns);
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
        errHandler.addError(E10079, {testFile->path.filename()});
    }
}

bool fitsIn(const std::string& value, const std::string& limit) {
    if (value.size() != limit.size()) {
        return value.size() < limit.size();
    }
    return value <= limit;
}

LgsExpr* LgsParser::determineIntConst(const std::string& tokenStr, const int base) {
    auto str = tokenStr;
    if (tokenStr.starts_with("0b") || tokenStr.starts_with("0x")) {
        str = tokenStr.substr(2).c_str();
    }
    const bool negative = str[0] == '-';
    const auto digits = negative ? str.substr(1) : str;
    const auto v = strtoll(str.c_str(), nullptr, base);
    LgsType* type = nullptr;
    if (fitsIn(digits, std::to_string(std::numeric_limits<int32_t>::max()))) {
        type = &LGS_INT;
    } else if (fitsIn(digits, std::to_string(std::numeric_limits<long>::max())) || fitsIn(digits, std::to_string(std::numeric_limits<int64_t>::max()))) {
        type = &LGS_LONG;
    }
    const auto expr = new LgsIntConst(type, v);
    setLocation(expr->location, &currentToken, &currentToken);
    return expr;
}

int LgsParser::getBinOpPrecedence(const LgsBinOpType opType) {
    switch (opType) {
    case OR:
        return 1;
    case AND:
        return 2;
    case BIT_OR:
        return 3;
    case BIT_XOR:
        return 4;
    case BIT_AND:
        return 5;
    case EQ:
    case NE:
        return 6;
    case LT:
    case GT:
    case LE:
    case GE:
    case IN:
        return 7;
    case LSHIFT:
    case RSHIFT:
        return 8;
    case ADD:
    case SUB:
        return 9;
    case MUL:
    case DIV:
    case CROSS:
    case MODULO:
        return 10;
    case POW:
        return 11;
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
    assert(currentIndex < tokens.size());
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

bool LgsParser::validateTypeName(const std::string& typeName, const LgsLocation* location) {
    if (islower(typeName[0])) {
        errHandler.addError(E10033, location, filePath, {typeName});
        return false;
    }
    return true;
}

void LgsParser::addError(const LgsBaseMsg& lgsErr, const LgsLocation& location, const std::vector<std::string>& args) {
    errHandler.addError(lgsErr, &location, filePath, args);
}

void LgsParser::addParsingError(const LgsLocation* location) {
    const auto t = location ? *location : tokens[currentIndex].location;
    return errHandler.addError(E10085, &t, filePath, {});
}

void LgsParser::recursionGuard() {
    if (recursionCount++ < MAX_TOKENS_NUMBER) return;
    assert(0);
}

LgsFunc* wrapStmtsBlockWithLambda(LgsStmtsBlock* stmtsBlock) {
    const auto func = new LgsFunc("", nullptr);
    func->funcType->isLambda = true;
    func->location = stmtsBlock->location;
    func->stmtsBlock = stmtsBlock;
    return func;
}
