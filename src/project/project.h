#ifndef PROJECT_H
#define PROJECT_H

#include <stdio.h>

/**
 *
 */
typedef struct AppConfig {
    char *path;
} AppConfig;

/**
 *
 */
typedef struct Application {
    char *name;
    const char *root_path;
    AppConfig *app_config;
} App;

/**
 *
 */
typedef struct AppFile {
    const char *name;
    char *path;
    char *parent_path;
    const char *code;
} AppFile;


void init_project();
int is_logos_file(const char *path);

App *create_application();
AppConfig *create_app_config();
AppFile *create_app_file(const char *name);

void free_application(App *app);
void free_app_file(AppFile *app_file);
void free_app_config(AppConfig *app_config);

#endif //PROJECT_H
