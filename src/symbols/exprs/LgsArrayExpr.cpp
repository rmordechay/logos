#include "exprs/LgsArrayExpr.h"

#include "types/iterables/LgsSet.h"

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsArrayExpr::completeType(LgsType* toType) {
    if (type && type->asDArray() && toType->asSArray()) {
        freeType(type);
        type = toType;
    }
    if (toType->asSArray() || toType->asDArray() || toType->asSet()) {
        const auto otherBaseType = toType->asIterable()->baseType;
        for (size_t i = 0; i < elements.size(); ++i) {
            const auto element = elements[i];
            if (!element->type) {
                element->type = otherBaseType;
            } else {
                if (element->type->equals(otherBaseType)) continue;
                if (element->type->canCastTo(otherBaseType)) {
                    const auto castTo = element->castTo(otherBaseType);
                    if (element != castTo) freeExpr(element);
                    elements[i] = castTo;
                }
            }
        }
        type->asIterable()->baseType = otherBaseType;
    }
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
