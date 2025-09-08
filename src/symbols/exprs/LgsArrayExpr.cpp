#include "exprs/LgsArrayExpr.h"

std::string LgsArrayExpr::pname() {
    return type->pname();
}

json::value LgsArrayExpr::asJSON() {
    json::object jsonObj;
    jsonObj["exprKind"] = "arrayExpr";
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}

void LgsArrayExpr::completeType(LgsType* toType) {
    const auto thisDArr = type->asDArray();
    if (thisDArr && toType->asDArray()) {
        freeExpr(thisDArr->sizeExpr);
        thisDArr->sizeExpr = toType->asDArray()->sizeExpr;
        return;
    }
    const auto thisSArr = type->asSArray();
    if (thisSArr && toType->asSArray()) {
        freeExpr(thisSArr->sizeExpr);
        thisSArr->sizeExpr = toType->asSArray()->sizeExpr;
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
