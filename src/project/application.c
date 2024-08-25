#include <stdlib.h>
#include <string.h>
#include "project.h"

/**
 *
 */
App *create_application(const char *name, const char *root_path) {
    App *app = malloc(sizeof(App));
    app->name = name;
    app->root_path = root_path;
    app->packages = create_hash_map();
    return app;
}

/**
 *
 */
void free_application(App *app) {
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
Package *create_package(const char *name, const char *path) {
    Package *pkg = malloc(sizeof(Package));
    pkg->name = name;
    pkg->path = path;
    pkg->packages = create_hash_map();
    pkg->files = create_hash_map();
    return pkg;
}

/**
 *
 */
void free_package(Package *package) {
    free(package);
}

/**
 *
 */
void free_file(AppFile *file) {
    free(file);
}
