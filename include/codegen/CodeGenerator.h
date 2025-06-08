#pragma once
#include "logos/LgsProject.h"
#include <filesystem>

class LgsFile;
class LgsValue;
class LgsMainFile;
class LgsObject;

using namespace llvm;

using namespace filesystem;

class CodeGenerator {
public:
    static void init();
    static void generate(LogosProject& project);
    static void writeIRToFile(LogosProject& project);
    ~CodeGenerator() = default;
};


