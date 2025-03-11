#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <string>

class LogosStack;
using namespace std;

class LogosFile {
public:
    string name;
    string absPath;
    string relPath;

    explicit LogosFile(const string& name, const string& path) : name(name), absPath(path) {}
    virtual ~LogosFile() = default;
};

#endif //LOGOSFILE_H
