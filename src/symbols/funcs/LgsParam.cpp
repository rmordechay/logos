#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"

json LgsParam::asJson() {
    json tree;
    tree["name"] = name;
    tree["type"] = type->getName();
    if (expr) {
        tree["expr"] = expr->asJson();
    }
    return tree;
}
