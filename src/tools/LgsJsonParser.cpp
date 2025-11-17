#include "../../include/tools/LgsJsonParser.h"
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
#include "stmts/LgsAssignment.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

#include <llvm/IR/InlineAsm.h>

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
    bool isFirst = true;
    for (const auto& [funcName, func] : mainFile->funcs) {
        if (!isFirst) addComma();
        isFirst = false;
        parseFunc(func);
    }
    closeArray(true);

    openKeyArray("object");
    for (size_t i = 0; i < mainFile->objects.size(); ++i) {
        if (i > 0) addComma();
        parseObject(mainFile->objects[i]);
    }
    closeArray(true);

    openKeyArray("interfaces");
    for (size_t i = 0; i < mainFile->interfaces.size(); ++i) {
        if (i > 0) addComma();
        parseInterface(mainFile->interfaces[i]);
    }
    closeArray(true);

    openKeyArray("enums");
    for (size_t i = 0; i < mainFile->enums.size(); ++i) {
        if (i > 0) addComma();
        parseEnum(mainFile->enums[i]);
    }
    closeArray(true);

    openKeyArray("subtypes");
    for (size_t i = 0; i < mainFile->subtypes.size(); ++i) {
        if (i > 0) addComma();
        parseSubtype(mainFile->subtypes[i]);
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
    for (size_t i = 0; i < obj->fields.size(); ++i) {
        if (i > 0) addComma();
        parseField(obj->fields[i]);
    }
    closeArray(true);

    openKeyArray("methods");
    bool isFirst = true;
    for (const auto& [funcName, method] : obj->methods) {
        if (!isFirst) addComma();
        isFirst = false;
        parseFunc(method);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::parseInterface(LgsInterface* interface) {
    openObject();
    addKeyValueStr("name", interface->getName(), true);
    openKeyArray("fields");
    for (size_t i = 0; i < interface->fields.size(); ++i) {
        if (i > 0) addComma();
        parseField(interface->fields[i]);
    }
    closeArray(true);
    openKeyArray("methods");
    bool isFirst = true;
    for (const auto& [funcName, method] : interface->methods) {
        if (!isFirst) addComma();
        isFirst = false;
        parseFunc(method);
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::parseEnum(LgsEnum* enum_) {
    openObject();
    addKeyValueStr("name", enum_->getName());
    addComma();
    openKeyArray("fields");
    for (size_t i = 0; i < enum_->fields.size(); ++i) {
        if (i > 0) addComma();
        openObject();
        addKeyValueStr("name", enum_->fields[i]->name);
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
    for (size_t i = 0; i < func->funcType->params.size(); ++i) {
        if (i > 0) addComma();
        parseParam(&func->funcType->params[i]);
    }
    closeArray(true);
    openKey("stmtsBlock");
    parseStmtsBlock(func->stmtsBlock);
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
    if (stmtsBlock) {
        for (size_t i = 0; i < stmtsBlock->stmts.size(); ++i) {
            if (i > 0) addComma();
            parseStmt(stmtsBlock->stmts[i].stmt);
        }
    }
    closeArray();
}

void LgsJsonParser::parseVarDec(const LgsVarDec* varDec) {
    openObject();
    addKeyValueStr("kind", "variable", true);
    addKeyValueStr("name", varDec->name);
    closeObject();
}

void LgsJsonParser::parseAssignment(LgsAssignment* assignment) {
    openObject();
    addKeyValueStr("kind", "assignment", true);
    openKey("leftExpr");
    parseExpr(assignment->lValue);
    addComma();
    openKey("rightExpr");
    parseExpr(assignment->rValue);
    addComma();
    addKeyValueStr("op", assignment->getAssignTypeStr());
    closeObject();
}

void LgsJsonParser::parseIfStmt(LgsIfStmt* ifStmt) {
    openObject();
    addKeyValueStr("kind", "ifStmt", true);
    openKey("ifCond");
    parseExpr(ifStmt->ifCond);
    addComma();
    openKey("ifStmtsBlock");
    parseStmtsBlock(ifStmt->ifBlock);
    closeObject();
}

void LgsJsonParser::parseSwitch(LgsSwitch* switchStmt) {
    openObject();
    addKeyValueStr("kind", "switch");
    closeObject();
}

void LgsJsonParser::parseWhileLoop(LgsWhileLoop* whileLoop) {
    openObject();
    addKeyValueStr("kind", "whileLoop");
    closeObject();
}

void LgsJsonParser::parseLoopStmt(LgsForLoop* loopStmt) {
    openObject();
    addKeyValueStr("kind", "loopStmt");
    closeObject();
}

void LgsJsonParser::parseRangeLoop(LgsRangeLoop* rangeLoop) {
    openObject();
    addKeyValueStr("kind", "rangeLoop");
    closeObject();
}

void LgsJsonParser::parseForeachLoop(LgsForeachLoop* foreachLoop) {
    openObject();
    addKeyValueStr("kind", "foreachLoop");
    closeObject();
}

void LgsJsonParser::parseInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    openObject();
    addKeyValueStr("kind", "infiniteLoop");
    closeObject();
}

void LgsJsonParser::parseReturnStmt(LgsReturn* returnStmt) {
    openObject();
    addKeyValueStr("kind", "returnStmt");
    closeObject();
}

void LgsJsonParser::parseContinueStmt(const LgsContinue* continueStmt) {
    openObject();
    addKeyValueStr("kind", "continueStmt");
    closeObject();
}

void LgsJsonParser::parseBreakStmt(const LgsBreak* breakStmt) {
    openObject();
    addKeyValueStr("kind", "break");
    closeObject();
}

void LgsJsonParser::parseCoroutine(const LgsCoroutine* coroutine) {
    openObject();
    addKeyValueStr("kind", "coroutine");
    closeObject();
}

void LgsJsonParser::parseDeferStmt(const LgsDeferStmt* deferStmt) {
    openObject();
    addKeyValueStr("kind", "deferStmt");
    closeObject();
}

void LgsJsonParser::parseIOStmt(const LgsIOStmt* ioStmt) {
    openObject();
    addKeyValueStr("kind", "ioStmt");
    closeObject();
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
    addKeyValueStr("kind", "binaryExpr", true);
    addKeyValueStr("operator", binaryExpr->opText);
    closeObject();
}

void LgsJsonParser::parseTernaryExpr(LgsTernaryExpr* ternary) {
    openObject();
    addKeyValueStr("kind", "binaryExpr");
    closeObject();
}

void LgsJsonParser::parseCast(LgsCast* cast) {
    openObject();
    addKeyValueStr("kind", "cast");
    closeObject();
}

void LgsJsonParser::parseArrayExpr(LgsArrayExpr* arrayExpr) {
    openObject();
    addKeyValueStr("kind", "arrayExpr");
    closeObject();
}

void LgsJsonParser::parseStaticArray(const LgsArrayExpr* arrayExpr) {
    openObject();
    addKeyValueStr("kind", "arrayExpr");
    closeObject();
}

void LgsJsonParser::parseDynamicArray(LgsArrayExpr* arrayExpr) {
    openObject();
    addKeyValueStr("kind", "arrayExpr");
    closeObject();
}

void LgsJsonParser::parseHashMap(LgsHashMap* hashMap) {
    openObject();
    addKeyValueStr("kind", "hashMap");
    closeObject();
}

void LgsJsonParser::parseVectorExpr(const LgsVectorExpr* vectorExpr) {
    openObject();
    addKeyValueStr("kind", "variable");
    closeObject();
}

void LgsJsonParser::parseVariable(const LgsVariable* variable) {
    openObject();
    addKeyValueStr("kind", "variable", true);
    addKeyValueStr("name", variable->name);
    closeObject();
}

void LgsJsonParser::parseSelection(LgsSelection* selection) {
    openObject();
    addKeyValueStr("kind", "selection", true);
    openKeyArray("exprs");
    for (size_t i = 0; i < selection->exprs.size(); ++i) {
        if (i > 0) addComma();
        parseExpr(selection->exprs[i]);
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::parseFuncCall(LgsFuncCall* funcCall) {
    openObject();
    addKeyValueStr("kind", "funcCall", true);
    addKeyValueStr("name", funcCall->name, true);
    openKey("args");
    openArray();
    for (size_t i = 0; i < funcCall->args.size(); ++i) {
        if (i > 0) addComma();
        parseExpr(funcCall->args[i].expr);
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
    addKeyValueStr("kind", "strConst", true);
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
    addKeyValueStr("kind", "intConst", true);
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

void LgsJsonParser::parseLoopMetaVar(LgsMetaVar* metaVar) {
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
    if (withComma) addComma();
}

void LgsJsonParser::addKeyValueInt(const std::string& k, const size_t v, const bool withComma) {
    openKey(k);
    json << v;
    if (withComma) addComma();
}

void LgsJsonParser::addKeyValueBool(const std::string& k, const bool v, const bool withComma) {
    openKey(k);
    addBool(v);
    if (withComma) addComma();
}

void LgsJsonParser::addComma() {
    json << ',';
}
