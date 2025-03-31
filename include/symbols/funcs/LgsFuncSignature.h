#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
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
    vector<string> paramTypeNames;

    void setComposedName() {
        stringstream ss;
        if (parentName != "") {
            ss << parentName << "_";
        }
        ss << name;
        for (int i = 0; i < paramTypeNames.size(); ++i) {
            ss << "_" + paramTypeNames[i];
        }
        composedName = ss.str();
    }
};

#endif //LGSFUNCSIGNATURE_H
