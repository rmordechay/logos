#ifndef LOGOSFILE_H
#define LOGOSFILE_H
#include "LogosParser.h"

#include <string>

using namespace std;

class LogosFile {
public:
    string name;

    explicit LogosFile(const string& name) : name(name) {}
    virtual ~LogosFile() = default;
};

#endif //LOGOSFILE_H
