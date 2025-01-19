#include "LogosStack.h"

#include <iostream>

void LogosStack::enterScope() {
    const LogosStackFrame stackFrame(top());
    push(stackFrame);
}

void LogosStack::exitScope() {
    pop();
}

Value* LogosStack::getSymbol(const string& name) {
    return top().symbolTable[name];
}

Function* LogosStack::getFunc(const string& name) {
    return top().functions[name];
}

void LogosStack::addSymbol(const string& name, Value* value) {
    top().symbolTable[name] = value;
}

void LogosStack::addFunc(const string& name, Function* value) {
    top().functions[name] = value;
}

void LogosStack::setCurrentFunc(Function* value) {
    top().currentFunction = value;
}