#pragma once
#include "Lgs_Types.h"
#include <string>

struct Lgs_Stack;

void freeRTType(void* ptr, Lgs_RTType type);
void funcCleanup(Lgs_Stack& stack);
std::string getTypeName(Lgs_RTType type);
