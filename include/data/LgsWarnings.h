#pragma once

struct LgsWarning {
    std::string msg;
    size_t errCode;
    LgsLocation location;
};

/** Templates warnings. Should not be returned directly, but formatted and returned as a new LgsWarning */
inline size_t warningCodeStart = 10000;
inline LgsBaseError W10000{.msg = "Variable '%s' is not used.", .code = warningCodeStart};
inline LgsBaseError W10001{.msg = "Setting owner for type '%s' has no meaning.", .code = warningCodeStart};

