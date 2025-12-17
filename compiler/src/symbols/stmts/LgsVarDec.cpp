#include "stmts/LgsVarDec.h"
#include "codegen/LgsCgModule.h"
#include "types/iterables/LgsStr.h"
#include "LgsUtils.h"
#include "types/LgsNullable.h"

#include <llvm/IR/DIBuilder.h>

void LgsVarDec::setType(LgsType* newType) {
    type = newType;
}

Value* LgsVarDec::loadIR(LgsCgModule& cg) {
    if (!IRValue->getType()->isPointerTy()) return IRValue;
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

bool LgsVarDec::shouldAllocate() const {
    if (!type) return false;
    if (type->asObject()) return false;
    if (type->asNullable() && !type->asNullable()->passByRef) return false;
    if (expr->asFuncCall() || expr->asBinExpr()) return false;
    if (type->asIterable() && type->asIterable()->isStatic) return false;
    if (type->asSubtype() || type->asFuncType()) return false;
    return true;
}

void LgsVarDec::setDebugValue(LgsCgModule& cg) {
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
    hashNodeInt(oldHash, isConst);
    hashNodeInt(oldHash, isOwner);
    hashNodeString(oldHash, name);
    if (type) type->hashNode(oldHash);
    if (expr) expr->hashNode(oldHash);
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