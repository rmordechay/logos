#include "exprs/LgsBinaryExpr.h"
#include "utils/LgsUtils.h"

Value* LgsBinaryExpr::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

void LgsBinaryExpr::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "BinaryExpr");
    closeJsonObject(json);
}

std::string LgsBinaryExpr::asText() {
    return left->asText() + ' ' + op.name + ' ' + right->asText();
}

LgsBinaryExpr::~LgsBinaryExpr() {
    if (left) {
        freeExpr(left);
        right = nullptr;
    }
    if (right) {
        freeExpr(right);
        left = nullptr;
    }
}
