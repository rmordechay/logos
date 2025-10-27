#pragma once
#include <fstream>
#include <string>

struct LgsLocation {
    size_t fileID = 0;
    size_t index = 0;
    size_t lineStart = 0;
    size_t columnStart = 0;
};

struct LgsBaseError {
    const char* const msg;
    size_t const code;
    LgsBaseError(const char* msg, const size_t code) : msg(msg), code(code) {}
};

struct LgsError {
    std::string msg;
    size_t errCode;
    LgsLocation location;
    std::string filePath = "";

    LgsError(const std::string& msg, const size_t errCode) : msg(msg), errCode(errCode) {}
    LgsError(const std::string& msg, const size_t errCode, const LgsLocation& location) : msg(msg), errCode(errCode), location(location) {}
};

/** Templates errors. Should not be returned directly, but formatted and returned as a new LgsError */
inline size_t errCodeStart = 10000;
inline LgsBaseError E10000{"main() function is not defined in Main.lgs file.", errCodeStart++};
inline LgsBaseError E10001{"Expected type %s does not match the given type %s.", errCodeStart++};
inline LgsBaseError E10002{"Expression %s of type %s must be an iterable.", errCodeStart++};
inline LgsBaseError E10003{"Index is out of bounds.", errCodeStart++};
inline LgsBaseError E10004{"Function %s must return an expression of type %s. Given: %s.", errCodeStart++};
inline LgsBaseError E10005{"%s is not a member of %s.", errCodeStart++};
inline LgsBaseError E10006{"%s is not defined.", errCodeStart++};
inline LgsBaseError E10007{"File %s is duplicate. All files in a project must be unique.", errCodeStart++};
inline LgsBaseError E10008{"Main.lgs could not be found in src directory.", errCodeStart++};
inline LgsBaseError E10009{"Duplicate Main files were found in the project. Locations:%s", errCodeStart++};
inline LgsBaseError E10010{"Not a root path of a Logos project.", errCodeStart++};
inline LgsBaseError E10011{"%s is already declared.", errCodeStart++};
inline LgsBaseError E10012{"%s cannot be %s-assigned to type %s.", errCodeStart++};
inline LgsBaseError E10013{"Field %s is with function type. Declare it as a standard function instead.", errCodeStart++};
inline LgsBaseError E10014{"Expression of type %s does not match base type %s.", errCodeStart++};
inline LgsBaseError E10015{"Function %s was found but it doesnt match the parameters.\nGiven:\t  %s\nExpected:  %s", errCodeStart++};
inline LgsBaseError E10016{"Object %s does not fully implement %s.\n%s", errCodeStart++};
inline LgsBaseError E10017{"break must be inside a for loop.", errCodeStart++};
inline LgsBaseError E10018{"%s cannot cast to type %s.", errCodeStart++};
inline LgsBaseError E10019{"activeEnv %s could not be found in the envs directory.", errCodeStart++};
inline LgsBaseError E10020{"Environment '%s' must declare the required variable '%s' of type '%s'.", errCodeStart++};
inline LgsBaseError E10021{"%s and %s must be the same type. Given: %s and %s.", errCodeStart++};
inline LgsBaseError E10022{"%s cannot be instantiated.", errCodeStart++};
inline LgsBaseError E10023{"Expression with type %s must be nullable.", errCodeStart++};
inline LgsBaseError E10024{"null must have an explict nullable type.", errCodeStart++};
inline LgsBaseError E10025{"Only interfaces are allowed in implements. Given: %s.", errCodeStart++};
inline LgsBaseError E10026{"Function %s must return an expression of type %s. None was given.", errCodeStart++};
inline LgsBaseError E10027{"Void function can either return Void type or empty return. Given: %s.", errCodeStart++};
inline LgsBaseError E10028{"Default parameters must be defined lastly.", errCodeStart++};
inline LgsBaseError E10029{"Constant field %s must be initialized in the class or in the constructor.", errCodeStart++};
inline LgsBaseError E10030{"Non-public field %s is used outside its parent object %s.", errCodeStart++};
inline LgsBaseError E10031{"Non-public method %s is used outside its parent object %s.", errCodeStart++};
inline LgsBaseError E10032{"Singleton object %s cannot be instantiated.", errCodeStart++};
inline LgsBaseError E10033{"Type name must be capitalized. Given: %s.", errCodeStart++};
inline LgsBaseError E10034{"%s has a method with name %s but it doesnt match the parameters.\nGiven:\t  %s\nExpected:  %s", errCodeStart++};
inline LgsBaseError E10035{"Index of %s has %s level which is too deep. Max level: %s.", errCodeStart++};
inline LgsBaseError E10036{"%s cannot be indexed with type %s.", errCodeStart++};
inline LgsBaseError E10037{"Left index of slice must be less or equal than the right index.", errCodeStart++};
inline LgsBaseError E10038{"continue must be inside a for loop.", errCodeStart++};
inline LgsBaseError E10039{"main() function accepts only one optional parameter of type Str[].", errCodeStart++};
inline LgsBaseError E10040{"The number of variables in the for loop (%s) do not match the number of the iterables returned values (%s).", errCodeStart++};
inline LgsBaseError E10041{"Could not unpack iterable %s of type %s with %s variables.", errCodeStart++};
inline LgsBaseError E10042{"Expression %s of type %s cannot be sliced.", errCodeStart++};
inline LgsBaseError E10043{"Default parameters and variadic arguments are not allowed in the same function.", errCodeStart++};
inline LgsBaseError E10044{"Variadic argument must be the last argument.", errCodeStart++};
inline LgsBaseError E10045{"Variadic argument cannot have default arguments.", errCodeStart++};
inline LgsBaseError E10046{"%s is not callable.", errCodeStart++};
inline LgsBaseError E10047{"External file %s was not found.", errCodeStart++};
inline LgsBaseError E10048{"Index %s is out of bounds. Max expected index: %s", errCodeStart++};
inline LgsBaseError E10049{"Not enough information to infer type of %s.", errCodeStart++};
inline LgsBaseError E10050{"Only integer values can be incremented (++) or decremented (--). Given: %s.", errCodeStart++};
inline LgsBaseError E10051{"%s is constant and cannot be overwritten.", errCodeStart++};
inline LgsBaseError E10052{"Spread operator in %s... must only be used with iterables. Given type: %s.", errCodeStart++};
inline LgsBaseError E10053{"%s is a Logos global name and cannot be redefined.", errCodeStart++};
inline LgsBaseError E10054{"Field %s is set more than one time.", errCodeStart++};
inline LgsBaseError E10055{"Function %s must return from all its paths.", errCodeStart++};
inline LgsBaseError E10056{"Type %s has multiple fields with the same name %s.", errCodeStart++};
inline LgsBaseError E10057{"Pattern matching expression %s must be of type Bool.", errCodeStart++};
inline LgsBaseError E10058{"Field %s is defined in multiple interfaces: %s.", errCodeStart++};
inline LgsBaseError E10059{"Unreachable code.", errCodeStart++};
inline LgsBaseError E10060{"for.isFirst and for.isLast are only allowed inside a for loop.", errCodeStart++};
inline LgsBaseError E10061{"%s is not allowed in an infinite loop.", errCodeStart++};
inline LgsBaseError E10062{"Interface %s implements all its methods which is not allowed. Make at least one of the methods abstract (without implementation) or change it to object", errCodeStart++};
inline LgsBaseError E10063{"Interfaces must have at least one (abstract) method or field.", errCodeStart++};
inline LgsBaseError E10064{"%s is already defined in %s.", errCodeStart++};
inline LgsBaseError E10065{"%s is not allowed in a while loop.", errCodeStart++};
inline LgsBaseError E10066{"While loop condition %s must be of type Bool. Given: %s.", errCodeStart++};
inline LgsBaseError E10067{"%s was not found.", errCodeStart++};
inline LgsBaseError E10068{"App version must be in the form of 1.0.0. Given: %s.", errCodeStart++};
inline LgsBaseError E10069{"Too many scalars passed to %s.", errCodeStart++};
inline LgsBaseError E10070{"Invalid scalars %s for %s.", errCodeStart++};
inline LgsBaseError E10071{"break if must be inside an if statement.", errCodeStart++};
inline LgsBaseError E10072{"Type %s has multiple methods with the same name %s.", errCodeStart++};
inline LgsBaseError E10073{"Only numbers or vectors can be elements of a vector. Given: %s.", errCodeStart++};
inline LgsBaseError E10074{"Vector mismatch. Vector dimension: %s. Given: %s.", errCodeStart++};
inline LgsBaseError E10075{"Expression %s already has an owner.", errCodeStart++};
inline LgsBaseError E10076{"'%s' is not defined between %s and %s.", errCodeStart++}; // operation, left-expr, right-expr
inline LgsBaseError E10077{"Expression %s has no owner.", errCodeStart++};
inline LgsBaseError E10078{"Defer functions must return Void. Given: %s.", errCodeStart++};
inline LgsBaseError E10079{"Test file %s must be inside tests directory.", errCodeStart++};
inline LgsBaseError E10080{"Index %s was not found in iterable.", errCodeStart++};
inline LgsBaseError E10081{"Range-start type %s is not equal to the range-end type %s.", errCodeStart++};
inline LgsBaseError E10082{"Loop range %s must be a number. Given: %s.", errCodeStart++};
inline LgsBaseError E10083{"Method %s is an object method but was called as a class method.", errCodeStart++};
inline LgsBaseError E10084{"%s does not belong to an IO pair.", errCodeStart++};
inline LgsBaseError E10085{"Parsing error.", errCodeStart++};
inline LgsBaseError E10086{"Invalid Logos file path: %s.", errCodeStart++};
inline LgsBaseError E10087{"Lexing error.", errCodeStart++};
inline LgsBaseError E10088{"Bad character.", errCodeStart++};
inline LgsBaseError E10089{"%s can only be assigned to an instance of %s, not the object itself.", errCodeStart++};
inline LgsBaseError E10090{"%s can only prefix numbers. Given: %s.", errCodeStart++};
inline LgsBaseError E10091{"not can only prefix Bool. Given: %s.", errCodeStart++};
inline LgsBaseError E10092{"Condition %s must be of type Bool. Given: %s.", errCodeStart++};
