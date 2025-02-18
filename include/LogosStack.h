#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "symbols/LogosSymbol.h"
#include <stack>
#include <map>
#include <llvm/IR/Module.h>

using namespace std;
using namespace llvm;

struct LogosStackFrame {
    map<string, LogosSymbol> symbols;
};

class LogosStack : stack<LogosStackFrame> {
public:
    map<string, LogosSymbol> globalSymbols;
    Function* currentFunc = nullptr;

    void enterScope(Function* func);
    void enterScope();
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    void addLocalSymbol(const string& name, const LogosSymbol& symbol);
    void addGlobalSymbol(const string& name, const LogosSymbol& symbol);
    void deleteGlobalSymbol(const string& name);
    void reset();
    ~LogosStack() = default;
};



#endif //LOGOSSTACK_H
