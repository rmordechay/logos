#include "exprs/LgsArrayExpr.h"

#include <assert.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/IRBuilder.h>

#include "types/iterables/LgsSet.h"
#include "codegen/LgsCodeGen.h"
#include "LgsTokens.h"
#include "LgsType.h"
#include "types/iterables/LgsIterable.h"

LgsExpr* LgsArrayExpr::cast(LgsType* toType, const bool explicitly) {
    if (const auto dArr = toType->asDArray()) {
        setType(new LgsDArray());
        auto current = iterable->asDArray();
        auto target = dArr;
        while (const auto innerDArr = target->baseType->asDArray()) {
            current->baseType = new LgsDArray();
            current = current->baseType->asDArray();
            target = innerDArr;
        }
    } else if (const auto sArr = toType->asSArray()) {
        setType(new LgsSArray(nullptr, sArr->lengthExpr));
        auto current = iterable->asSArray();
        auto target = sArr;
        while (const auto innerSArr = target->baseType->asSArray()) {
            current->baseType = new LgsSArray(nullptr, innerSArr->lengthExpr);
            current = current->baseType->asSArray();
            target = innerSArr;
        }
    }
    return this;
}

void LgsArrayExpr::setType(LgsType* newType) {
    iterable = newType->asIterable();
    type = iterable;
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
    if (type) return type->pname();
    if (elements.empty()) return "[]";
    return "[" + elements.front()->asText() + "...]";
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
