#include "cli/LgsCli.h"

int main(const int argc, char** argv) {
    const LgsCli cli(argc, argv);
    if (!cli.execute()) return 1;
    return 0;
}
