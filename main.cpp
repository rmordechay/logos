#include "cli/LgsCli.h"
#include "src/logos/LgsC.cpp"

int main(const int argc, char* argv[]) {
    const LgsCli cli(argc, argv);
    cli.execute();
    return 0;
}
