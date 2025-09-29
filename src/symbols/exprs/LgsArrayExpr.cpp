#include "exprs/LgsArrayExpr.h"

#include "types/iterables/LgsSet.h"

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsArrayExpr::completeType(LgsType* toType) {
    const auto thisDArr = type->asDArray();
    const auto otherDArr = toType->asDArray();
    if (thisDArr && otherDArr) {
        if (!thisDArr->baseType) {
            thisDArr->baseType = otherDArr->baseType;
        }
        if (!thisDArr->size) {
            thisDArr->size = otherDArr->size;
        }
        return;
    }
    const auto thisSArr = type->asSArray();
    const auto otherSArr = toType->asSArray();
    if (thisSArr && otherSArr) {
        if (!thisSArr->baseType) {
            thisSArr->baseType = otherSArr->baseType;
        }
        if (!thisSArr->size) {
            thisSArr->size = otherSArr->size;
        }
        return;
    }
    const auto thisSet = type->asSet();
    const auto otherSet = toType->asSet();
    if (thisSet && otherSet) {
        if (!thisSet->baseType) {
            thisSet->baseType = otherSet->baseType;
        }
        if (!thisSet->size) {
            thisSet->size = otherSet->size;
        }
    }
}

std::string LgsArrayExpr::getName() {
    return type->pname();
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
