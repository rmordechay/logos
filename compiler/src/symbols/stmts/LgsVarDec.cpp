#include "stmts/LgsVarDec.h"
#include "codegen/LgsCodeGen.h"
#include "types/iterables/LgsStr.h"
#include "LgsUtils.h"
#include "types/LgsNullable.h"

#include <llvm/IR/DIBuilder.h>

LgsType* LgsVarDec::getType() {
    return type;
}

void LgsVarDec::setType(LgsType* newType) {
    type = newType;
}

void LgsVarDec::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
    const auto var = cg.debugger.diBuilder->createAutoVariable(
        cg.debugger.subprogram,
        name,
        cg.debugger.diFile,
        location.lineStart,
        type->getDebugType(cg)
    );
    cg.debugger.diBuilder->insertDeclare(
        IRValue,
        var,
        cg.debugger.diBuilder->createExpression(),
        cg.getDebugLoc(location),
        cg.builder.GetInsertBlock()
    );
}

void LgsVarDec::hashNode(size_t& oldHash) {
    hashNodeInt(oldHash, isNullable);
    hashNodeInt(oldHash, isMutable);
    hashNodeString(oldHash, name);
    if (type) type->hashNode(oldHash);
    if (expr) expr->hashNode(oldHash);
}

LgsStmt* LgsVarDec::clone() {
    const auto newLgsVarDec = new LgsVarDec(*this);
    if (expr) newLgsVarDec->expr = expr->clone();
    return newLgsVarDec;
}

LgsVarDec::~LgsVarDec() {
    if (expr) {
        if (type && expr->type && type == expr->type) {
            freeExpr(expr);
        } else {
            freeType(type);
            freeExpr(expr);
        }
    } else {
        freeType(type);
    }
    setType(nullptr);
    expr = nullptr;
}
