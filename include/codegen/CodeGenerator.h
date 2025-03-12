#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Logos.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/TargetParser/Host.h>

class LogosFile;
class LogosValue;

const auto targetTriple = sys::getDefaultTargetTriple();
inline TargetMachine* targetMachine = nullptr;

class CodeGenerator {
public:
    path buildDir;

    explicit CodeGenerator(const path& buildDir) : buildDir(buildDir) {}
    void init();
    void generateCode(const LogosMainFile* mainFile, const map<string, LogosSymbol>& globalSymbols);
    void generateModule(const LogosMainFile* mainFile, const map<string, LogosSymbol>& globalSymbols) const;
    static void generateModule(LogosObject* obj, const map<string, LogosSymbol>& globalSymbols, const path& buildDir);
    static Module* createModule(const string& objName);
    static void writeIRToFile(const Module* module, const path& buildDir, const path& name);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
