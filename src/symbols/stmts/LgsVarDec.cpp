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
    if (type->isNumber()) return false;
    return true;
}

void LgsVarDec::setDebugValue(LgsLLVMGen& cg) {
    const auto var = cg.diBuilder->createAutoVariable(
        cg.compileUnit,
        name,
        cg.diFile,
        location.lineStart,
        type->getDebugType(cg)
    );
    cg.diBuilder->insertDeclare(
        IRValue,
        var,
        cg.diBuilder->createExpression(),
        getDebugLoc(cg),
        cg.builder.GetInsertBlock()
    );
}

LgsVarDec::~LgsVarDec() {
    if (expr) {
        freeExpr(expr);
        expr = nullptr;
    } else if (type) {
        freeType(type);
        type = nullptr;
    }
}
