#include "stmts/LgsVarDec.h"
#include "codegen/LgsLLVMGen.h"
#include "types/iterables/LgsStr.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/DIBuilder.h>

void LgsVarDec::setType(LgsType* newType) {
    type = newType;
}

std::string LgsVarDec::asText() {
    return name;
}

Value* LgsVarDec::loadIR(LgsLLVMGen& cg) {
    if (!IRValue->getType()->isPointerTy()) return IRValue;
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

bool LgsVarDec::shouldAllocate() const {
    if (type->isHeapAlloc || type->asFuncType()) return false;
    if (type->asIterable() && type->asIterable()->isStatic) return false;
    if (type->asSubtype()) return false;
    return true;
}

void LgsVarDec::setDebugValue(LgsLLVMGen& cg) {
    const auto var = cg.debugger.diBuilder->createAutoVariable(
        cg.debugger.diProgram,
        name,
        cg.debugger.diFile,
        location.lineStart,
        type->getDebugType(cg)
    );
    cg.debugger.diBuilder->insertDeclare(
        IRValue,
        var,
        cg.debugger.diBuilder->createExpression(),
        getDebugLoc(cg),
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

LgsVarDec* LgsVarDec::clone() {
    assert(0);
}
