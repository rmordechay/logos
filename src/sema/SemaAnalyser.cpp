#include "SemaAnalyser.h"
#include "LogosErrors.h"
#include "LogosUtils.h"
#include "exprs/LogosBinaryExpr.h"
#include "exprs/LogosSelection.h"
#include "funcs/LogosUserFunc.h"
#include "stmts/LogosFieldDef.h"

#include <format>
#include <stmts/LogosLoop.h>

bool SemaAnalyser::analyse() {
    collectGlobals();
    ThreadPool threadPool;
    for (const auto& [name, file] : files) {
        threadPool.runTask([this, file] {
            visitLogosFile(file);
        });
    }
    threadPool.wait();
    while (theStack.size() > 0) {
        theStack.pop();
    }
    return successful;
}

void SemaAnalyser::collectGlobals() {
    for (const auto& [name, file] : files) {
        if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
            const auto object = objFile->obj;
            theStack.addGlobalSymbol(object->name(), LogosSymbol(OBJECT, object));
        }
    }
}

void SemaAnalyser::visitLogosFile(LogosFile* file) {
    if (const auto mainFile = dynamic_cast<LogosMainFile*>(file)) {
        visitMainFile(mainFile);
    }
    if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
        visitObjectFile(objFile);
    }
}

void SemaAnalyser::visitMainFile(const LogosMainFile* mainFile) {
    visitMainFunc(mainFile->mainFunc, mainFile->path);
    for (const auto& func : mainFile->funcs) {
        visitUserFunc(func);
    }
}

void SemaAnalyser::visitObjectFile(const LogosObjectFile* objectFile) {
    if (!objectFile) return;
    visitObject(objectFile->obj);
}

void SemaAnalyser::visitObject(const LogosObject* object) {
    if (!object) return;
    for (const auto& entry : object->fields) {
        visitField(entry.second);
    }
}

void SemaAnalyser::visitMainFunc(const LogosUserFunc* mainFunc, const string& path) {
    if (!mainFunc) {
        printError(100, nullptr);
        return;
    }
    visitUserFunc(mainFunc);
}

void SemaAnalyser::visitUserFunc(const LogosUserFunc* func) {
    theStack.enterScope();
    for (const auto& param : func->params) {
        if (!func) return;
        visitVarDec(param);
    }
    visitStmtBlock(func->stmtBlock);
    theStack.exitScope();
}



void SemaAnalyser::visitStmt(LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<LogosVarDec*>(stmt)) {
        visitVarDec(varDec);
    }
    if (const auto ifStmt = dynamic_cast<LogosIf*>(stmt)) {
        visitIfStmt(ifStmt);
    }
    if (const auto loopStmt = dynamic_cast<LogosLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    }
    if (const auto fieldDef = dynamic_cast<LogosFieldDefinition*>(stmt)) {
        visitFieldDef(fieldDef);
    }
}

void SemaAnalyser::visitStmtBlock(LogosStmtBlock* stmtBlock) {
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitField(LogosField* field) {

}

void SemaAnalyser::visitFieldDef(const LogosFieldDefinition* fieldDef) {
}


void SemaAnalyser::visitVarDec(LogosVarDec* varDec) {
    visitExpr(varDec->expr);
    const auto inferredType = varDec->expr->type;
    const auto userType = varDec->userType;
    if (userType && *userType != inferredType) {
        printError(101, &varDec->position, *userType, inferredType->name());
    }
    if (inferredType) {
        varDec->inferredType = inferredType;
    }
    theStack.addLocalSymbol(varDec->name, Utils::createSymbol(varDec->expr));
}

void SemaAnalyser::visitIfStmt(const LogosIf* ifStmt) {
    if (!ifStmt) return;
}

void SemaAnalyser::visitLoopStmt(const LogosLoop* loopStmt) {
    if (!loopStmt) return;
}

void SemaAnalyser::visitExpr(LogosExpr* expr) {
    if (!expr) return;
    if (const auto unaryExpr = dynamic_cast<LogosUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    }
    if (const auto binaryExpr = dynamic_cast<LogosBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
    if (const auto selection = dynamic_cast<LogosSelection*>(expr)) {
        visitSelection(selection);
    }
}

void SemaAnalyser::visitUnaryExpr(LogosUnaryExpr* unaryExpr) {
    if (!unaryExpr) return;
    if (const auto instance = dynamic_cast<LogosInstance*>(unaryExpr)) {
        visitInstance(instance);
    }
    if (const auto funcCall = dynamic_cast<LogosFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    }
}

void SemaAnalyser::visitBinaryExpr(const LogosBinaryExpr* binaryExpr) {
}

void SemaAnalyser::visitSelection(const LogosSelection* selection) {
    if (!selection) return;
    selection->type = inferSelectionType(selection);
}

void SemaAnalyser::visitInstance(LogosInstance* instance) {
    if (!instance) return;
    const auto symbol = theStack.getSymbol(instance->name);
    const auto obj = symbol->object;
    instance->type = obj;
    instance->obj = obj;
}

void SemaAnalyser::visitFuncCall(const LogosFuncCall* funcCallExpr) {
    if (!funcCallExpr) return;
}

void SemaAnalyser::visitConstant(const LogosUnaryExpr* unaryExpr) {
    if (!unaryExpr) return;
}

void SemaAnalyser::setUnsuccessful() {
    unique_lock lock(mtx);
    successful = false;
}

LogosType* SemaAnalyser::inferSelectionType(const LogosSelection* selection) {
    auto previousExpr = selection->exprs[0];
    LogosUnaryExpr* nextExpr = nullptr;
    for (int i = 1; i < selection->exprs.size(); ++i) {
        nextExpr = selection->exprs[i];
        resolveSelection(previousExpr, nextExpr);
        previousExpr = nextExpr;
    }
    if (nextExpr) { // If true, nextExpr is the last element
        selection->type = nextExpr->type;
    }
    return nullptr;
}

void SemaAnalyser::resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = theStack.getSymbol(previousExpr->getName());
    switch (symbol->type) {
    case FIELD:
        break;
    case INSTANCE: {
        const auto obj = symbol->instance->obj;
        const auto func = obj->funcs[nextExpr->getName()];
        nextExpr->type = func->type;
        break;
    }
    case FUNC_CALL:
        break;
    case VARIABLE:
        break;
    case CONSTANT:
        break;
    default:
        break;
    }
}

template <typename... Args>
void SemaAnalyser::printError(const int errCode, Position *position, Args&&... args) {
    setUnsuccessful();
    const auto msgPair = LOGOS_ERRORS.find(errCode);
    // const auto formattedMessage = std::vformat(msgPair->second, std::make_format_args(args...));
    if (position) {
        cout <<  std::format("Error at {} {} {}: \n", *position->filePath, position->lineNumber, position->posInLine);
    } else {
        // cout << formattedMessage << endl;
    }
}

SemaAnalyser::~SemaAnalyser() {
    delete mainFile;
    for (const auto& file : files) {
        delete file.second;
    }
}