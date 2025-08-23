#include "exprs/unary/LgsArrayExpr.h"
#include "cli/LgsCli.h"
#include <llvm/IR/Module.h>

std::string LgsArrayExpr::pname() {
    return type->pname();
}

json::value LgsArrayExpr::asJSON() {
    json::object jsonObj;
    jsonObj["exprKind"] = "arrayExpr";
    jsonObj["type"] = type->asJSON();
    return jsonObj;
}

LgsArrayExpr::~LgsArrayExpr() {
    for (const auto& initialElement : initialElements) {
        delete initialElement;
    }
    initialElements.clear();
}
