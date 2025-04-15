#ifndef LOGOSANALYSER_H
#define LOGOSANALYSER_H
#include "LgsErrors.h"
#include "LgsWarnings.h"

#include <iostream>
#include <mutex>
#include <vector>
#include <string>
#include <filesystem>

class LgsFile;
struct Location;
using namespace std;

class LgsAnalyser {
public:
    mutex mtx;
    bool successful = true;
    vector<LgsError> errors;
    vector<LgsWarning> warnings;
    filesystem::path filePath;

    void setUnsuccessful();
    string formatMsg(const string& errMsg, const vector<string>& args = {}) const;
    void handleError(const LgsError& lgsErr, const Location* location, const vector<string>& args = {});
};


#endif //LOGOSANALYSER_H
