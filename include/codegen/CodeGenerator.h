#pragma once

class LgsApp;

class CodeGenerator {
public:
    static void init();
    static void writeIRToFile(LgsApp& project);
    ~CodeGenerator() = default;
};


