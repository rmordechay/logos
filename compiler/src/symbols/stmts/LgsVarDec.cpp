#include "stmts/LgsVarDec.h"
#include "codegen/LgsCodeGen.h"
#include <llvm/IR/DIBuilder.h>
#include "LgsUtils.h"
#include "LgsTokens.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"

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

LgsStmt* LgsVarDec::clone() const {
    const auto newLgsVarDec = new LgsVarDec(*this);
    if (expr) newLgsVarDec->expr = expr->clone();
    if (type) newLgsVarDec->type = type->clone();
    return newLgsVarDec;
}