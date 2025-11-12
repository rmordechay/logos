#pragma once
#include "LgsErrors.h"

inline size_t lpmErrCodeStart = 50000;
inline LgsBaseMsg E60000{"Logos import path must be in the form of: 'url:version'. Given: %s", lpmErrCodeStart++};
inline LgsBaseMsg E60001{"Package URL contain insecure protocol. Given: %s", lpmErrCodeStart++};