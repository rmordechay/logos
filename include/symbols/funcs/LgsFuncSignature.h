#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "LgsParam.h"
#include "exprs/unary/LgsFuncCall.h"
#include "types/LgsType.h"
#include <sstream>

class LgsParam;

class LgsFuncSignature {
public:
    string name;
    string IRName;
    string parentName;
    LgsType* type;
    vector<LgsParam> params;
    bool isMethod = false;
    bool isStatic = false;
    bool isCallback = false;
    bool hasDefaultParams = false;

    LgsFuncSignature(const string& name, LgsType* type, const vector<LgsParam>& params): LgsFuncSignature(name, "", type, params) {}
    LgsFuncSignature(const string& name, const string& parentName, LgsType* type, const vector<LgsParam>& params) : name(name), parentName(parentName), type(type), params(params) {
        if (parentName != "") isMethod = true;
    }

    void setIRName() {
        vector<string> argTypeNames;
        for (const auto& param : params) {
            argTypeNames.emplace_back(param.type->getName());
        }
        IRName = getComposedName(name, parentName, argTypeNames);
    }

    bool isEqual(const LgsFuncCall* funcCall) const {
        if (!isEqual(funcCall->name, funcCall->parentName, funcCall->type)) return false;
        if (params.size() == 0) return true;
        for (size_t i = isMethod; i < params.size(); ++i) {
            auto thisTypeName = params[i].type->getName();
            auto otherTypeName = funcCall->args[i]->type->getName();
            if (thisTypeName != otherTypeName) return false;
        }
        return true;
    }

    bool isEqual(const LgsFuncSignature* other) const {
        if (!isEqual(other->name, other->parentName, other->type)) return false;
        if (params.size() == 0) return true;
        for (size_t i = 0; i < params.size() - 1; ++i) {
            auto thisTypeName = params[i + 1].type->getName();
            auto otherTypeName = other->params[i].type->getName();
            if (thisTypeName != otherTypeName) return false;
        }
        return true;
    }

    bool isEqual(const string& otherName, const string& otherParentName, const LgsType* otherType) const {
        if (isMethod && parentName != otherParentName) return false;
        if (name != otherName) return false;
        if (otherType && type->getName() != otherType->getName()) return false;
        return true;
    }

    string getPrintName() const {
        stringstream strStream;
        strStream << name << '(';
        for (size_t i = 0; i < params.size(); ++i) {
            strStream << params[i].type->getName();
            if (i != params.size() - 1) strStream << ", ";
        }
        strStream << "): " << type->getName();
        return strStream.str();
    }

    static string getComposedName(const string& name, const string& parentName, const vector<string>& argTypeNames) {
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
};

#endif //LGSFUNCSIGNATURE_H
