#pragma once

class LgsProject;

class CodeGenerator {
public:
    static void init();
    static void writeIRToFile(LgsProject& project);
    ~CodeGenerator() = default;
};


