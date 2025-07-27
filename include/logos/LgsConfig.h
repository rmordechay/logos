#pragma once
#include "utils/LgsUtils.h"

inline LogLevel logLevel = DEBUG;
#define WRITE_IR_TO_FILE true
#define INITIAL_ARRAY_CAPACITY 2
#define BIG_SIZE_THRESHOLD 20
#define WORKERS_NUMBER thread::hardware_concurrency()
