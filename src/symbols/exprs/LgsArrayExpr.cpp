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
        for (int i = 0; i < initialElements.size(); ++i) {
            const auto element = initialElements[i];
            if (!element->type) {
                element->type = otherBaseType;
            } else {
                if (element->type->equals(otherBaseType)) continue;
                if (element->type->canCastTo(otherBaseType)) {
                    const auto castTo = element->castTo(otherBaseType);
                    if (element != castTo) freeExpr(element);
                    initialElements[i] = castTo;
                }
            }
        }
        type->asIterable()->baseType = otherBaseType;
    }
}

std::string LgsArrayExpr::getName() {
    return type ? type->pname() : "[]";
}

json::value LgsArrayExpr::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprKind"] = "arrayExpr";
    jsonObj["type"] = type->asJsonStr();
    return jsonObj;
}

LgsArrayExpr::~LgsArrayExpr() {
    for (const auto& initialElement : initialElements) {
        freeExpr(initialElement);
    }
    initialElements.clear();
}
