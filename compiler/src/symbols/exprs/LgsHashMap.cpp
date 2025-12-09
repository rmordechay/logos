#include "exprs/LgsHashMap.h"
#include "LgsUtils.h"
#include "codegen/LgsCgModule.h"

void LgsHashMap::castImplicitly(LgsType* toType) {
    if (!toType->asMap()) return;
    if (!type) {
        setType(toType);
    }
}

void LgsHashMap::setDebugValue(LgsCgModule& cg) {
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
    for (const auto [key, value] : elements) {
        freeExpr(key);
        freeExpr(value);
    }
    elements.clear();
}
