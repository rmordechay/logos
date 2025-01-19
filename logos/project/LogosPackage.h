#ifndef LOGOSPACKAGE_H
#define LOGOSPACKAGE_H
#include "files/LogosFile.h"
#include "LogosDefinitions.h"

#include <string>
#include <vector>

using namespace std;

class LogosPackage {
public:
    string name;
    string path;
    vector<LogosFile*> files;
    vector<LogosPackage*> packages;

    LogosPackage(const string& name, const string& path) : name(name), path(filesystem::absolute(path).string()) {}
    ~LogosPackage();
};


#endif // LOGOSPACKAGE_H
