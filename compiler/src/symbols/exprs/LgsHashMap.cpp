#include "exprs/LgsHashMap.h"
#include "LgsUtils.h"
#include "codegen/LgsCodeGen.h"

void LgsPair::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsPair::asText() {
    assert(0);
}

void LgsHashMap::castImplicitly(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) setType(toType);
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
    return type->pname();
}

LgsHashMap::~LgsHashMap() {
    for (const auto pair : elements) {
        freeExpr(pair->key);
        freeExpr(pair->value);
    }
    elements.clear();
}
