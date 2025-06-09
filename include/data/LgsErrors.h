#pragma once


inline string ERROR_PLACEHOLDER = "%s";

struct LgsError {
    string msg;
    int errCode;
};

/** Templates errors. Should not be returned directly, but formatted and returned as a new LgsError */
inline int errCodeStart = 10000;
inline LgsError E10000{.msg = "main() function is not defined in Main.lgs file.", .errCode = errCodeStart++};
inline LgsError E10001{.msg = "Left type '%s' does not match the right type '%s'.", .errCode = errCodeStart++};
inline LgsError E10002{.msg = "'%s' must be an iterable.", .errCode = errCodeStart++};
inline LgsError E10003{.msg = "Array index '%s' is out of bounds.", .errCode = errCodeStart++};
inline LgsError E10004{.msg = "Function '%s' must return expression of type '%s'. Given: '%s'.", .errCode = errCodeStart++};
inline LgsError E10005{.msg = "Field '%s' is not a member of '%s'.", .errCode = errCodeStart++};
inline LgsError E10006{.msg = "'%s' is not defined.", .errCode = errCodeStart++};
inline LgsError E10007{.msg = "File name '%s.lgs' is duplicate. All files in a project must be unique. Locations:%s", .errCode = errCodeStart++};
inline LgsError E10008{.msg = "'Main.lgs' could not be found in 'src' directory.", .errCode = errCodeStart++};
inline LgsError E10009{.msg = "Duplicate Main files were found in the project. Locations:%s", .errCode = errCodeStart++};
inline LgsError E10010{.msg = "Current path is not a root path of a logos project.", .errCode = errCodeStart++};
inline LgsError E10011{.msg = "'%s' is already declared at line %s.", .errCode = errCodeStart++};
inline LgsError E10012{.msg = "Function '%s' is not defined.", .errCode = errCodeStart++};
inline LgsError E10013{.msg = "Function '%s' is not a member of '%s'.", .errCode = errCodeStart++};
inline LgsError E10014{.msg = "Pattern of type '%s' does not match base type '%s'.", .errCode = errCodeStart++};
inline LgsError E10015{.msg = "Function with name '%s' was found but it doesn't match the parameters.\n\t   Given:    %s\n\t   Expected: %s", .errCode = errCodeStart++};
inline LgsError E10016{.msg = "Object '%s' does not fully implement '%s'. Missing functions:%s", .errCode = errCodeStart++};
inline LgsError E10017{.msg = "'break' must be inside a loop statement.", .errCode = errCodeStart++};
inline LgsError E10018{.msg = "Expression of type '%s' cannot be casted to type '%s'.", .errCode = errCodeStart++};
inline LgsError E10019{.msg = "activeEnv '%s' could not be found in the envs directory.", .errCode = errCodeStart++};
inline LgsError E10020{.msg = "Environment '%s' does not define the required field '%s'.", .errCode = errCodeStart++};
inline LgsError E10021{.msg = "Duplicate fields were found in enum '%'.", .errCode = errCodeStart++};
inline LgsError E10022{.msg = "'%s' cannot be instantiated.", .errCode = errCodeStart++};
inline LgsError E10023{.msg = "Type '%s' must be nullable. Change the type to %s? or set a value.", .errCode = errCodeStart++};
inline LgsError E10024{.msg = "Declaration of null value must have an explict nullable type.", .errCode = errCodeStart++};
inline LgsError E10025{.msg = "'%s' must be an interface.", .errCode = errCodeStart++};
inline LgsError E10026{.msg = "Function '%s' must return expression of type '%s'. None was given.", .errCode = errCodeStart++};
inline LgsError E10027{.msg = "Void function must not return a value. Given: '%s'.", .errCode = errCodeStart++};
inline LgsError E10028{.msg = "Default parameters must be defined lastly.", .errCode = errCodeStart++};
inline LgsError E10029{.msg = "const field '%s' must be initialized in the constructor.", .errCode = errCodeStart++};
inline LgsError E10030{.msg = "Non-public field '%s' is used outside its parent object '%s'.", .errCode = errCodeStart++};
inline LgsError E10031{.msg = "Non-public method '%s' is used outside its parent object '%s'.", .errCode = errCodeStart++};
inline LgsError E10032{.msg = "Singleton object '%s' cannot be instantiated.", .errCode = errCodeStart++};
inline LgsError E10033{.msg = "Function '%s' is declared multiple times.", .errCode = errCodeStart++};
inline LgsError E10034{.msg = "Object '%s' has a method with name '%s' but it doesn't match the parameters.\n\t   Given:    %s\n\t   Expected: %s", .errCode = errCodeStart++};
inline LgsError E10035{.msg = "Index of %s has %s level which is too deep. Max level: %s.", .errCode = errCodeStart++};
inline LgsError E10036{.msg = "'%s' cannot be indexed with type '%s'.", .errCode = errCodeStart++};
inline LgsError E10037{.msg = "Left-hand index of slice must be less than right-hand index. Given: %s.", .errCode = errCodeStart++};
inline LgsError E10038{.msg = "'continue' must be inside a loop statement.", .errCode = errCodeStart++};
inline LgsError E10039{.msg = "main() function accepts only one optional parameter of type 'Str[]'.", .errCode = errCodeStart++};
inline LgsError E10040{.msg = "The number of variables in the for loop (%s) do not match the number of the iterable's returned values (%s).", .errCode = errCodeStart++};
inline LgsError E10041{.msg = "'%s' unpacks %s variables, not %s.", .errCode = errCodeStart++};
inline LgsError E10042{.msg = "Left index in slice must be less than the right index. Given: '%s'.", .errCode = errCodeStart++};
inline LgsError E10043{.msg = "Default parameters and variadic arguments are not allowed in the same function.", .errCode = errCodeStart++};
inline LgsError E10044{.msg = "Variadic argument must be the last argument.", .errCode = errCodeStart++};
inline LgsError E10045{.msg = "Variadic argument cannot have default arguments.", .errCode = errCodeStart++};
inline LgsError E10046{.msg = "'%s' is not callable.", .errCode = errCodeStart++};
inline LgsError E10047{.msg = "External file '%s' was not found.", .errCode = errCodeStart++};
inline LgsError E10048{.msg = "Static array must have a constant size.", .errCode = errCodeStart++};
inline LgsError E10049{.msg = "Not enough information to infer type of array. Specify an explicit type or initialize with element(s).", .errCode = errCodeStart++};


