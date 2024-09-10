#include "project/project.h"
#include "analyser/analysis.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: logos <next_command>\n");
        return 1;
    }
    char *cmd = argv[1];
    if (strcmp(cmd, "run") == 0) {
        App *app = init_project();
        analyse_src_code(app);
        free_application(app);
    }
    return 0;
}


