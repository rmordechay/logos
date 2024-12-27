#ifndef LOGOSVALUE_H
#define LOGOSVALUE_H
#include <string>

enum class ValueType { EMPTY, INT, FLOAT, BOOL, STRING };

class LogosValue {
public:
    ValueType type;

    union Value {
        const int* intValue;
        const float* floatValue;
        const bool* boolValue;
        const std::string* stringValue;
    } value{};

    LogosValue(const ValueType type, const int* value) : type(type) {
        this->value.intValue = value;
    }

    LogosValue(const ValueType type, const float* value) : type(type) {
        this->value.floatValue = value;
    }

    LogosValue(const ValueType type, const bool* value) : type(type) {
        this->value.boolValue = value;
    }

    LogosValue(const ValueType type, const std::string* value) : type(type) {
        this->value.stringValue = value;
    }
};

#endif // LOGOSVALUE_H
