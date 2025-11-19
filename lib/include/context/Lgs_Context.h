#pragma once

#if defined(__x86_64__) || defined(_M_X64)
#include "Lgs_X86_64.h"
#elif defined(__aarch64__) || defined(_M_ARM64)
#include "Lgs_Aarch64.h"
#else
#error "Unsupported architecture"
#endif