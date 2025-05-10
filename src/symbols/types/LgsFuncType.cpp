#include "types/LgsFuncType.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

bool LgsFuncType::equals(LgsType* other) {
    const auto otherFuncType = other->asFuncType();
    if (!otherFuncType) return false;
    if (name != otherFuncType->name) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() != otherParams.size()) return false;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto thisType = params[i]->type;
        const auto otherType = otherFuncType->params[i]->type;
        if (thisType->equals(otherType)) return false;
    }
    return true;
}

bool LgsFuncType::equals(const LgsFuncCall* other) const {
    if (name != other->name) return false;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    if (params.size() < args.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        const auto thisType = params[i]->type;
        assert(thisType);
        const auto otherType = args[i]->type;
        if (!thisType->equals(otherType)) return false;
    }
    return true;
}

string LgsFuncType::getIRName() {
    if (IRName != "") return IRName;
    vector<string> paramTypeNames;
    for (const auto& param : params) {
        paramTypeNames.emplace_back(param->type->getIRName());
    }
    IRName = getComposedName(name, parentName, paramTypeNames);
    return IRName;
}

Type* LgsFuncType::getIRType() {
    return ptrTy;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(false);
}

string LgsFuncType::prettyName() const {
    return name;
}

LgsType* LgsFuncType::inferBinaryType(LgsType* other) {
    return nullptr;
}

string LgsFuncType::getAsStr(const bool withType) const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < params.size(); ++i) {
        strStream << params[i]->type->prettyName();
        if (i != params.size() - 1) strStream << ", ";
    }
    if (withType) {
        strStream << "): " << rt->prettyName();
    } else {
        strStream << ")";
    }
    return strStream.str();
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

LgsFuncType::~LgsFuncType() {
    for (const auto param : params) {
        delete param;
    }
}
