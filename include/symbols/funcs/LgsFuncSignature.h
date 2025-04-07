#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "LgsParam.h"
#include "types/LgsType.h"

#include <sstream>

class LgsParam;

struct LgsFuncSignature {
    string name;
    string composedName;
    string internalName;
    string parentName;
    LgsType* type;
    vector<LgsParam> params;
    bool isStatic = false;

    LgsFuncSignature(const string& name, const string& parentName, LgsType* type, const vector<LgsParam>& params)
        : name(name), parentName(parentName), type(type), params(params) {
        setIRName();
    }

    void setIRName() {
        vector<string> argTypeNames;
        for (const auto& param : params) {
            argTypeNames.emplace_back(param.type->getName());
        }
        composedName = getComposedName(name, parentName, argTypeNames);
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
