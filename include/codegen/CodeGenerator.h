#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H
#include <Logos.h>
#include <llvm/Target/TargetMachine.h>

class LogosFile;
class LogosValue;

const auto targetTriple = sys::getDefaultTargetTriple();
inline TargetMachine* targetMachine = nullptr;

class CodeGenerator {
public:
    static void initIR();
    static void generateCode(const LogosMainFile* mainFile, const map<string, LogosSymbol>& globalSymbols);
    static void generateMainModule(const LogosMainFile* mainFile, const map<string, LogosSymbol>& globalSymbols);
    static void generateObjectModule(LogosObject* obj, const map<string, LogosSymbol>& globalSymbols);
    static Module* createModule(const string& objName);
    static void writeIRToFile(const Module* module, const string& name);
    ~CodeGenerator() = default;
};

#endif //CODEGENERATOR_H
