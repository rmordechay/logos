#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "LgsParam.h"
#include "types/LgsType.h"

#include <sstream>

class LgsParam;

struct LgsFuncSignature {
    string name;
    LgsType* rt;
    string rtName;
    string parentName;
    string composedName;
    vector<LgsParam*> params;

    void setNameFromArgs(const vector<string>& argTypeNames) {
        stringstream strStream;
        if (parentName != "") {
            strStream << parentName << "_";
        }
        strStream << name;
        for (int i = 0; i < argTypeNames.size(); ++i) {
            strStream << "_" + argTypeNames[i];
        }
        composedName = strStream.str();
    }

    void setNameFromParams() {
        vector<string> argTypeNames;
        for (const auto& param : params) {
            argTypeNames.emplace_back(param->type->getName());
        }
        setNameFromArgs(argTypeNames);
    }

    bool operator==(const LgsFuncSignature* other) const {
        return name == other->name;
    }
};

#endif //LGSFUNCSIGNATURE_H
