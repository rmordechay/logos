#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->getName();
}

json LgsParam::asJSON() {
    json tree;
    tree["name"] = name;
    return tree;
}
