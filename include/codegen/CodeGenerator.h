#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "types/LgsType.h"

#include <filesystem>
#include <llvm/IR/Module.h>
class LgsFile;
class LgsValue;
class LgsMainFile;
class LgsObject;

using namespace llvm;
using namespace std;
using namespace filesystem;

class CodeGenerator {
public:
    static void generate(LgsMainFile* mainFile, bool writeToFile = true);
    static void generateObjModule(const LgsType* obj, bool writeToFile = true);
    static Module* createEmptyModule(const std::string& objName);
    static void writeIRToFile(const Module* module, const path& name);
    static void createBuildDir();
    static void initLLVM();
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
