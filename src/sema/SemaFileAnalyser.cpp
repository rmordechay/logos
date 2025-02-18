#include "SemaFileAnalyser.h"

#include <LogosErrors.h>
#include <LogosUtils.h>
#include <exprs/LogosArray.h>
#include <exprs/LogosArrayIndex.h>
#include <exprs/LogosBinaryExpr.h>
#include <exprs/LogosConstant.h>
#include <exprs/LogosFuncCall.h>
#include <exprs/LogosInstance.h>
#include <exprs/LogosSelection.h>
#include <exprs/LogosVariable.h>

void SemaFileAnalyser::visitMainFile(const LogosMainFile* mainFile) {
    visitMainFunc(mainFile->mainFunc, mainFile->path);
    for (const auto& func : mainFile->funcs) {
        visitUserFunc(func);
    }
}

void SemaFileAnalyser::visitObjectFile(const LogosObjectFile* objectFile) {
    if (!objectFile) return;
    visitObject(objectFile->obj);
}

void SemaFileAnalyser::visitObject(const LogosObject* object) {
    if (!object) return;
    for (const auto& entry : object->fields) {
        visitField(entry.second);
    }
}

void SemaFileAnalyser::visitMainFunc(const LogosUserFunc* mainFunc, const std::string& path) {
    if (checkErr100(mainFunc)) return;
    visitUserFunc(mainFunc);
}

void SemaFileAnalyser::visitUserFunc(const LogosUserFunc* func) {
    logosStack.enterScope();
    for (const auto& param : func->params) {
        visitVarDec(param);
    }
    visitStmtBlock(func->stmtBlock);
    logosStack.exitScope();
}


void SemaFileAnalyser::visitStmt(LogosStmt* stmt) {
    if (!stmt) return;
    if (const auto varDec = dynamic_cast<LogosVarDec*>(stmt)) {
        visitVarDec(varDec);
    } else if (const auto ifStmt = dynamic_cast<LogosIf*>(stmt)) {
        visitIfStmt(ifStmt);
    } else if (const auto loopStmt = dynamic_cast<LogosLoop*>(stmt)) {
        visitLoopStmt(loopStmt);
    } else if (const auto fieldDef = dynamic_cast<LogosFieldDefinition*>(stmt)) {
        visitFieldDef(fieldDef);
    }
}

void SemaFileAnalyser::visitStmtBlock(LogosStmtBlock* stmtBlock) {
    for (const auto& stmt : stmtBlock->stmts) {
        visitStmt(stmt);
    }
}

void SemaFileAnalyser::visitField(LogosField* field) {

}

void SemaFileAnalyser::visitFieldDef(const LogosFieldDefinition* fieldDef) {
}


void SemaFileAnalyser::visitVarDec(LogosVarDec* varDec) {
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

void SemaFileAnalyser::visitIfStmt(const LogosIf* ifStmt) {
}

void SemaFileAnalyser::visitLoopStmt(const LogosLoop* loopStmt) {
    visitExpr(loopStmt->iterable);
    loopStmt->loopVar->type = loopStmt->iterable->type;
}

void SemaFileAnalyser::visitExpr(LogosExpr* expr) {
    if (!expr) return;
    if (const auto unaryExpr = dynamic_cast<LogosUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LogosBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else if (const auto array = dynamic_cast<LogosArray*>(expr)) {
        visitArray(array);
    }
}

void SemaFileAnalyser::visitArray(const LogosArray* array) {
    for (const auto& element : array->elements) {
        visitExpr(element);
    }
    // TODO add proper check for array type
    array->type = array->elements[0]->type;
}

void SemaFileAnalyser::visitUnaryExpr(LogosUnaryExpr* unaryExpr) {
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

void SemaFileAnalyser::visitBinaryExpr(const LogosBinaryExpr* binaryExpr) {
}

void SemaFileAnalyser::visitSelection(const LogosSelection* selection) {
    if (!selection) return;
    selection->type = inferSelectionType(selection);
}

void SemaFileAnalyser::visitInstance(LogosInstance* instance) {
    if (!instance) return;
    const auto symbol = logosStack.getSymbol(instance->name);
    const auto obj = symbol->object;
    instance->type = obj;
    instance->obj = obj;
}

void SemaFileAnalyser::visitArrayIndex(const LogosArrayIndex* arrayIndex) {
    visitExpr(arrayIndex->baseExpr);
    arrayIndex->type = arrayIndex->baseExpr->type;
}

void SemaFileAnalyser::visitFuncCall(const LogosFuncCall* funcCallExpr) {

}

void SemaFileAnalyser::visitVariable(const LogosVariable* variable) {
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
    case FUNC:
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

void SemaFileAnalyser::visitConstant(const LogosConstant* constant) {

}

void SemaFileAnalyser::setUnsuccessful() {
    unique_lock lock(mtx);
    successful = false;
}

LogosType* SemaFileAnalyser::inferSelectionType(const LogosSelection* selection) {
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

void SemaFileAnalyser::resolveSelection(LogosUnaryExpr* previousExpr, LogosUnaryExpr* nextExpr) {
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
    case FUNC:
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
void SemaFileAnalyser::printError(const int errCode, Position* position, Args&&... args) {
    setUnsuccessful();
    const auto msgPair = LOGOS_ERRORS.find(errCode);
    // const auto formattedMessage = std::vformat(msgPair->second, std::make_format_args(args...));
    if (position) {
        cout << std::format("Error at {} {} {}: \n", *position->filePath, position->lineNumber, position->posInLine);
    } else {
        // cout << formattedMessage << endl;
    }
}

bool SemaFileAnalyser::checkErr100(const LogosUserFunc* mainFunc) {
    if (!mainFunc) {
        printError(100, nullptr);
        return true;
    }
    return false;
}

SemaFileAnalyser::~SemaFileAnalyser() {
    delete mainFile;
}