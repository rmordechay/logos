#include "funcs/LgsParam.h"

#include "exprs/LgsExpr.h"
#include "types/LgsFuncType.h"

string LgsParam::format(string& indentStr) {
    return name + ": " + type->getPrettyName();
}

json LgsParam::asJSON() {
    json tree;
    tree["name"] = name;
    return tree;
}

string LgsParam::getIRName() {
    if (const auto funcType = dynamic_cast<LgsFuncType*>(type)) {
        return funcType->IRName;
    }
    return name;
}
