#include "SemaAnalyser.h"
#include "LogosErrors.h"

#include <__format/format_functions.h>

bool SemaAnalyser::analyse(const vector<LogosFile*>& files) {
    pool.start();
    for (const auto file : files) {
        pool.enqueueTask([this, file] {
            visitLogosFile(file);
        });
    }
    pool.wait();
    return successful;
}

void SemaAnalyser::visitLogosFile(LogosFile* file) {
    if (const auto mainFile = dynamic_cast<LogosMainFile*>(file)) {
        visitMainFile(mainFile);
    }
    if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
        visitObjectFile(objFile);
    }
    files[file->name] = file;
}

void SemaAnalyser::visitMainFile(const LogosMainFile* mainFile) {
    visitImportsStmts(mainFile->imports);
    visitMainFunc(mainFile->mainFunc);
    for (const auto func : mainFile->funcs) {
        visitFunc(func);
    }
}

void SemaAnalyser::visitObject(const LogosObject* object) {
    if (!object) return;
}

void SemaAnalyser::visitMainFunc(const LogosUserFunc* mainFunc) {
    if (!mainFunc) {
        printError(100);
        setUnsuccessful();
        return;
    }
}

void SemaAnalyser::visitImportsStmts(const vector<LogosImportStmt*>& importsStmts) {
    if (importsStmts.empty()) return;
}

void SemaAnalyser::visitObjectFile(const LogosObjectFile* objectFile) {
    if (!objectFile) return;
}

void SemaAnalyser::visitFunc(const LogosFunc* func) {
    for (const auto param : func->params) {
        if (!func) return;
        visitVarDec(param);
    }
    for (const auto stmt : func->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitStmt(const LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<const LogosVarDec*>(stmt)) {
        visitVarDec(varDec);
    }
    if (const auto ifStmt = dynamic_cast<const LogosIfStmt*>(stmt)) {
        visitIfStmt(ifStmt);
    }
    if (const auto ifStmt = dynamic_cast<const LogosConstructor*>(stmt)) {
        visitConstructor(ifStmt);
    }
    if (const auto funcCall = dynamic_cast<const LogosFuncCall*>(stmt)) {
        visitFuncCall(funcCall);
    }
}

void SemaAnalyser::visitStmtList(const vector<LogosStmt*>& stmts) {
    if (stmts.empty()) return;
}

void SemaAnalyser::visitVarDec(const LogosVarDec* varDec) {
    if (!varDec) return;
}

void SemaAnalyser::visitIfStmt(const LogosIfStmt* ifStmt) {
    if (!ifStmt) return;
}

void SemaAnalyser::visitExpr(const LogosExpr* expr) {
    if (!expr) return;
}

void SemaAnalyser::visitUnaryExpr(const LogosUnaryExpr* unaryExpr) {
    if (!unaryExpr) return;
}

void SemaAnalyser::visitConstructor(const LogosConstructor* constructorExpr) {
    if (!constructorExpr) return;
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

void SemaAnalyser::printError(const int errCode, Position position) {
    cout <<  std::format("Error at {} {}", position.lineNumber, position.posInLine);
    cout << LOGOS_ERRORS.at(errCode) << endl;
}

void SemaAnalyser::printError(const int errCode) {
    cout << LOGOS_ERRORS.at(errCode) << endl;
}
