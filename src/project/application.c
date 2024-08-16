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
    app->app_config = create_app_config();
    return app;
}

/**
 *
 */
void free_application(App *app) {
    free(app->name);
//    free_app_config(app->app_config);
    free(app);
}

/**
 *
 */
AppConfig *create_app_config() {
    return NULL;
}

/**
 *
 */
void free_app_config(AppConfig *app_config) {
    free(app_config->path);
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
