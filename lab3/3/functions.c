#include "functions.h"


return_code input_handling(const char* argv) {
    if (argv[0] != '-' && argv[0] != '/') {
        return INVALID_INPUT;
    } 

    if (argv[1] != 'a' && argv[1] != 'd') {
        return INVALID_INPUT;
    }

    return OK;
}
return_code is_correct_input(Employee employee) {
    int i;
    for (i = 0; i < strlen(employee.name); ++i)
    {
        if (!((employee.name[i] >= 'a' && employee.name[i] <= 'z') || (employee.name[i] >= 'A' && employee.name[i] <= 'Z')))
            return INVALID_INPUT;
    }
    for (i = 0; i < strlen(employee.last_name); ++i) {
        if (!((employee.last_name[i] >= 'a' && employee.last_name[i] <= 'z') || (employee.last_name[i] >= 'A' && employee.last_name[i] <= 'Z')))
            return INVALID_INPUT;
    }

    return OK;
}

return_code upload_info(Employee** result_info, FILE* input_file, int* size) {
    // int capacity = 2;
    // int reading_cnt;
    // Employee* employees;
    // Employee* tmp;
    // *size = 0;

    // employees = (Employee *)malloc(sizeof(Employee) * capacity);
    // if (!employees)
    //     return MEMORY_ALLOCATION_ERROR;

    // while ((reading_cnt = fscanf(input_file, 
    // "%u%s%s%lf\n", &employees[*size].id, employees[*size].name, employees[*size].last_name, &employees[*size].wages)) == 4) {

    //     if (is_correct_input(employees[*size]) != OK) {
    //         free(employees);
    //         return INVALID_INPUT;
    //     }

    //     (*size)++;

    //     if (*size == capacity) {
    //         capacity *= 2;
    //         tmp = (Employee *)realloc(employees, capacity * sizeof(Employee));
    //         if (!tmp)
    //         {
    //             free(employees);
    //             return MEMORY_ALLOCATION_ERROR;
    //         }
    //         employees = tmp;
    //     }
    // }

    // if (reading_cnt < 4 && reading_cnt > 0)
    // {
    //     free(employees);
    //     return INVALID_INPUT;
    // }

    // if (!result_info) {
    //     return DEREFERENCING_NULL_POINTER_ATTEMPT;
    // }

    // *result_info = employees;
    // return OK;

    int capacity = 2, count_read;
    *size = 0;
    if (!result_info)
        return INVALID_INPUT;
    *result_info = NULL;

    Employee *data = (Employee *)malloc(sizeof(Employee) * capacity);
    Employee *for_realloc;
    if (!data)
        return MEMORY_ALLOCATION_ERROR;

    while ((count_read = fscanf(input_file, "%u%s%s%lf\n", &data[*size].id, data[*size].name, data[*size].last_name, &data[*size].wages)) == 4)
    {
        if (is_correct_input(data[(*size)]) != OK)
        {
            free(data);
            return INVALID_INPUT;
        }
        (*size)++;
        if (*size == capacity)
        {
            capacity *= 2;
            for_realloc = (Employee *)realloc(data, capacity * sizeof(Employee));
            if (!for_realloc)
            {
                free(data);
                return MEMORY_ALLOCATION_ERROR;
            }
            data = for_realloc;
        }
    }

    if (count_read < 4 && count_read > 0)
    {
        free(data);
        return INVALID_INPUT;
    }
    *result_info = data;
    return OK;


}

int comp_for_a(const void *a, const void *b) {
    const Employee *emp_a = (const Employee *)a;
    const Employee *emp_b = (const Employee *)b;
    int temp;

    if (emp_a->wages - emp_b->wages > EPS)
    {
        return 1;
    }
    if (emp_b->wages - emp_a->wages > EPS)
    {
        return -1;
    }

    temp = strcmp(emp_a->last_name, emp_b->last_name);

    if (temp)
        return temp;

    temp = strcmp(emp_a->name, emp_b->name);

    if (temp)
        return temp;

    return emp_a->id - emp_b->id;
}

int comp_for_d(const void *a, const void *b) {
    return comp_for_a(a, b) * -1;
}