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
    static void generate(LgsMainFile* mainFile);
    static void generateMainFunc(CodegenMetadata* metadata, LgsFuncImpl* mainFunc);
    static void createIRMainFunc(const CodegenMetadata* metadata);
    static void generateObjModule(const LgsType* obj);
    static Module* createEmptyModule(const std::string& objName);
    static void writeIRToFile(const Module* module, const path& name);
    static void init();
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
