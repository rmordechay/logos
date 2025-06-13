#pragma once
#include "utils/LgsLogger.h"

inline LogLevel logLevel = DEBUG;
#define WRITE_IR_TO_FILE false
#define INITIAL_ARRAY_CAPACITY 2
#define PARAM_SWAP_SIZE_THRESHOLD 20
#define WORKERS_NUMBER thread::hardware_concurrency()
