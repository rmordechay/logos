#include <stdlib.h>
#include <string.h>
#include "project.h"

#define LOGOS_FILE_EXT "lgs"

/**
 *
 */
App *create_application() {
    App *app = malloc(sizeof(App));;
    app->name = NULL;
    app->root_path = NULL;
    return app;
}

/**
 *
 */
void free_application(App *app) {
    free(app->name);
    free_hash_map(app->packages);
    free(app);
}


/**
 *
 */
int is_logos_file(const char *path) {
    char *dot = strrchr(path, '.');
    return dot && strcmp(dot + 1, LOGOS_FILE_EXT) == 0;
}

/**
 *
 */
AppFile *create_app_file(const char *name) {
    AppFile *app_file = malloc(sizeof(AppFile));
    app_file->name = name;
    return app_file;
}

/**
 *
 */
Package *create_package(const char *name) {
    Package *pkg = malloc(sizeof(Package));
    pkg->name = name;
    return pkg;
}

/**
 *
 */
void free_package(Package *package) {
    free((char *)package->name);
    free(package);
}
