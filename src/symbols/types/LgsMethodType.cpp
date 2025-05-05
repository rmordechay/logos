#include "types/LgsMethodType.h"
#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"

string LgsMethodType::getIRName() {
    if (IRName != "") return IRName;
    vector<string> argTypeNames;
    for (const auto& param : params) {
        argTypeNames.emplace_back(param->type->getPrettyName());
    }
    IRName = getComposedName(name, parentName, argTypeNames);
    return IRName;
}

bool LgsMethodType::equals(LgsType* other) const {
    const auto otherFuncType = dynamic_cast<LgsFuncType*>(other);
    if (!otherFuncType) return false;
    if (name != otherFuncType->name) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < params.size() - 1; ++i) {
        auto thisTypeName = params[i + 1]->type->getPrettyName();
        auto otherTypeName = otherFuncType->params[i]->type->getPrettyName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

string LgsFuncType::getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames) {
    stringstream strStream;
    if (parentName != "") {
        strStream << parentName << "_";
    }
    strStream << name;
    for (int i = 0; i < argTypeNames.size(); ++i) {
        strStream << "_" + argTypeNames[i];
    }
    return strStream.str();
}

