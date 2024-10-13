typedef enum return_code {
    OK,
    INVALID_INPUT,
    MEMORY_ALLOCATION_ERROR,
    OVERFLOW_ERROR
} return_code;

return_code calculate_geometric_average(double* result, int count_of_values, ...);
return_code fast_exponentiation(double num_to_exponentation, int degree, double* result);
int there_is_overflow(double num);