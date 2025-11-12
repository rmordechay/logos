#include "cli/LgsCliHandler.h"

int main(const int argc, char** argv) {
    const LgsCliHandler cli(argc, argv);
    if (!cli.execute()) return 1;
    return 0;
}
