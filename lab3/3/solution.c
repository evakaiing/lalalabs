#include "functions.h"

int main(int argc, char* argv[]) {
    char* info = NULL;
    char current_path[PATH_MAX];
    char absolute_path[PATH_MAX];
    FILE* input_file, *output_file;
    int size;
    Employee* employees = NULL;
    char absolute_path_1[BUFSIZ], absolute_path_2[BUFSIZ];

    const char* flag = argv[2];

    if (argc != 4) {
        printf("Invalid inut\n");
        return INVALID_INPUT;
    }

    if (input_handling(flag) != OK) {
        return_code rc = input_handling(flag);
        printf("Error handling\n");
        return rc;
    }

    if (!realpath(argv[1], absolute_path_1) || !realpath(argv[3], absolute_path_2)) {
        printf("Error realpath\n");
        return INVALID_INPUT;
    }

    if (!strcmp(absolute_path_1, absolute_path_2)) {
        return INVALID_INPUT;
    }

    input_file = fopen(argv[1], "r");
    if (!input_file) {
        printf("Couldn't open input file\n");

        return FILE_OPENNING_ERROR;
    }

    output_file = fopen(argv[3], "w");
    if (!output_file) {
        printf("Couldn't open output file\n");
        fclose(input_file);
        return FILE_OPENNING_ERROR;
    }


    upload_info(&employees, input_file, &size);
    
    if (argv[2][1] == 'a') {
        qsort(employees, size, sizeof(Employee), comp_for_a);
    } else {
        qsort(employees, size, sizeof(Employee), comp_for_d);
    }

    for (int i = 0; i < size; i++)
    {
        fprintf(output_file, "%u %s %s %lf\n", employees[i].id, employees[i].name, employees[i].last_name, employees[i].wages);
    }

    free(employees);
    fclose(input_file);
    fclose(output_file);

}