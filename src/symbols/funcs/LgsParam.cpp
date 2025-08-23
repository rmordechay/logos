#include "funcs/LgsParam.h"
#include "funcs/LgsFunc.h"
#include "utils/LgsUtils.h"

json::value LgsParam::asJSON() {
    json::object obj;
    obj["name"] = name;
    return obj;
}

LgsParam LgsParam::clone() const {
    LgsParam newParam(type->clone(), name);
    newParam.expr = expr ? expr->clone() : nullptr;
    newParam.isVariadic = isVariadic;
    newParam.isSelf = isSelf;
    return newParam;
}
