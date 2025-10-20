#pragma once
#include "LgsErrors.h"

inline size_t cliErrCodeStart = 40000;
inline LgsBaseError E40000{.msg = "Unknown command.", .code = cliErrCodeStart++};
inline LgsBaseError E40001{.msg = "Wrong number of arguments.", .code = cliErrCodeStart++};
inline LgsBaseError E40002{.msg = "Missing argument for %s.", .code = cliErrCodeStart++};
inline LgsBaseError E40003{.msg = "Invalid optimization level %s.", .code = cliErrCodeStart++};
inline LgsBaseError E40004{.msg = "Path %s not found.", .code = cliErrCodeStart++};
inline LgsBaseError E40005{.msg = "%s is not a Logos file.", .code = cliErrCodeStart++};