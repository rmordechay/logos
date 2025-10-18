#include "parser/LgsJsonParser.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsField.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsEnum.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/LgsSubType.h"

void LgsJsonParser::visitMainFile(LgsMainFile* mainFile) {
    openObject();

    openKeyArray("funcs");
    bool first = true;
    for (const auto& [funcName, func] : mainFile->funcs) {
        if (!first) json << ',';
        first = false;
        visitFunc(func);
    }
    closeArray(true);

    openKeyArray("object");
    first = true;
    for (const auto obj : mainFile->objects) {
        if (!first) json << ',';
        first = false;
        visitObject(obj);
    }
    closeArray(true);

    openKeyArray("interfaces");
    first = true;
    for (const auto interface : mainFile->interfaces) {
        if (!first) json << ',';
        first = false;
        visitInterface(interface);
    }
    closeArray(true);

    openKeyArray("enums");
    first = true;
    for (const auto enum_ : mainFile->enums) {
        if (!first) json << ',';
        first = false;
        visitEnum(enum_);
    }
    closeArray(true);

    openKeyArray("subtypes");
    first = true;
    for (const auto subtype : mainFile->subtypes) {
        if (!first) json << ',';
        first = false;
        visitSubtype(subtype);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::visitObject(LgsObject* obj) {
    openObject();
    addKeyValueStr("name", obj->name, true);

    openKeyArray("fields");
    bool first = true;
    for (const auto field : obj->fields) {
        if (!first) json << ',';
        first = false;
        visitField(field);
    }
    closeArray(true);

    openKeyArray("methods");
    first = true;
    for (const auto& [funcName, method] : obj->methods) {
        if (!first) json << ',';
        first = false;
        visitFunc(method);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::visitInterface(LgsInterface* interface) {
    openObject();
    addKeyValueStr("name", interface->name, true);

    openKeyArray("fields");
    bool first = true;
    for (const auto field : interface->fields) {
        if (!first) json << ',';
        first = false;
        visitField(field);
    }
    closeArray(true);

    openKeyArray("methods");
    first = true;
    for (const auto& [funcName, method] : interface->methods) {
        if (!first) json << ',';
        first = false;
        visitFunc(method);
    }
    closeArray();

    closeObject();
}

void LgsJsonParser::visitEnum(const LgsEnum* enum_) {
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

void LgsJsonParser::visitSubtype(LgsSubType* subtype) {
    assert(0);
}

void LgsJsonParser::visitField(const LgsField* field) {
    openObject();
    addKeyValueStr("name", field->name, true);
    addKeyValueStr("type", field->type->getName(), true);
    addKeyValueBool("isOwner", field->isOwner, true);
    addKeyValueBool("isConst", field->isConst, true);
    addKeyValueBool("isPublic", field->isPublic);
    closeObject();
}

void LgsJsonParser::visitFunc(const LgsFunc* func) {
    openObject();
    addKeyValueStr("name", func->funcType->name, true);
    addKeyValueStr("rt", func->funcType->rt->getName(), true);
    openKeyArray("params");
    bool first = true;
    for (const auto& param : func->funcType->params) {
        if (!first) json << ',';
        first = false;
        visitParam(&param);
    }
    closeArray(true);
    openKey("statements");
    if (func->stmtsBlock) visitStmtsBlock(func->stmtsBlock);
    else json << "[]";
    closeObject();
}

void LgsJsonParser::visitParam(const LgsParam* param) {
    openObject();
    addKeyValueStr("name", param->name, true);
    addKeyValueStr("type", param->type->pname());
    closeObject();
}

void LgsJsonParser::visitIOPair(LgsIOPair* ioPair, LgsObject* obj) {
    assert(0);
}

void LgsJsonParser::visitStmt(LgsStmt* stmt) {
    if (const auto pattern = stmt->asSwitch()) visitSwitch(pattern);
    else if (const auto ifStmt = stmt->asIfStmt()) visitIfStmt(ifStmt);
    else if (const auto varDec = stmt->asVarDec()) visitVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) visitLoopStmt(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) visitCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) visitDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) visitAssignment(assignment);
    else if (const auto funcCall = stmt->asFuncCall()) visitFuncCall(funcCall);
    else if (const auto postfixExpr = stmt->asPostfixExpr()) visitPostfixExpr(postfixExpr);
    else if (const auto selection = stmt->asSelection()) visitSelection(selection);
    else if (const auto returnStmt = stmt->asReturn()) visitReturnStmt(returnStmt);
    else if (const auto continueStmt = stmt->asContinue()) visitContinueStmt(continueStmt);
    else if (const auto ioStmt = stmt->asIOStmt()) visitIOStmt(ioStmt);
    else if (const auto breakStmt = stmt->asBreak()) visitBreakStmt(breakStmt);
    else if (auto expr = stmt->asExpr()) visitExpr(expr);
    else assert(0);
}

void LgsJsonParser::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    openArray();
    bool first = true;
    for (const auto stmt : stmtsBlock->stmts) {
        if (!first) json << ',';
        first = false;
        visitStmt(stmt);
    }
    closeArray();
}

void LgsJsonParser::visitVarDec(const LgsVarDec* varDec) {
    openObject();
    addKeyValueStr("kind", "Variable", true);
    addKeyValueStr("name", varDec->name);
    closeObject();
}

void LgsJsonParser::visitAssignment(LgsAssignment* assignment) {
    assert(0);
}

void LgsJsonParser::visitIfStmt(LgsIfStmt* ifStmt) {
    openObject();
    addKeyValueStr("kind", "IfStmt", true);
    openKey("ifCond");
    visitExpr(ifStmt->ifCond);
    closeObject();
}

void LgsJsonParser::visitSwitch(LgsSwitch* switchStmt) {
    openObject();
    addKeyValueStr("kind", "Switch");
    closeObject();
}

void LgsJsonParser::visitWhileLoop(LgsWhileLoop* whileLoop) {
    assert(0);
}

void LgsJsonParser::visitLoopStmt(LgsForLoop* loopStmt) {
    assert(0);
}

void LgsJsonParser::visitRangeLoop(LgsRangeLoop* rangeLoop) {
    assert(0);
}

void LgsJsonParser::visitForeachLoop(LgsForeachLoop* foreachLoop) {
    assert(0);
}

void LgsJsonParser::visitInfiniteLoop(const LgsInfiniteLoop* infiniteLoop) {
    assert(0);
}

void LgsJsonParser::visitReturnStmt(LgsReturn* returnStmt) {
    assert(0);
}

void LgsJsonParser::visitContinueStmt(const LgsContinue* continueStmt) {
    assert(0);
}

void LgsJsonParser::visitBreakStmt(const LgsBreak* breakStmt) {
    assert(0);
}

void LgsJsonParser::visitCoroutine(const LgsCoroutine* coroutine) {
    assert(0);
}

void LgsJsonParser::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    assert(0);
}

