#pragma once
#include "LgsErrors.h"

inline size_t cliErrCodeStart = 40000;
inline LgsBaseError E40000{"Unknown command.", cliErrCodeStart++};
inline LgsBaseError E40001{"Wrong number of arguments.", cliErrCodeStart++};
inline LgsBaseError E40002{"Missing argument for %s.", cliErrCodeStart++};
inline LgsBaseError E40003{"Invalid argument %s.", cliErrCodeStart++};
inline LgsBaseError E40004{"Path %s does not exist.", cliErrCodeStart++};
inline LgsBaseError E40005{"Logos project name must be lowercase, hyphen-seperated and start with a character. Given: %s.", cliErrCodeStart++};
inline LgsBaseError E40006{"Project with name '%s' already exists in the current directory.", cliErrCodeStart++};
