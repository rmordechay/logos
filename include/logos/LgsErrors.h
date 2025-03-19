#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>
#include <string>

using namespace std;
inline string ERROR_PLACE_HOLDER = "%s";

enum LgsWarningCode {
    W10000, W10001, W10002, W10003, W10004, W10005, W10006, W10007, W10008, W10009,
};


#define E10000 "main() function is not defined in Main.lgs file."
#define E10001 "The left-hand type '%s' is not equal to the right-hand type '%s'."
#define E10002 "'%s' is not iterable."
#define E10003 "Number of arguments does not much. Expected: %s, Given: %s."
#define E10004 "Function %s must return %s."
#define E10005 "'%s' is not a member of '%s'."
#define E10006 "'%s' is not defined."
#define E10007 "File name '%s.lgs' is duplicate. All files in a project must be unique. Locations:%s"
#define E10008 "'Main.lgs' could not be found in 'src' directory."
#define E10009 "Duplicate Main files were found in the project. Locations:%s"
#define E10010 "Current path is not a root path of a logos project."
#define E10011 "'%s' is already declared at line %s."
#define E10012 "Function '%s' is not defined."
#define E10013 "Function '%s' is not defined with this overload. Declared overloads:%s"


const map<LgsWarningCode, string> LOGOS_WARNINGS = {
    {W10000, "variable %s is never used."},
};

#endif //LOGOSERRORS_H
