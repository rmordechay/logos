#include "gen/parser.h"
#include "project/project.h"

void analyse_tree(App *app);

int main() {
    App *app = init_project();
    analyse_tree(app);
    free_application(app);
    return 0;
}


