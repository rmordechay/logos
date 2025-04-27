#ifndef LGSWARNINGS_H
#define LGSWARNINGS_H
#include <string>

using namespace std;

inline string WARNING_PLACEHOLDER = "%s";

struct LgsWarning {
    string msg;
    int warningCode;
};

/** Templates warnings. Should not be returned directly, but formatted and returned as a new LgsWarning */
inline int warningCodeStart = 10000;
inline LgsWarning W10000{.msg = "Variable '%s' is not used.", .warningCode = warningCodeStart};
#endif //LGSWARNINGS_H
