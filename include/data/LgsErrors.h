#ifndef LOGOSERRORS_H
#define LOGOSERRORS_H
#include <map>
#include <string>

using namespace std;

inline string ERROR_PLACEHOLDER = "%s";

struct LgsError {
    string msg;
    int errCode;
};

/** Templates errors. Should not be returned directly, but formatted and returned as a new LgsError */
inline int errCodeStart = 10000;
inline LgsError E10000{.msg = "main() function is not defined in Main.lgs file.", .errCode = errCodeStart};
inline LgsError E10001{.msg = "The left-hand type '%s' is not equal to the right-hand type '%s'.", .errCode = ++errCodeStart};
inline LgsError E10002{.msg = "'%s' is not iterable.", .errCode = ++errCodeStart};
inline LgsError E10003{.msg = "Number of arguments does not much. Expected: %s, Given: %s.", .errCode = ++errCodeStart};
inline LgsError E10004{.msg = "Function '%s' must return '%s'.", .errCode = ++errCodeStart};
inline LgsError E10005{.msg = "Field '%s' is not a member of '%s'.", .errCode = ++errCodeStart};
inline LgsError E10006{.msg = "'%s' is not defined.", .errCode = ++errCodeStart};
inline LgsError E10007{.msg = "File name '%s.lgs' is duplicate. All files in a project must be unique. Locations:%s", .errCode = ++errCodeStart};
inline LgsError E10008{.msg = "'Main.lgs' could not be found in 'src' directory.", .errCode = ++errCodeStart};
inline LgsError E10009{.msg = "Duplicate Main files were found in the project. Locations:%s", .errCode = ++errCodeStart};
inline LgsError E10010{.msg = "Current path is not a root path of a logos project.", .errCode = ++errCodeStart};
inline LgsError E10011{.msg = "'%s' is already declared at line %s.", .errCode = ++errCodeStart};
inline LgsError E10012{.msg = "Function '%s' is not defined.", .errCode = ++errCodeStart};
inline LgsError E10013{.msg = "Function '%s' is not a member of '%s'.", .errCode = ++errCodeStart};
inline LgsError E10014{.msg = "Pattern of type '%s' does not match base type '%s'.", .errCode = ++errCodeStart};
inline LgsError E10015{.msg = "Function with name '%s' was found but it does not match any overload.\n\t   Given: %s\n\t   Possible overloads:%s", .errCode = ++errCodeStart};
inline LgsError E10016{.msg = "Object '%s' does not fully implement '%s'. Missing functions:%s", .errCode = ++errCodeStart};
inline LgsError E10017{.msg = "break is not part of a loop.", .errCode = ++errCodeStart};
inline LgsError E10018{.msg = "Expression of type '%s' cannot be casted to type '%s'.", .errCode = ++errCodeStart};
inline LgsError E10019{.msg = "activeEnv '%s' could not be found in the envs directory.", .errCode = ++errCodeStart};
inline LgsError E10020{.msg = "Environment '%s' does not define the required field '%s'.", .errCode = ++errCodeStart};
inline LgsError E10021{.msg = "Duplicate fields were found in enum '%'.", .errCode = ++errCodeStart};
inline LgsError E10022{.msg = "'%s' cannot be instantiated.", .errCode = ++errCodeStart};
inline LgsError E10023{.msg = "Type '%s' must be nullable. Change the type to %s? or set a value.", .errCode = ++errCodeStart};
inline LgsError E10024{.msg = "Declaration of null value must have an explict nullable type.", .errCode = ++errCodeStart};
inline LgsError E10025{.msg = "'%s' must be an interface.", .errCode = ++errCodeStart};
inline LgsError E10026{.msg = "Function '%s' must return an expression of type '%s'. None was given.", .errCode = ++errCodeStart};
inline LgsError E10027{.msg = "Function '%s' must return '%s'. Given: '%s'.", .errCode = ++errCodeStart};
inline LgsError E10028{.msg = "Default parameters must be defined lastly.", .errCode = ++errCodeStart};
inline LgsError E10029{.msg = "const field '%s' must be initialized in the constructor.", .errCode = ++errCodeStart};
inline LgsError E10030{.msg = "Non-public field '%s' is used outside its parent object '%s'.", .errCode = ++errCodeStart};
inline LgsError E10031{.msg = "Non-public method '%s' is used outside its parent object '%s'.", .errCode = ++errCodeStart};
inline LgsError E10032{.msg = "Singleton object '%s' cannot be instantiated.", .errCode = ++errCodeStart};
inline LgsError E10033{.msg = "Function '%s' is declared multiple times.", .errCode = ++errCodeStart};
inline LgsError E10034{.msg = "Object '%s' has method(s) with name '%s' but it does not match any overload.\n\t   Given: %s\n\t   Possible overloads:%s", .errCode = ++errCodeStart};

#endif //LOGOSERRORS_H
