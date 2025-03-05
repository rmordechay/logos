#ifndef LOGOSUTILS_H
#define LOGOSUTILS_H

#include "exprs/LogosInstance.h"
#include <llvm/Target/TargetMachine.h>
#include <filesystem>

using namespace std;
using namespace llvm;

class Utils {
public:
    static bool isLogosFile(const filesystem::directory_entry& filePath);
    static bool isMainFile(const filesystem::directory_entry& filePath);
    static void emitIRFile(const string& filePath, Module* module);
};


#endif //LOGOSUTILS_H
