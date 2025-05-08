#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include "funcs/LgsFuncImpl.h"
#include "types/LgsType.h"

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
    static void generate(LgsMainFile* mainFile, bool writeToFile = true);
    static void generateMainFunc(CodeGenMetadata* metadata, LgsFuncImpl* mainFunc);
    static void createIRMainFunc(const CodeGenMetadata* metadata);
    static void generateObjModule(const LgsType* obj, bool writeToFile = true);
    static Module* createEmptyModule(const std::string& objName);
    static void writeIRToFile(const Module* module, const path& name);
    static void createBuildDir();
    static void initLLVM();
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
