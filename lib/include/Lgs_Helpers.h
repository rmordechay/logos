#pragma once
#include "Lgs_Types.h"
#include <sstream>

std::string formatElement(const Lgs_TypeInfo* rtt, void* elem);
void freeValue(void* ptr, const Lgs_TypeInfo* type);
