#ifndef LOGOSCOMMAND_H
#define LOGOSCOMMAND_H
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class LogosCliCmd {
public:
    vector<string> flags;

    static void exitWithMsg(const string& errorMsg);
    virtual void init(int argc, char** argv) = 0;
    virtual void runCmd() = 0;
    virtual ~LogosCliCmd() = default;
};

#endif //LOGOSCOMMAND_H
