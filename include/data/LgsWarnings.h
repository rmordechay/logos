#pragma once

struct LgsWarning {
    std::string msg;
    size_t errCode;
    LgsLocation location;
};

/** Templates warnings. Should not be returned directly, but formatted and returned as a new LgsWarning */
inline size_t warningCodeStart = 50000;
inline LgsBaseError W50000{"Variable '%s' is not used.", warningCodeStart};
inline LgsBaseError W50001{"Setting owner for type '%s' has no meaning.", warningCodeStart};

