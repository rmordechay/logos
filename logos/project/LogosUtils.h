#ifndef LOGOSUTILS_H
#define LOGOSUTILS_H

#include "LogosDefinitions.h"
#include <__filesystem/directory_entry.h>

using namespace std;

class Utils {
public:
    static bool isLogosFile(const filesystem::directory_entry& filePath);
    static bool isMainFile(const filesystem::directory_entry& filePath);
};

#endif //LOGOSUTILS_H
