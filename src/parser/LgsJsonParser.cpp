#include "parser/LgsJsonParser.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsNull.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsMainFile.h"
#include "files/LgsObjectFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

void LgsJsonParser::parseFile(LgsFile* file) {
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(file)) {
        parseMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(file)) {
        parseObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(file)) {
        parseInterface(interfaceFile->interface);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(file)) {
        parseTestFile(testFile);
    } else {
        assert(0);
    }
}

void LgsJsonParser::parseMainFile(LgsMainFile* mainFile) {
    openObject();

    openKeyArray("funcs");
    bool first = true;
    for (const auto& [funcName, func] : mainFile->funcs) {
        if (!first) json << ',';
        first = false;
        parseFunc(func);
    }
    closeArray(true);

    openKeyArray("object");
    first = true;
    for (const auto obj : mainFile->objects) {
        if (!first) json << ',';
        first = false;
        parseObject(obj);
    }
    closeArray(true);

    openKeyArray("interfaces");
    first = true;
    for (const auto interface : mainFile->interfaces) {
        if (!first) json << ',';
        first = false;
        parseInterface(interface);
    }
    closeArray(true);

    openKeyArray("enums");
    first = true;
    for (const auto enum_ : mainFile->enums) {
        if (!first) json << ',';
        first = false;
        parseEnum(enum_);
    }
    closeArray(true);

    openKeyArray("subtypes");
    first = true;
    for (const auto subtype : mainFile->subtypes) {
        if (!first) json << ',';
        first = false;
        parseSubtype(subtype);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::parseTestFile(LgsTestFile* testFile) {
    assert(0);
}

void LgsJsonParser::parseObject(LgsObject* obj) {
    openObject();
    addKeyValueStr("name", obj->name, true);

    openKeyArray("fields");
    bool first = true;
    for (const auto field : obj->fields) {
        if (!first) json << ',';
        first = false;
        parseField(field);
    }
    closeArray(true);

    openKeyArray("methods");
    first = true;
    for (const auto& [funcName, method] : obj->methods) {
        if (!first) json << ',';
        first = false;
        parseFunc(method);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::parseInterface(LgsInterface* interface) {
    openObject();
    addKeyValueStr("name", interface->name, true);

    openKeyArray("fields");
    bool first = true;
    for (const auto field : interface->fields) {
        if (!first) json << ',';
        first = false;
        parseField(field);
    }
    closeArray(true);

    openKeyArray("methods");
    first = true;
    for (const auto& [funcName, method] : interface->methods) {
        if (!first) json << ',';
        first = false;
        parseFunc(method);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::parseEnum(const LgsEnum* enum_) {
    openObject();
    addKeyValueStr("name", enum_->name);
    json << ',';
    openKeyArray("fields");
    auto first = true;
    for (const auto f : enum_->fields) {
        if (!first) json << ',';
        first = false;
        openObject();
        addKeyValueStr("name", f->name);
        closeObject();
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::parseSubtype(LgsSubType* subtype) {
    assert(0);
}

void LgsJsonParser::parseField(const LgsField* field) {
    openObject();
    addKeyValueStr("name", field->name, true);
    addKeyValueStr("type", field->type->getName(), true);
    addKeyValueBool("isOwner", field->isOwner, true);
    addKeyValueBool("isConst", field->isConst, true);
    addKeyValueBool("isPublic", field->isPublic);
    closeObject();
}

void LgsJsonParser::parseFunc(const LgsFunc* func) {
    openObject();
    addKeyValueStr("name", func->funcType->name, true);
    addKeyValueStr("rt", func->funcType->rt->getName(), true);
    openKeyArray("params");
    bool first = true;
    for (const auto& param : func->funcType->params) {
        if (!first) json << ',';
        first = false;
        parseParam(&param);
    }
    closeArray(true);
    openKey("statements");
    if (func->stmtsBlock) parseStmtsBlock(func->stmtsBlock);
    else json << "[]";
    closeObject();
}

void LgsJsonParser::parseParam(const LgsParam* param) {
    openObject();
    addKeyValueStr("name", param->name, true);
    addKeyValueStr("type", param->type->pname());
    closeObject();
}

void LgsJsonParser::parseIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    assert(0);
}

void LgsJsonParser::parseStmt(LgsStmt* stmt) {
    if (const auto pattern = stmt->asSwitch()) parseSwitch(pattern);
    else if (const auto ifStmt = stmt->asIfStmt()) parseIfStmt(ifStmt);
    else if (const auto varDec = stmt->asVarDec()) parseVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) parseLoopStmt(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) parseCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) parseDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) parseAssignment(assignment);
    else if (const auto funcCall = stmt->asFuncCall()) parseFuncCall(funcCall);
    else if (const auto postfixExpr = stmt->asPostfixExpr()) parsePostfixExpr(postfixExpr);
    else if (const auto selection = stmt->asSelection()) parseSelection(selection);
    else if (const auto returnStmt = stmt->asReturn()) parseReturnStmt(returnStmt);
    else if (const auto continueStmt = stmt->asContinue()) parseContinueStmt(continueStmt);
    else if (const auto ioStmt = stmt->asIOStmt()) parseIOStmt(ioStmt);
    else if (const auto breakStmt = stmt->asBreak()) parseBreakStmt(breakStmt);
    else if (auto expr = stmt->asExpr()) parseExpr(expr);
    else assert(0);
}

void LgsJsonParser::parseStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    openArray();
    bool first = true;
    for (const auto stmt : stmtsBlock->stmts) {
        if (!first) json << ',';
        first = false;
        parseStmt(stmt);
    }
    closeArray();
}

void LgsJsonParser::parseVarDec(const LgsVarDec* varDec) {
    openObject();
    addKeyValueStr("kind", "Variable", true);
    addKeyValueStr("name", varDec->name);
    closeObject();
}

void LgsJsonParser::parseAssignment(LgsAssignment* assignment) {
    assert(0);
}

void LgsJsonParser::parseIfStmt(LgsIfStmt* ifStmt) {
    openObject();
    addKeyValueStr("kind", "IfStmt", true);
    openKey("ifCond");
    parseExpr(ifStmt->ifCond);
    closeObject();
}

void LgsJsonParser::parseSwitch(LgsSwitch* switchStmt) {
    openObject();
    addKeyValueStr("kind", "Switch");
    closeObject();
}

void LgsJsonParser::parseWhileLoop(LgsWhileLoop* whileLoop) {
    assert(0);
}

void LgsJsonParser::parseLoopStmt(LgsForLoop* loopStmt) {
    assert(0);
}

void LgsJsonParser::parseRangeLoop(LgsRangeLoop* rangeLoop) {
    assert(0);
}

void LgsJsonParser::parseForeachLoop(LgsForeachLoop* foreachLoop) {
    assert(0);
}

void LgsJsonParser::parseInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    assert(0);
}

void LgsJsonParser::parseReturnStmt(LgsReturn* returnStmt) {
    assert(0);
}

void LgsJsonParser::parseContinueStmt(const LgsContinue* continueStmt) {
    assert(0);
}

void LgsJsonParser::parseBreakStmt(const LgsBreak* breakStmt) {
    assert(0);
}

void LgsJsonParser::parseCoroutine(const LgsCoroutine* coroutine) {
    assert(0);
}

void LgsJsonParser::parseDeferStmt(const LgsDeferStmt* deferStmt) {
    assert(0);
}

void LgsJsonParser::parseIOStmt(const LgsIOStmt* ioStmt) {
    assert(0);
}

void LgsJsonParser::parseExpr(LgsExpr*& expr) {
    if (!expr) return;
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        parseTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        parseBinaryExpr(binaryExpr);
    } else {
        if (const auto variable = expr->asVariable()) return parseVariable(variable);
        if (const auto lambda = expr->asFunc()) return parseFunc(lambda);
        if (const auto intConst = expr->asIntConst()) return parseIntConst(intConst);
        if (const auto instance = expr->asInstance()) return parseInstance(instance);
        if (const auto funcCall = expr->asFuncCall()) return parseFuncCall(funcCall);
        if (const auto strConst = expr->asStrConst()) return parseStrConst(strConst);
        if (const auto selection = expr->asSelection()) return parseSelection(selection);
        if (const auto arrayExpr = expr->asArrayExpr()) return parseArrayExpr(arrayExpr);
        if (const auto hashMap = expr->asHashMap()) return parseHashMap(hashMap);
        if (const auto iterIndex = expr->asIterIndex()) return parseIterIndex(iterIndex);
        if (const auto postfixExpr = expr->asPostfixExpr()) return parsePostfixExpr(postfixExpr);
        if (const auto prefixExpr = expr->asPrefixExpr()) return parsePrefixExpr(prefixExpr);
        if (const auto forVar = expr->asLoopMetaVar()) return parseLoopMetaVar(forVar);
        if (const auto vecExpr = expr->asVectorExpr()) return parseVectorExpr(vecExpr);
        if (const auto null = expr->asNull()) return parseNull(null);
        if (const auto castExpr = expr->asCast()) return parseCast(castExpr);
        if (const auto jsonExpr = expr->asJson()) return parseJson(jsonExpr);
        assert(0);
    }
}

void LgsJsonParser::parseBinaryExpr(const LgsBinaryExpr* binaryExpr) {
    openObject();
    addKeyValueStr("kind", "BinaryExpr", true);
    addKeyValueStr("operator", binaryExpr->op.name);
    closeObject();
}

void LgsJsonParser::parseTernaryExpr(LgsTernaryExpr* ternary) {
    openObject();
    addKeyValueStr("kind", "BinaryExpr");
    closeObject();
}

void LgsJsonParser::parseCast(LgsCast* cast) {
    assert(0);
}

void LgsJsonParser::parseArrayExpr(LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsJsonParser::parseStaticArray(const LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsJsonParser::parseDynamicArray(LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsJsonParser::parseHashMap(LgsHashMap* hashMap) {
    assert(0);
}

void LgsJsonParser::parseVectorExpr(const LgsVectorExpr* vectorExpr) {
    assert(0);
}

void LgsJsonParser::parseVariable(const LgsVariable* variable) {
    openObject();
    addKeyValueStr("kind", "Variable", true);
    addKeyValueStr("name", variable->name);
    closeObject();
}

void LgsJsonParser::parseSelection(const LgsSelection* selection) {
    openObject();
    addKeyValueStr("kind", "Selection", true);
    openKeyArray("exprs");
    bool first = true;
    for (auto expr : selection->exprs) {
        if (!first) json << ',';
        first = false;
        parseExpr(expr);
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::parseFuncCall(const LgsFuncCall* funcCall) {
    openObject();
    addKeyValueStr("kind", "FuncCall", true);
    addKeyValueStr("name", funcCall->name, true);
    openKey("args");
    openArray();
    bool first = true;
    for (auto arg : funcCall->args) {
        if (!first) json << ',';
        first = false;
        parseExpr(arg);
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::parsePrefixExpr(LgsPrefixExpr* prefixExpr) {
    assert(0);
}

void LgsJsonParser::parsePostfixExpr(LgsPostfixExpr* postfixExpr) {
    assert(0);
}

void LgsJsonParser::parseStrConst(const LgsStrConst* strConst) {
    openObject();
    addKeyValueStr("kind", "IntConst", true);
    addKeyValueStr("value", strConst->value);
    closeObject();
}

void LgsJsonParser::parseTypeExpr(LgsTypeExpr* typeExpr) {
    assert(0);
}

void LgsJsonParser::parseJson(const LgsJson* jsonStmt) {
    assert(0);
}

void LgsJsonParser::parseInstance(LgsInstance* instance) {
    assert(0);
}

void LgsJsonParser::parseNull(LgsNull* null) {
    assert(0);
}

void LgsJsonParser::parseIntConst(const LgsIntConst* intConst) {
    openObject();
    addKeyValueStr("kind", "IntConst", true);
    addKeyValueStr("type", intConst->type->pname(), true);
    addKeyValueInt("value", intConst->value);
    closeObject();
}

void LgsJsonParser::parseInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    assert(0);
}

void LgsJsonParser::parseIterIndex(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsJsonParser::parseIndex(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsJsonParser::parseSlice(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsJsonParser::parseLoopMetaVar(LgsLoopMetaVar* metaVar) {
    assert(0);
}

void LgsJsonParser::addString(const std::string& v) {
    json << '"' << v << '"';
}

void LgsJsonParser::addBool(const bool v) {
    json << (v ? "true" : "false");
}

void LgsJsonParser::openArray() {
    json << '[';
}

void LgsJsonParser::closeArray(const bool withComma) {
    json << (withComma ? "]," : "]");
}

void LgsJsonParser::openObject() {
    json << '{';
}

void LgsJsonParser::closeObject(const bool withComma) {
    json << (withComma ? "}," : "}");
}

void LgsJsonParser::openKey(const std::string& v) {
    addString(v);
    json << ':';
}

void LgsJsonParser::openKeyArray(const std::string& v) {
    addString(v);
    json << ":[";
}

void LgsJsonParser::openKeyObject(const std::string& v) {
    addString(v);
    json << ":{";
}

void LgsJsonParser::addKeyValueStr(const std::string& k, const std::string& v, const bool withComma) {
    openKey(k);
    addString(v);
    if (withComma) json << ',';
}

void LgsJsonParser::addKeyValueInt(const std::string& k, const size_t v, const bool withComma) {
    openKey(k);
    json << v;
    if (withComma) json << ',';
}

void LgsJsonParser::addKeyValueBool(const std::string& k, const bool v, const bool withComma) {
    openKey(k);
    addBool(v);
    if (withComma) json << ',';
}