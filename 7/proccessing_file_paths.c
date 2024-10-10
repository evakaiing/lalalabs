
#include "functions.h"
#include <string.h>
#include <limits.h> 
#include <unistd.h> 


int is_absolute_path(char* path) {
    #if defined _WIN32 || defined _WIN64
        return (strlen(path) > 2 && path[1] == ':' && path[2] == '\\');
    #else 
        return (path[0] == '/');
    #endif
}
return_code convert_path_to_absolute(char* path_to_current_directory, char* input_path, char* result) {
    if (is_absolute_path(input_path)) {
        strcpy(result, input_path);
        return OK;
    }
    int len_of_filename = 0;
    char *p_input_path = input_path + strlen(input_path) - 1;

    while (p_input_path != input_path && *p_input_path != '/') {
        --p_input_path;
        ++len_of_filename;
    }

    if (*p_input_path == '/') {
        ++p_input_path;
    }

    strcpy(result, path_to_current_directory);

    if (result[strlen(result) - 1] != '/') {
        strcat(result, "/");
    }

    strcat(result, p_input_path);

    return OK;
}


return_code get_path_to_current_directory(char* path_for_current_directory) {
    getcwd(path_for_current_directory, PATH_MAX);
    if (!path_for_current_directory) {
        return FILE_PATH_LENGTH_ERROR;
    }

    size_t len = strlen(path_for_current_directory);
    if (len > 0 && path_for_current_directory[len - 1] != '/') {
        strcat(path_for_current_directory, "/");
    }

    return OK;
}

