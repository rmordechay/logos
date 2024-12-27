#ifndef LOGOSTYPE_H
#define LOGOSTYPE_H
#include <string>

#define INT_LITERAL "Int"

class LogosType {
public:
    // LogosType() = default;
    virtual ~LogosType() = default;
    // virtual std::string getName() const = 0;
};

class LogosInt final : public LogosType {
public:
    static constexpr auto name = "Int";
    int value;
    LogosInt() = default;
    explicit LogosInt(const int value): value(value) {}
};

class LogosFloat final : public LogosType {
public:
    static constexpr auto name = "Float";
    float value;
    LogosFloat() = default;
    explicit LogosFloat(const float value): value(value) {}
};

class LogosBool final : public LogosType {
public:
    static constexpr auto name = "Bool";
    static constexpr auto trueLiteral = "true";
    static constexpr auto falseLiteral = "false";
    bool value;
    LogosBool() = default;
    explicit LogosBool(const bool value): value(value) {}
};

class LogosString final : public LogosType {
public:
    static constexpr auto name = "Str";
    std::string value;
    LogosString() = default;
    explicit LogosString(const std::string& value): value(value) {}
};

#endif //LOGOSTYPE_H
