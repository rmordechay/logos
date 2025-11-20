#include "exprs/LgsArrayExpr.h"
#include "types/iterables/LgsSet.h"
#include "LgsUtils.h"

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsArrayExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    if (const auto sArr = type->asSArray()) {
        if (toType->asStr() && sArr->baseType->asChar()) {
            return IRValue;
        }
    }
    return IRValue;
}

void LgsArrayExpr::castImplicitly(LgsType* toType) {
    if (!type) return;
    if (type->asDArray() && (toType->asSArray() || toType->asSet())) {
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
        const auto element = elements[i];
        if (element->type) continue;
        element->setType(otherBaseType);
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
