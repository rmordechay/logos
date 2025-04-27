#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"
#include "funcs/LgsFuncImpl.h"
#include "funcs/LgsFuncSignature.h"

LgsParam::LgsParam(LgsFuncImpl* func)
    : name(func->signature.name), type(func->signature.type), func(func) {}

string LgsParam::format(string& indentStr) {
    return name + ": " + type->getName();
}

json LgsParam::asJSON() {
    json tree;
    tree["name"] = name;
    return tree;
}
