#include "cli/LgsCli.h"

int main(const int argc, char* argv[]) {
    const LgsCli cli(argc, argv);
    cli.execute();
    return 0;
}