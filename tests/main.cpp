#include "utils/LgsUtils.h"

#include <gtest/gtest.h>

int main(int argc, char** argv) {
    initLLVM();
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}