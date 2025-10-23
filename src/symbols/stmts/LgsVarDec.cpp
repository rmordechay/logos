#include "stmts/LgsVarDec.h"
#include "codegen/LgsLLVMGen.h"
#include "types/LgsPtr.h"
#include "types/iterables/LgsStr.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/DIBuilder.h>

std::string LgsVarDec::asText() {
    return name;
}

Value* LgsVarDec::loadIR(LgsLLVMGen& cg) {
    if (!IRValue->getType()->isPointerTy()) return IRValue;
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

bool LgsVarDec::shouldAllocate() const {
    if (type->isHeapAlloc || type->asFuncType()) return false;
    if (type->asStr() && type->asStr()->isStatic) return false;
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

LgsVarDec::~LgsVarDec() {
    if (expr) {
        if (type == expr->type) {
            expr->type = nullptr;
        }
        freeExpr(expr);
        expr = nullptr;
    }
    freeType(type);
    type = nullptr;
}
