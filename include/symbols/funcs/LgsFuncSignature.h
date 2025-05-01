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
    string path;
    LgsType* type;
    vector<LgsParam> params;
    bool isCallback = false;
    bool hasDefaultParams = false;

    LgsFuncSignature(const string& name, LgsType* type) : name(name), type(type) {}
    LgsFuncSignature(const string& name, LgsType* type, const vector<LgsParam>& params) : name(name), type(type), params(params) {}

    string getAsStr(const bool withType = false) const {
        stringstream strStream;
        strStream << name << '(';
        for (size_t i = 0; i < params.size(); ++i) {
            strStream << params[i].type->getName();
            if (i != params.size() - 1) strStream << ", ";
        }
        if (withType) {
            strStream << "): " << type->getName();
        } else {
            strStream << ")";
        }
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
