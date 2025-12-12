#pragma once
#include <string>
class LgsType;

class LgsOwner {
public:
    virtual std::string getName() = 0;
    virtual LgsType* getType() = 0;
    virtual ~LgsOwner() = default;
};
