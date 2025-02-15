#include "SemaAnalyser.h"
#include "LogosErrors.h"
#include "exprs/LogosBinaryExpr.h"
#include "funcs/LogosUserFunc.h"
#include "stmts/LogosFieldDef.h"

#include <format>

bool SemaAnalyser::analyse() {
    collectGlobals();
    ThreadPool threadPool;
    for (const auto [name, file] : files) {
        threadPool.runTask([this, file] {
            visitLogosFile(file);
        });
    }
    threadPool.wait();
    return successful;
}

void SemaAnalyser::collectGlobals() {
    for (const auto [name, file] : files) {
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
    for (const auto func : mainFile->funcs) {
        visitUserFunc(func);
    }
}

void SemaAnalyser::visitObjectFile(const LogosObjectFile* objectFile) {
    if (!objectFile) return;
    visitObject(objectFile->obj);
}

void SemaAnalyser::visitObject(const LogosObject* object) {
    if (!object) return;
    for (const auto entry : object->fields) {
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
    for (const auto param : func->params) {
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
    if (const auto ifStmt = dynamic_cast<const LogosIf*>(stmt)) {
        visitIfStmt(ifStmt);
    }
    if (const auto fieldDef = dynamic_cast<const LogosFieldDef*>(stmt)) {
        visitFieldDef(fieldDef);
    }
}

void SemaAnalyser::visitStmtBlock(LogosStmtBlock* stmtBlock) {
    for (const auto stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitField(LogosField* field) {

}

void SemaAnalyser::visitFieldDef(const LogosFieldDef* fieldDef) {
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
}

void SemaAnalyser::visitIfStmt(const LogosIf* ifStmt) {
    if (!ifStmt) return;
}

void SemaAnalyser::visitExpr(const LogosExpr* expr) {
    if (!expr) return;
    if (const auto unaryExpr = dynamic_cast<const LogosUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    }
    if (const auto binaryExpr = dynamic_cast<const LogosBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
}

void SemaAnalyser::visitUnaryExpr(const LogosUnaryExpr* unaryExpr) {
    if (!unaryExpr) return;
    if (const auto constructor = dynamic_cast<const LogosConstructor*>(unaryExpr)) {
        visitConstructor(constructor);
    }
    if (const auto funcCall = dynamic_cast<const LogosFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    }
}

void SemaAnalyser::visitBinaryExpr(const LogosBinaryExpr* binaryExpr) {
}

void SemaAnalyser::visitConstructor(const LogosConstructor* constructorExpr) {
    if (!constructorExpr) return;
    const auto symbol = theStack.getSymbol(constructorExpr->name);
    const auto obj = symbol->object;
    constructorExpr->type = obj;
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

void SemaAnalyser::checkTypes(LogosVarDec* varDec, LogosType* type) {
    const auto userType = varDec->userType;
    if (userType && *userType != type) {
        printError(101, &varDec->position, *userType, type->name());
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
    for (const auto file : files) {
        delete file.second;
    }
}