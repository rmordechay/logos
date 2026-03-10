#include "exprs/LgsVariable.h"

#include <codegen/LgsCodeGen.h>
#include <assert.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/IRBuilder.h>

#include "funcs/LgsParam.h"
#include "stmts/LgsVarDec.h"
#include "LgsTokens.h"
#include "LgsType.h"

LgsExpr* LgsVariable::cast(LgsType* toType, bool explicitly) {
    if (toType && type && type->canCastTo(toType)) {
        setType(toType);
    }
    return this;
}

std::string LgsVariable::asText() {
    return name;
}

void LgsVariable::setDebugValue(LgsCodeGen& cg) {
    setDebugLoc(cg);
    const auto var = cg.debugger.diBuilder->createAutoVariable(
        cg.debugger.subprogram->getScope(),
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

LgsVariable* LgsVariable::clone() const {
    const auto newVar = new LgsVariable(*this);
    newVar->setType(type);
    return newVar;
}
