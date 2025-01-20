#include "LogosStack.h"

#include <iostream>

void LogosStack::enterScope(Function* func) {
    const LogosStackFrame stackFrame(top());
    push(stackFrame);
    addFunc(func->getName().str(), func);
    setCurrentFunc(func);
}

void LogosStack::exitScope() {
    pop();
}

LogosSymbol* LogosStack::getSymbol(const string& name) {
    return top().symbolTable[name];
}

Function* LogosStack::getFunc(const string& name) {
    return top().functions[name];
}

void LogosStack::addSymbol(const string& name, LogosSymbol* symbol) {
    top().symbolTable[name] = symbol;
}

void LogosStack::addFunc(const string& name, Function* value) {
    top().functions[name] = value;
}

void LogosStack::setCurrentFunc(Function* value) {
    top().currentFunction = value;
}