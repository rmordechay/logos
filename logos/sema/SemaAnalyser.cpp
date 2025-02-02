#include "SemaAnalyser.h"
#include "LogosErrors.h"

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
            theStack.globalSymbols[object->name()] = LogosSymbol(OBJECT, object);
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
    for (const auto field : object->fields) {
        visitVarDec(field);
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
    for (const auto param : func->params) {
        if (!func) return;
        visitVarDec(param);
    }
    for (const auto stmt : func->stmts) {
        visitStmt(stmt);
    }
}

void SemaAnalyser::visitStmt(LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<LogosVarDec*>(stmt)) {
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
}

void SemaAnalyser::visitVarDec(LogosVarDec* varDec) {
    const auto inferredType = varDec->expr->type;
    const auto userType = varDec->userType;
    if (userType && *userType != inferredType) {
        printError(101, &varDec->position, *userType, inferredType->name());
    } else {
        varDec->inferredType = inferredType;
    }
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

LogosType* SemaAnalyser::inferType(const LogosExpr* expr) {
    return expr->type;
}

void SemaAnalyser::setUnsuccessful() {
    unique_lock lock(mtx);
    successful = false;
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
