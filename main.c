#include "project/project.h"
#include "analyser/object_analyser.h"

void create_map();

int main() {
    App *app = init_project();
    analyse_tree(app);
    free_application(app);
    return 0;
}


