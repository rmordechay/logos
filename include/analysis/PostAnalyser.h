#pragma once
#include "files/LgsFile.h"
#include <vector>

class PostAnalyser {
public:
    static void analyse(const vector<LgsFile*>& files, LgsSymbolTable& globals);
    static void swapReturn(const LgsFunc* func);
    ~PostAnalyser() = default;
};
