#ifndef LGSFUNCSIGNATURE_H
#define LGSFUNCSIGNATURE_H
#include "types/LgsType.h"

#include <sstream>

struct LgsFuncSignature {
    string name;
    string parentName;
    string composedName;
    LgsType* type;
    vector<string> argTypeNames;

    void setComposedName() {
        stringstream ss;
        if (parentName != "") {
            ss << parentName << "_";
        }
        ss << name;
        for (int i = 0; i < argTypeNames.size(); ++i) {
            ss << "_" + argTypeNames[i];
        }
        composedName = ss.str();
    }
    ~LgsFuncSignature() {
        delete type;
    }
};

#endif //LGSFUNCSIGNATURE_H
