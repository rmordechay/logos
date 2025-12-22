#include "exprs/LgsArrayExpr.h"
#include "types/iterables/LgsSet.h"
#include "LgsUtils.h"
#include "codegen/LgsCgModule.h"

Value* LgsArrayExpr::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsArrayExpr::castImplicitly(LgsType* toType) {
    if (!toType->asIterable()) return;
    // Replace dynamic array with static if needed
    if (!type && toType->asSArray()) {
        setType(toType);
    } else if (type->asDArray() && (toType->asSArray() || toType->asSet())) {
        freeType(type);
        setType(toType);
    }

    LgsType* otherBaseType = nullptr;
    if (toType->asSet()) {
        otherBaseType = toType->genericArgs.front();
    } else {
        otherBaseType = toType->asIterable()->baseType;
    }
    for (size_t i = 0; i < elements.size(); ++i) {
        castExprImplicitly(elements[i], otherBaseType);
    }
    if (!type) {
        setType(toType);
    } else if (const auto& iter = type->asIterable()) {
        iter->baseType = otherBaseType;
    }
}

void LgsArrayExpr::setDebugValue(LgsCgModule& cg) {
    if (!IRValue) return;
    const auto di = cg.debugger.diBuilder;
    const auto file = cg.debugger.diFile;

    llvm::DIType* dbType = nullptr;
    if (const auto sarr = type->asSArray()) {
        dbType = sarr->getDebugType(cg);
    } else if (const auto darr = type->asDArray()) {
        dbType = darr->getDebugType(cg);
    } else if (const auto sett = type->asSet()) {
        dbType = sett->getDebugType(cg);
    } else {
        assert(0);
    }
    const auto var = di->createAutoVariable(cg.debugger.subprogram, "", file, location.lineStart, dbType);
    di->insertDeclare(IRValue, var, di->createExpression(), cg.getDebugLoc(location), cg.builder.GetInsertBlock());
}

std::string LgsArrayExpr::asText() {
    return type ? type->pname() : "[]";
}

LgsArrayExpr::~LgsArrayExpr() {
    for (const auto& initialElement : elements) {
        freeExpr(initialElement);
    }
    elements.clear();
}
