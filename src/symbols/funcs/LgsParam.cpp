#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->getName();
}
