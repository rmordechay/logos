#ifndef MYLANG_PROJECT_H
#define MYLANG_PROJECT_H

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
    char *root_path;
    AppConfig *app_config;
} App;

/**
 *
 */
typedef struct AppFile {
    char *name;
    char *full_path;
    char *parent_path;
    const char *code;
} AppFile;


void init_project();

App *create_application();
AppConfig *create_app_config();
AppFile *create_app_file();

void free_application(App *app);
void free_app_file(AppFile *app_file);
void free_app_config(AppConfig *app_config);

#endif //MYLANG_PROJECT_H
