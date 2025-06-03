#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "funcs/LgsFuncImpl.h"
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
    static void generate(const vector<LgsFile*>& files);
    static void init();
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
