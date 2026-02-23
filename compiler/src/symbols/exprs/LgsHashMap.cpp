#include "exprs/LgsHashMap.h"

#include <assert.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/IRBuilder.h>

#include "codegen/LgsCodeGen.h"
#include "LgsTokens.h"
#include "LgsType.h"
#include "exprs/LgsExpr.h"

void LgsPair::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsPair::asText() {
    assert(0);
}

void LgsHashMap::setDebugValue(LgsCodeGen& cg) {
    if (!IRValue) return;
    const auto di = cg.debugger.diBuilder;
    const auto file = cg.debugger.diFile;
    const auto map = type->asMap();
    assert(map);
    const auto dbType = map->getDebugType(cg);
    const auto var = di->createAutoVariable(cg.debugger.subprogram, "", file, location.lineStart, dbType);
    di->insertDeclare(IRValue, var, di->createExpression(), cg.getDebugLoc(location), cg.builder.GetInsertBlock());
}

bool LgsHashMap::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsHashMap::asText() {
    if (type) return type->pname();
    if (elements.empty()) return "[]";
    const auto p = elements.front()->asPair();
    return "{" + p->key->asText() + ": " + p->key->asText() + "...}";
}

LgsHashMap::~LgsHashMap() {
    for (const auto pair : elements) {
        freeExpr(pair->key);
        freeExpr(pair->value);
    }
    elements.clear();
}
