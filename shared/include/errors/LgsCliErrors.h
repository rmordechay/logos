#pragma once
#include "errors/LgsErrors.h"

inline size_t cliErrCodeStart = 40000;
inline LgsBaseMsg E40000{"Unknown command.", cliErrCodeStart++};
inline LgsBaseMsg E40001{"Wrong number of arguments.", cliErrCodeStart++};
inline LgsBaseMsg E40002{"Missing argument for %s.", cliErrCodeStart++};
inline LgsBaseMsg E40003{"Invalid argument '%s'.", cliErrCodeStart++};
inline LgsBaseMsg E40004{"Path %s does not exist.", cliErrCodeStart++};
inline LgsBaseMsg E40005{"Logos project name must be lowercase, hyphen-seperated and start with a character. Given: %s.", cliErrCodeStart++};
inline LgsBaseMsg E40006{"Project with name '%s' already exists in the current directory.", cliErrCodeStart++};