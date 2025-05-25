#ifndef LOGOS_H
#define LOGOS_H
#include "utils/LgsC.h"
#include <filesystem>
#include "LgsProject.h"

struct LgsError;
class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace llvm;

class Logos {
public:
    LogosProject project;
    vector<char*> args;
    vector<LgsError> errors;

    explicit Logos(const path& rootDirPath) {
        initPaths(rootDirPath);
    }
    void run();
    void initPaths(const path& rootDirPath) const;
    ~Logos() = default;
};

#endif // LOGOS_H
