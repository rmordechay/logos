#pragma once

inline string WARNING_PLACEHOLDER = "%s";

struct LgsWarning {
    string msg;
    size_t warningCode;
};

/** Templates warnings. Should not be returned directly, but formatted and returned as a new LgsWarning */
inline size_t warningCodeStart = 10000;
inline LgsWarning W10000{.msg = "Variable '%s' is not used.", .warningCode = warningCodeStart};

