#include "realization.c"
#include <ctype.h> 

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return INVALID_INPUT;
    }

    char command[BUFSIZ];
    IntArray arrays[MAX_ARRAYS];
    FILE* file = NULL;
    if ((file = fopen(argv[1], "r")) == NULL) {
        perror("Error opening file");
        return FILE_OPENNING_ERROR;
    }

    init_arrays(arrays);
    while (fgets(command, BUFSIZ, file)) {
        command[strcspn(command, "\r\n")] = 0; 
        execute_command(arrays, command);    
    }

    fclose(file); 
    return 0;
}

