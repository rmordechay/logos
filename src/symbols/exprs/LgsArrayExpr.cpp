#include "exprs/LgsArrayExpr.h"

#include "types/iterables/LgsSet.h"

Value* LgsArrayExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsArrayExpr::completeType(LgsType* toType) {
    if (!type && (toType->asSArray() || toType->asDArray() || toType->asSet())) {
        type = toType;
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