void LgsJsonParser::visitIOStmt(const LgsIOStmt* ioStmt) {
    assert(0);
}

void LgsJsonParser::visitExpr(LgsExpr*& expr) {
    if (!expr) return;
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        visitTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (const auto variable = expr->asVariable()) return visitVariable(variable);
        if (const auto lambda = expr->asFunc()) return visitFunc(lambda);
        if (const auto intConst = expr->asIntConst()) return visitIntConst(intConst);
        if (const auto instance = expr->asInstance()) return visitInstance(instance);
        if (const auto funcCall = expr->asFuncCall()) return visitFuncCall(funcCall);
        if (const auto strConst = expr->asStrConst()) return visitStrConst(strConst);
        if (const auto selection = expr->asSelection()) return visitSelection(selection);
        if (const auto arrayExpr = expr->asArrayExpr()) return visitArrayExpr(arrayExpr);
        if (const auto hashMap = expr->asHashMap()) return visitHashMap(hashMap);
        if (const auto iterIndex = expr->asIterIndex()) return visitIterIndex(iterIndex);
        if (const auto postfixExpr = expr->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
        if (const auto prefixExpr = expr->asPrefixExpr()) return visitPrefixExpr(prefixExpr);
        if (const auto forVar = expr->asLoopMetaVar()) return visitLoopMetaVar(forVar);
        if (const auto vecExpr = expr->asVectorExpr()) return visitVectorExpr(vecExpr);
        if (const auto nullableExpr = expr->asNullableExpr()) return visitExpr(nullableExpr->baseExpr);
        if (const auto castExpr = expr->asCast()) return visitCast(castExpr);
        if (const auto jsonExpr = expr->asJson()) return visitJson(jsonExpr);
        assert(0);
    }
}

