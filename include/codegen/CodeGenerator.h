#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
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
    static void generateModule(const path& buildDir, const LgsMainFile* mainFile, bool writeToFile = true);
    static void generateModule(const path& buildDir, LgsObject* obj, bool writeToFile = true);
    static Module* createEmptryModule(const std::string& objName);
    static void writeIRToFile(const Module* module, const path& buildDir, const path& name);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
