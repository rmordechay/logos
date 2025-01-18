#ifndef LOGOSMAINPACKAGE_H
#define LOGOSMAINPACKAGE_H
#include "LogosPackage.h"
#include "files/LogosMainFile.h"
#include <string>

using namespace std;

class LogosRootPackage {
public:
    string path;
    vector<LogosFile*> files;
    vector<LogosPackage*> packages;
    LogosMainFile* mainFile = nullptr;

    explicit LogosRootPackage(const string& path) : path(path) {}
    ~LogosRootPackage();
};



#endif //LOGOSMAINPACKAGE_H
