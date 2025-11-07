#pragma once
#include "LgsErrors.h"

inline size_t lpmErrCodeStart = 50000;
inline LgsBaseError E60000{"Logos import path must be in the form of: 'url:version'. Given: %s", lpmErrCodeStart++};
inline LgsBaseError E60001{"Package URL contain insecure protocol. Given: %s", lpmErrCodeStart++};