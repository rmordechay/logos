#ifndef LGSENV_H
#define LGSENV_H
#include <map>
#include <string>

class LgsActiveEnv {
public:
    std::string name;
    std::map<std::string, std::string> envVars;
};

#endif //LGSENV_H
