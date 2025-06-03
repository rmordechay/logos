#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "logos/LgsProject.h"
#include <filesystem>

class LgsFile;
class LgsValue;
class LgsMainFile;
class LgsObject;

using namespace llvm;
using namespace std;
using namespace filesystem;

class CodeGenerator {
public:
    static void init();
    static void generate(const LogosProject* project);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
