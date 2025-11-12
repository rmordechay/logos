#include "exprs/LgsArrayExpr.h"
#include "types/iterables/LgsSet.h"
#include "utils/LgsUtils.h"

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsArrayExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    if (toType->asStr()) {
        if (const auto sArr = type->asSArray()) {
            if (sArr->baseType->asChar()) return IRValue;
        }
    }
    assert(0);
}

void LgsArrayExpr::completeType(LgsType* toType) {
    if (type && type->asDArray() && toType->asSArray()) {
        freeType(type);
        setType(toType);
    }
    if (!toType->asSArray() && !toType->asDArray() && !toType->asSet()) return;
    const auto otherBaseType = toType->asIterable()->baseType;
    for (size_t i = 0; i < elements.size(); ++i) {
        const auto element = elements[i];
        if (!element->type) {
            element->setType(otherBaseType);
            continue;
        }
        if (element->type->equals(otherBaseType)) continue;
        if (!element->type->canCastTo(otherBaseType)) continue;
        const auto castTo = element->staticCast(otherBaseType);
        if (element != castTo) {
            freeExpr(element);
        }
        elements[i] = castTo;
    }
    type->asIterable()->baseType = otherBaseType;
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
