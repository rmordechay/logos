#include <gtest/gtest.h>
#include "LgsConfigs.h"
#include "codegen/LgsCodeGen.h"

int main(int argc, char** argv) {
    LgsCodeGen::initLLVM();
    lgsConfigs.isDevMode = true;
    lgsConfigs.isTestMode = true;
    lgsConfigs.printIR = false;
    lgsConfigs.writeIRFiles = false;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
