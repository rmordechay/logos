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

    void setNameFromArgs(const vector<string>& paramTypeNames) {
        stringstream strStream;
        if (parentName != "") {
            strStream << parentName << "_";
        }
        strStream << name;
        for (int i = 0; i < paramTypeNames.size(); ++i) {
            strStream << "_" + paramTypeNames[i];
        }
        composedName = strStream.str();
    }

    void setNameFromParams() {
        stringstream strStream;
        if (parentName != "") {
            strStream << parentName << "_";
        }
        strStream << name;
        for (int i = 0; i < params.size(); ++i) {
            strStream << "_" + params[i]->type->getName();
        }
        composedName = strStream.str();
    }

    bool operator==(const LgsFuncSignature* other) const {
        return name == other->name;
    }
};

#endif //LGSFUNCSIGNATURE_H
