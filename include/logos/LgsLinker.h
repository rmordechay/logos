#pragma once
#include "LgsModule.h"
#include "Platform.h"
#include <map>

bool link(const LgsPaths& paths, const map<string, LgsModule*>& modules);
