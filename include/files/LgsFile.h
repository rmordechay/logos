#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include <string>

class LgsStack;
using namespace std;

class LgsFile {
public:
    string name;
    string absPath;
    string relPath;

    explicit LgsFile(const string& name, const string& path) : name(name), absPath(path) {}
    virtual ~LgsFile() = default;
};

#endif //LOGOSFILE_H
