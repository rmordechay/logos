#include <stdlib.h>
#include "project.h"

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
    free(app->root_path);
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
