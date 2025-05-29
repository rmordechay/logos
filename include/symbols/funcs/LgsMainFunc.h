#ifndef LGSMAINFUNC_H
#define LGSMAINFUNC_H
#include "LgsFuncImpl.h"
#include "types/array/LgsArray.h"
#include "types/str/LgsStr.h"

class LgsMainFunc final : public LgsFuncImpl {
public:
    explicit LgsMainFunc() : LgsFuncImpl(LOGOS_MAIN_FUNC, &LGS_INT) {}
    ~LgsMainFunc() override = default;
};

#endif //LGSMAINFUNC_H
