#include "types/LgsFuncType.h"

#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"

Type* LgsFuncType::getIRType() {
    return ptrTy;
}

LgsExpr* LgsFuncType::getZeroValue() {
    assert(false);
}

const string LgsFuncType::getPrettyName() const {
    return name;
}

bool LgsFuncType::equals(LgsType* other) const {
    const auto otherFuncType = dynamic_cast<LgsFuncType*>(other);
    if (!otherFuncType) return false;
    if (name != otherFuncType->name) return false;
    const auto otherParams = otherFuncType->params;
    if (params.size() == 0 && otherParams.size() == 0) return true;
    for (size_t i = 0; i < params.size(); ++i) {
        auto thisTypeName = params[i]->type->getPrettyName();
        auto otherTypeName = otherFuncType->params[i]-> type->getPrettyName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

bool LgsFuncType::equals(const LgsFuncCall* other) const {
    if (name != other->name) return false;
    const auto args = other->args;
    if (params.size() == 0 && args.size() == 0) return true;
    if (params.size() < args.size()) return false;
    for (size_t i = 0; i < params.size(); ++i) {
        assert(args[i]);
        auto thisTypeName = params[i]->type->getPrettyName();
        auto otherTypeName = args[i]->type->getPrettyName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

LgsType* LgsFuncType::inferBinaryType(LgsType* other) {
    assert(false);
}

string LgsFuncType::getAsStr(const bool withType) const {
    stringstream strStream;
    strStream << name << '(';
    for (size_t i = 0; i < params.size(); ++i) {
        strStream << params[i]->type->getPrettyName();
        if (i != params.size() - 1) strStream << ", ";
    }
    if (withType) {
        strStream << "): " << rt->getPrettyName();
    } else {
        strStream << ")";
    }
    return strStream.str();
}

string LgsFuncType::getIRName() {
    if (IRName != "") return IRName;
    vector<string> argTypeNames;
    for (const auto& param : params) {
        argTypeNames.emplace_back(param->type->getPrettyName());
    }
    IRName = getComposedName(name, "", argTypeNames);
    return IRName;
}

LgsFuncType::~LgsFuncType() {
    for (const auto param : params) {
        delete param;
    }
}

