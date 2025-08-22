#pragma once

struct LgsLocation {
    size_t fileID;
    size_t lineStart;
    size_t posInLine;
};

struct LgsBaseError {
    const char* const msg;
    size_t const errCode;
};

struct LgsError {
    std::string msg;
    size_t errCode;
    LgsLocation* location;
};

/** Templates errors. Should not be returned directly, but formatted and returned as a new LgsError */
inline size_t errCodeStart = 10000;
inline LgsBaseError E10000{.msg = "main() function is not defined in Main.lgs file.", .errCode = errCodeStart++};
inline LgsBaseError E10001{.msg = "Expected type '%s' does not match the given type '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10002{.msg = "Expression '%s' of type '%s' must be an iterable.", .errCode = errCodeStart++};
inline LgsBaseError E10003{.msg = "Index '%s' is out of bounds. Max expected size: %s.", .errCode = errCodeStart++};
inline LgsBaseError E10004{.msg = "Function '%s' must return an expression of type '%s'. Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10005{.msg = "'%s' is not a member of '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10006{.msg = "'%s' is not defined.", .errCode = errCodeStart++};
inline LgsBaseError E10007{.msg = "File name '%s.lgs' is duplicate. All files in a project must be unique. Locations:%s", .errCode = errCodeStart++};
inline LgsBaseError E10008{.msg = "'Main.lgs' could not be found in 'src' directory.", .errCode = errCodeStart++};
inline LgsBaseError E10009{.msg = "Duplicate Main files were found in the project. Locations:%s", .errCode = errCodeStart++};
inline LgsBaseError E10010{.msg = "Not a root path of a logos project.", .errCode = errCodeStart++};
inline LgsBaseError E10011{.msg = "'%s' is already declared.", .errCode = errCodeStart++};
inline LgsBaseError E10012{.msg = "Function call cannot be assigned to a value.", .errCode = errCodeStart++};
inline LgsBaseError E10013{.msg = "Field '%s' is with function type. Declare it as a standard function instead.", .errCode = errCodeStart++};
inline LgsBaseError E10014{.msg = "Expression of type '%s' does not match base type '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10015{.msg = "Function with name '%s' was found but it doesn't match the parameters.%pGiven:\t  %s%pExpected:  %s", .errCode = errCodeStart++};
inline LgsBaseError E10016{.msg = "Object '%s' does not fully implement '%s'. %s", .errCode = errCodeStart++};
inline LgsBaseError E10017{.msg = "'break' must be inside a for loop.", .errCode = errCodeStart++};
inline LgsBaseError E10018{.msg = "Expression of type '%s' cannot cast to type '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10019{.msg = "activeEnv '%s' could not be found in the envs directory.", .errCode = errCodeStart++};
inline LgsBaseError E10020{.msg = "Environment '%s' does not define the required field '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10021{.msg = "Only function call or block is allowed to run as coroutine.", .errCode = errCodeStart++};
inline LgsBaseError E10022{.msg = "'%s' cannot be instantiated.", .errCode = errCodeStart++};
inline LgsBaseError E10023{.msg = "Type '%s' must be nullable.", .errCode = errCodeStart++};
inline LgsBaseError E10024{.msg = "Declaration of null value must have an explict nullable type.", .errCode = errCodeStart++};
inline LgsBaseError E10025{.msg = "Only interfaces are allowed in 'implements'. Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10026{.msg = "Function '%s' must return an expression of type '%s'. None was given.", .errCode = errCodeStart++};
inline LgsBaseError E10027{.msg = "Void function can either return 'Void' type or empty 'return'. Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10028{.msg = "Default parameters must be defined lastly.", .errCode = errCodeStart++};
inline LgsBaseError E10029{.msg = "Constant field '%s' must be initialized in the class or in the constructor.", .errCode = errCodeStart++};
inline LgsBaseError E10030{.msg = "Non-public field '%s' is used outside its parent object '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10031{.msg = "Non-public method '%s' is used outside its parent object '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10032{.msg = "Singleton object '%s' cannot be instantiated.", .errCode = errCodeStart++};
inline LgsBaseError E10033{.msg = "Type name must be capitalized. Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10034{.msg = "Object '%s' has a method with name '%s' but it doesn't match the parameters.%pGiven:\t  %s%pExpected:  %s", .errCode = errCodeStart++};
inline LgsBaseError E10035{.msg = "Index of %s has %s level which is too deep. Max level: %s.", .errCode = errCodeStart++};
inline LgsBaseError E10036{.msg = "'%s' cannot be indexed with type '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10037{.msg = "Left index of slice must be less or equal than the right index. Given: %s.", .errCode = errCodeStart++};
inline LgsBaseError E10038{.msg = "'continue' must be inside a for loop.", .errCode = errCodeStart++};
inline LgsBaseError E10039{.msg = "main() function accepts only one optional parameter of type 'Str[]'.", .errCode = errCodeStart++};
inline LgsBaseError E10040{.msg = "The number of variables in the for loop (%s) do not match the number of the iterable's returned values (%s).", .errCode = errCodeStart++};
inline LgsBaseError E10041{.msg = "'%s' unpacks %s or %s, Given: %s.", .errCode = errCodeStart++};
inline LgsBaseError E10042{.msg = "Expression '%s' of type '%s' cannot be sliced.", .errCode = errCodeStart++};
inline LgsBaseError E10043{.msg = "Default parameters and variadic arguments are not allowed in the same function.", .errCode = errCodeStart++};
inline LgsBaseError E10044{.msg = "Variadic argument must be the last argument.", .errCode = errCodeStart++};
inline LgsBaseError E10045{.msg = "Variadic argument cannot have default arguments.", .errCode = errCodeStart++};
inline LgsBaseError E10046{.msg = "'%s' is not callable.", .errCode = errCodeStart++};
inline LgsBaseError E10047{.msg = "External file '%s' was not found.", .errCode = errCodeStart++};
inline LgsBaseError E10048{.msg = "Static iterable '%s' must have a constant size.", .errCode = errCodeStart++};
inline LgsBaseError E10049{.msg = "Not enough information to infer the type of the iterable. Specify an explicit type or initialize with element(s).", .errCode = errCodeStart++};
inline LgsBaseError E10050{.msg = "Only integer values can be incremented (++) or decremented (--). Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10051{.msg = "Constant field '%s' cannot be overwritten.", .errCode = errCodeStart++};
inline LgsBaseError E10052{.msg = "Spread operator in '%s...' must only be used with iterables. Given type: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10053{.msg = "'%s' is a Logos global name and cannot be redefined.", .errCode = errCodeStart++};
inline LgsBaseError E10054{.msg = "Field '%s' is set more than one time.", .errCode = errCodeStart++};
inline LgsBaseError E10055{.msg = "Function '%s' must return from all its paths.", .errCode = errCodeStart++};
inline LgsBaseError E10056{.msg = "Type '%s' has multiple fields with the same name '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10057{.msg = "Pattern matching expression '%s' must be of type Bool.", .errCode = errCodeStart++};
inline LgsBaseError E10058{.msg = "Field '%s' is defined in multiple interfaces: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10059{.msg = "Unreachable code.", .errCode = errCodeStart++};
inline LgsBaseError E10060{.msg = "'for.isFirst' and 'for.isLast' are only allowed inside a for loop.", .errCode = errCodeStart++};
inline LgsBaseError E10061{.msg = "'for.isLast' is not allowed in an infinite loop.", .errCode = errCodeStart++};
inline LgsBaseError E10062{.msg = "Interface '%s' implements all its methods which is not allowed. Make at least one of the methods abstract (without implementation) or change it to 'object'", .errCode = errCodeStart++};
inline LgsBaseError E10063{.msg = "Interfaces must have at least one (abstract) method or field.", .errCode = errCodeStart++};
inline LgsBaseError E10064{.msg = "'%s' is already defined in '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10065{.msg = "'for.isFirst' and 'for.isLast' are not allowed in a while loop.", .errCode = errCodeStart++};
inline LgsBaseError E10066{.msg = "While loop condition '%s' must be of type Bool. Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10067{.msg = "'%s' was not found.", .errCode = errCodeStart++};
inline LgsBaseError E10068{.msg = "App version must be in the form of '1.0.0'. Given: '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10069{.msg = "Too many scalars passed to '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10070{.msg = "Invalid scalars '%s' for '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10071{.msg = "'break if' must be inside an if statement.", .errCode = errCodeStart++};
inline LgsBaseError E10072{.msg = "Type '%s' has multiple methods with the same name '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10078{.msg = "Type '%s' has multiple methods with the same name '%s'.", .errCode = errCodeStart++};
inline LgsBaseError E10079{.msg = "Defer functions must return 'Void'. Given: '%s'.", .errCode = errCodeStart++};