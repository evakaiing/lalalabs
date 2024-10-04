// TODO: 
// convertation path to absolute
// get path to current file 
// add prefix to output file
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

    if (strlen(path_to_current_directory) + strlen(input_path) > PATH_MAX) {
        return FILE_PATH_LENGTH_ERROR;
    }

    strcpy(result, path_to_current_directory);
    strcat(result, input_path);

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

return_code get_output_filename(char* input_path, char* output_path) {
    int size_of_path_to_file = strlen(input_path);
    if (size_of_path_to_file > PATH_MAX) {
        return FILE_PATH_LENGTH_ERROR;
    }

    char* name_input_file = input_path;
    name_input_file += size_of_path_to_file;
    do {
        --name_input_file;
    } while (*name_input_file != '/');
    strncat(output_path, input_path, name_input_file - input_path + 1);
    strcat(output_path, "out_");
    strcat(output_path, name_input_file + 1);

    return OK;
}