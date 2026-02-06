#include "exprs/LgsArrayExpr.h"
#include "types/iterables/LgsSet.h"
#include "LgsUtils.h"
#include "codegen/LgsCodeGen.h"
#include "types/LgsNullable.h"

Value* LgsArrayExpr::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

void LgsArrayExpr::castImplicitly(LgsType* toType) {
    if ((type && type->asIterable()->baseType) || !toType->asIterable()) return;
    setType(toType);
}

void LgsArrayExpr::setDebugValue(LgsCodeGen& cg) {
    if (!IRValue) return;
    const auto di = cg.debugger.diBuilder;
    const auto file = cg.debugger.diFile;

    DIType* dbType = nullptr;
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

LgsExpr* LgsArrayExpr::clone() {
    const auto newArr = new LgsArrayExpr(*this);
    newArr->elements.clear();
    for (const auto element : elements) {
        newArr->elements.push_back(element->clone());
    }
    return newArr;
}

LgsArrayExpr::~LgsArrayExpr() {
    for (const auto& initialElement : elements) {
        freeExpr(initialElement);
    }
    elements.clear();
}
