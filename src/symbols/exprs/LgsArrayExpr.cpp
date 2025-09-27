#include "exprs/LgsArrayExpr.h"

std::string LgsArrayExpr::pname() {
    return type->pname();
}

json::value LgsArrayExpr::asJsonStr() {
    json::object jsonObj;
    jsonObj["exprKind"] = "arrayExpr";
    jsonObj["type"] = type->asJsonStr();
    return jsonObj;
}

void LgsArrayExpr::completeType(LgsType* toType) {
    const auto thisDArr = type->asDArray();
    const auto otherDArr = toType->asDArray();
    if (thisDArr && otherDArr) {
        if (!thisDArr->baseType) {
            thisDArr->baseType = otherDArr->baseType;
        }
        if (!thisDArr->sizeExpr) {
            thisDArr->sizeExpr = otherDArr->sizeExpr;
        }
        return;
    }
    const auto thisSArr = type->asSArray();
    const auto otherSArr = toType->asSArray();
    if (thisSArr && otherSArr) {
        if (!thisSArr->baseType) {
            thisSArr->baseType = otherSArr->baseType;
        }
        if (!thisSArr->sizeExpr) {
            thisSArr->sizeExpr = otherSArr->sizeExpr;
        }
    }
}

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsArrayExpr::~LgsArrayExpr() {
    for (const auto& initialElement : initialElements) {
        delete initialElement;
    }
    initialElements.clear();
}
