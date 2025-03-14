#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>
#include <string>

using namespace std;
inline string ERROR_PLACE_HOLDER = "%s";

enum LgsErrCode {
    E10000, E10001, E10002, E10003, E10004, E10005, E10006, E10007, E10008, E10009,
    E10010, E10011, E10012, E10013, E10014, E10015, E10016, E10017, E10018, E10019,
    E10020, E10021, E10022, E10023, E10024, E10025, E10026, E10027, E10028, E10029,
    E10030, E10031, E10032, E10033, E10034, E10035, E10036, E10037, E10038, E10039,
};

enum LgsWarningCode {
    E50000, E50001, E50002, E50003, E50004, E50005, E50006, E50007, E50008, E50009,
};

const map<LgsErrCode, string> LOGOS_ERRORS = {
    {E10000, "main() function is not defined in Main.lgs file."},
    {E10001, "The left-hand type '%s' is not equal to the right-hand type '%s'."},
    {E10002, "'%s' is not iterable."},
    {E10003, "Number of arguments does not much. Expected: %s, Given: %s."},
    {E10004, "Function %s must return %s."},
    {E10005, "'%s' is not a member of '%s'."},
    {E10006, "'%s' is not defined."},
    {E10007, "File name '%s.lgs' is duplicate. All files in a project must be unique. Locations:%s"},
    {E10008, "'Main.lgs' could not be found in 'src' directory"},
    {E10009, "Duplicate Main files were found in the project. Locations:%s"},
    {E10010, "Current path is not a root path of a logos project"},
    {E10011, "'{}' is already declared at {}"},
};

const map<LgsWarningCode, string> LOGOS_WARNINGS = {
    {E50000, "variable %s is never used."},
};

#endif //LOGOSERRORS_H
