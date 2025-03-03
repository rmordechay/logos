#include "SemaAnalyser.h"
#include "LogosErrors.h"
#include "exprs/LogosBinaryExpr.h"

#include <LogosUtils.h>
#include <ThreadPool.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosConstant.h>
#include <exprs/LogosFuncCall.h>
#include <exprs/LogosInstance.h>
#include <exprs/LogosSelection.h>
#include <exprs/LogosVariable.h>
#include <format>
#include <funcs/LogosPrint.h>
#include <loops/LogosLoop.h>
#include <stmts/LogosFieldDef.h>
#include <stmts/LogosIf.h>
#include <ranges>

void SemaAnalyser::analyse(const map<string, LogosFile*>& files, const map<string, LogosSymbol>& globalSymbols) {
    ThreadPool threadPool;
    for (const auto& file : files | views::values) {
        threadPool.runTask([file, &globalSymbols] {
            SemaAnalyser semaAnalyser;
            semaAnalyser.logosStack.globalSymbols = globalSymbols;
            semaAnalyser.visitLogosFile(file);
        });
    }
    threadPool.wait();
}

void SemaAnalyser::visitLogosFile(LogosFile* file) {
    if (const auto mainFile = dynamic_cast<LogosMainFile*>(file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LogosObjectFile*>(file)) {
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

void SemaAnalyser::visitMainFunc(const LogosFuncImpl* mainFunc, const std::string& path) {
    if (checkErr100(mainFunc)) return;
    visitUserFunc(mainFunc);
}

void SemaAnalyser::visitUserFunc(const LogosFuncImpl* func) {
    logosStack.enterScope();
    for (const auto& param : func->params) {
        visitVarDec(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}


void SemaAnalyser::visitStmt(LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<LogosVarDec*>(stmt)) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = dynamic_cast<LogosIf*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto loopStmt = dynamic_cast<LogosLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LogosFieldDef*>(stmt)) {
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
    logosStack.addLocalSymbol(varDec->name, LogosSymbol::createSymbol(varDec->expr));
}

void SemaAnalyser::visitIfStmt(const LogosIf* ifStmt) {
}

void SemaAnalyser::visitLoopStmt(const LogosLoop* loopStmt) {}

void SemaAnalyser::visitExpr(LogosExpr* expr) {
    if (!expr) return;
    if (const auto unaryExpr = dynamic_cast<LogosUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LogosBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else if (const auto array = dynamic_cast<LogosArray*>(expr)) {
        visitArray(array);
    }
}

void SemaAnalyser::visitArray(const LogosArray* array) {
    for (const auto& element : array->elements) {
        visitExpr(element);
    }
    array->type = inferArrayType(array);
}

void SemaAnalyser::visitUnaryExpr(LogosUnaryExpr* unaryExpr) {
    if (!unaryExpr) return;
    if (const auto instance = dynamic_cast<LogosInstance*>(unaryExpr)) {
        visitInstance(instance);
    } else if (const auto funcCall = dynamic_cast<LogosFuncCall*>(unaryExpr)) {
        visitFuncCall(funcCall);
    } else if (const auto selection = dynamic_cast<LogosSelection*>(unaryExpr)) {
        visitSelection(selection);
    } else if (const auto constant = dynamic_cast<LogosConstant*>(unaryExpr)) {
        visitConstant(constant);
    } else if (const auto arrIndex = dynamic_cast<LogosArrayIndex*>(unaryExpr)) {
        visitArrayIndex(arrIndex);
    } else if (const auto var = dynamic_cast<LogosVariable*>(unaryExpr)) {
        visitVariable(var);
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
    const auto symbol = logosStack.getSymbol(instance->name);
    const auto obj = symbol->object;
    instance->type = obj;
    instance->obj = obj;
}

void SemaAnalyser::visitArrayIndex(const LogosArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    arrayIndex->type = arrayIndex->baseExpr->type;
}

void SemaAnalyser::visitFuncCall(const LogosFuncCall* funcCallExpr) {

}

void SemaAnalyser::visitVariable(const LogosVariable* variable) {
    const auto symbol = logosStack.getSymbol(variable->name);
    switch (symbol->type) {
    case FIELD:
        break;
    case BINARY_EXPR:
        break;
    case INSTANCE:
        break;
    case FUNC_CALL:
        break;
    case CONSTANT:
        break;
    case OBJECT:
        break;
    case FUNC_IMPL:
        break;
    case METHOD_IMPL:
        break;
    case SELECTION:
        break;
    case ARRAY:
        variable->type = symbol->array->type;
        break;
    case ARRAY_INDEX:
        variable->type = symbol->arrayIndex->type;
        break;
    default:
        return;
    }
}

void SemaAnalyser::visitConstant(const LogosConstant* constant) {

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
    if (nextExpr) {
        // If true, nextExpr is the last element
        selection->type = nextExpr->type;
    }
    return nullptr;
}

LogosType* SemaAnalyser::inferArrayType(const LogosArray* array) {
    // TODO add proper check for array type
    return array->elements[0]->type;
}

void SemaAnalyser::resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
    const auto symbol = logosStack.getSymbol(previousExpr->getName());
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
    case BINARY_EXPR:
        break;
    case OBJECT:
        break;
    case BUILTIN_FUNC:
        break;
    case FUNC_IMPL:
        break;
    case METHOD_IMPL:
        break;
    case SELECTION:
        break;
    case ARRAY:
        break;
    case ARRAY_INDEX:
        break;
    }
}

template <typename... Args>
void SemaAnalyser::printError(const int errCode, Position* position, Args&&... args) {
    setUnsuccessful();
    const auto msgPair = LOGOS_ERRORS.find(errCode);
    // const auto formattedMessage = std::vformat(msgPair->second, std::make_format_args(args...));
    if (position) {
        cout << std::format("Error at {} {} {}: \n", *position->filePath, position->lineNumber, position->posInLine);
    } else {
        // cout << formattedMessage << endl;
    }
}

bool SemaAnalyser::checkErr100(const LogosFuncImpl* mainFunc) {
    if (!mainFunc) {
        printError(100, nullptr);
        return true;
    }
    return false;
}

