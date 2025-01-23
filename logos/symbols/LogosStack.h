#ifndef LOGOSSTACK_H
#define LOGOSSTACK_H
#include "LogosSymbol.h"
#include <stack>
#include "types/LogosInt.h"
#include <map>

using namespace std;

class LogosStackFrame {
public:
    Function* currentFunction = nullptr;
    map<string, LogosSymbol*> symbolTable;
    map<string, Function*> functions;
};

class LogosStack : public stack<LogosStackFrame> {
public:
    void enterScope(Function* func);
    void exitScope();
    LogosSymbol* getSymbol(const string& name);
    Function* getFunc(const string& name);
    void addSymbol(const string& name, LogosSymbol* symbol);
    void addFunc(const string& name, Function* value);
    void setCurrentFunc(Function* value);
    ~LogosStack() = default;
};

inline void LogosStack::enterScope(Function* func) {
    const LogosStackFrame stackFrame(top());
    push(stackFrame);
    addFunc(func->getName().str(), func);
    setCurrentFunc(func);
}

inline void LogosStack::exitScope() {
    pop();
}

inline LogosSymbol* LogosStack::getSymbol(const string& name) {
    return top().symbolTable[name];
}

inline Function* LogosStack::getFunc(const string& name) {
    return top().functions[name];
}

inline void LogosStack::addSymbol(const string& name, LogosSymbol* symbol) {
    top().symbolTable[name] = symbol;
}

inline void LogosStack::addFunc(const string& name, Function* value) {
    top().functions[name] = value;
}

inline void LogosStack::setCurrentFunc(Function* value) {
    top().currentFunction = value;
}



#endif //LOGOSSTACK_H
