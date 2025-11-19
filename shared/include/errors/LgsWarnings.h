#pragma once

struct LgsWarning {
    std::string msg;
    size_t errCode;
    LgsLocation location;

    LgsWarning(const std::string& msg, size_t errCode) : msg(msg), errCode(errCode) {}
    LgsWarning(const std::string& msg, size_t errCode, const LgsLocation& location) : msg(msg), errCode(errCode), location(location) {}
};

/** Templates warnings. Should not be returned directly, but formatted and returned as a new LgsWarning */
static inline size_t warningCodeStart = 50000;
inline LgsBaseMsg W10000{"Variable '%s' is not used.", warningCodeStart};
inline LgsBaseMsg W10001{"Setting owner for type '%s' has no meaning.", warningCodeStart};