void LgsJsonParser::visitBinaryExpr(const LgsBinaryExpr* binaryExpr) {
    openObject();
    addKeyValueStr("kind", "BinaryExpr", true);
    addKeyValueStr("operator", binaryExpr->op.name);
    closeObject();
}

void LgsJsonParser::visitTernaryExpr(LgsTernaryExpr* ternary) {
    openObject();
    addKeyValueStr("kind", "BinaryExpr");
    closeObject();
}

void LgsJsonParser::visitCast(LgsCast* cast) {
    assert(0);
}

void LgsJsonParser::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsJsonParser::visitStaticArray(const LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsJsonParser::visitDynamicArray(LgsArrayExpr* arrayExpr) {
    assert(0);
}

void LgsJsonParser::visitHashMap(LgsHashMap* hashMap) {
    assert(0);
}

void LgsJsonParser::visitVectorExpr(const LgsVectorExpr* vectorExpr) {
    assert(0);
}

void LgsJsonParser::visitVariable(const LgsVariable* variable) {
    openObject();
    addKeyValueStr("kind", "Variable", true);
    addKeyValueStr("name", variable->name);
    closeObject();
}

void LgsJsonParser::visitSelection(const LgsSelection* selection) {
    openObject();
    addKeyValueStr("kind", "Selection", true);
    openKeyArray("exprs");
    bool first = true;
    for (auto expr : selection->exprs) {
        if (!first) json << ',';
        first = false;
        visitExpr(expr);
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::visitFuncCall(const LgsFuncCall* funcCall) {
    openObject();
    addKeyValueStr("kind", "FuncCall", true);
    addKeyValueStr("name", funcCall->name, true);
    openKey("args");
    openArray();
    bool first = true;
    for (auto arg : funcCall->args) {
        if (!first) json << ',';
        first = false;
        visitExpr(arg);
    }
    closeArray();
    closeObject();
}

void LgsJsonParser::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    assert(0);
}

void LgsJsonParser::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    assert(0);
}

void LgsJsonParser::visitStrConst(const LgsStrConst* strConst) {
    openObject();
    addKeyValueStr("kind", "IntConst", true);
    addKeyValueStr("value", strConst->value);
    closeObject();
}

void LgsJsonParser::visitTypeExpr(LgsTypeExpr* typeExpr) {
    assert(0);
}

void LgsJsonParser::visitJson(const LgsJson* jsonStmt) {
    assert(0);
}

void LgsJsonParser::visitInstance(LgsInstance* instance) {
    assert(0);
}

void LgsJsonParser::visitIntConst(const LgsIntConst* intConst) {
    openObject();
    addKeyValueStr("kind", "IntConst", true);
    addKeyValueStr("type", intConst->type->pname(), true);
    addKeyValueInt("value", intConst->value);
    closeObject();
}

void LgsJsonParser::visitInterfaceInstance(LgsInstance* instance, LgsInterface* interface) {
    assert(0);
}

void LgsJsonParser::visitIterIndex(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsJsonParser::visitIndex(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsJsonParser::visitSlice(LgsIterIndex* iterIndex) {
    assert(0);
}

void LgsJsonParser::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
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