#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>
#include <string>

using namespace std;

inline string ERROR_PLACE_HOLDER = "%s";

struct LgsError {
    int errCode;
    string msg;
};

inline int errCodeStart = 10000;
inline LgsError E10000{.errCode = errCodeStart, .msg = "main() function is not defined in Main.lgs file."};
inline LgsError E10001{.errCode = ++errCodeStart, .msg = "The left-hand type '%s' is not equal to the right-hand type '%s'."};
inline LgsError E10002{.errCode = ++errCodeStart, .msg = "'%s' is not iterable."};
inline LgsError E10003{.errCode = ++errCodeStart, .msg = "Number of arguments does not much. Expected: %s, Given: %s."};
inline LgsError E10004{.errCode = ++errCodeStart, .msg = "Function '%s' must return '%s'."};
inline LgsError E10005{.errCode = ++errCodeStart, .msg = "'%s' is not a member of '%s'."};
inline LgsError E10006{.errCode = ++errCodeStart, .msg = "'%s' is not defined."};
inline LgsError E10007{.errCode = ++errCodeStart, .msg = "File name '%s.lgs' is duplicate. All files in a project must be unique. Locations:%s"};
inline LgsError E10008{.errCode = ++errCodeStart, .msg = "'Main.lgs' could not be found in 'src' directory."};
inline LgsError E10009{.errCode = ++errCodeStart, .msg = "Duplicate Main files were found in the project. Locations:%s"};
inline LgsError E10010{.errCode = ++errCodeStart, .msg = "Current path is not a root path of a logos project."};
inline LgsError E10011{.errCode = ++errCodeStart, .msg = "'%s' is already declared at line %s."};
inline LgsError E10012{.errCode = ++errCodeStart, .msg = "Function '%s' is not defined."};
inline LgsError E10013{.errCode = ++errCodeStart, .msg = "Function '%s' is not defined with this overload. Declared overloads:%s"};
inline LgsError E10014{.errCode = ++errCodeStart, .msg = "Pattern of type '%s' does not match base type '%s'."};
inline LgsError E10015{.errCode = ++errCodeStart, .msg = "Arguments with types (%s) do not match any overload of the function '%s'"};

#endif //LOGOSERRORS_H
