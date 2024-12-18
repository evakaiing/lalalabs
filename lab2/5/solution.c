#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "functions.h"

#include <unistd.h>

int main() {
    printf("Overfprintf:\n");

    overfprintf(stdout, "155 in Roman: %Ro\n", 155);
    overfprintf(stdout, "-1124 in Roman: %Ro\n", -1124);
    overfprintf(stdout, "5023 in Roman > 4000: %Ro\n", 5023);
    printf("\n");

    overfprintf(stdout, "100 in zerkendorf repr: %Zr\n", 100);
    printf("\n");

    overfprintf(stdout, "In 2 base 124: %CV\n", 124, 2);
    overfprintf(stdout, "In 10 base -52: %CV\n", -52, 10);
    overfprintf(stdout, "In small 12 base 124: %Cv\n", 124, 12);
    overfprintf(stdout, "In BIG 12 base 124: %CV\n", 124, 12);
    overfprintf(stdout, "In 2 base 124: %CV\n", 124, 2);
    printf("\n");

    overfprintf(stdout, "a228 in 16 base = %to in 10 base\n", "a228", 16);
    overfprintf(stdout, "A228 in 16 base = %TO in 10 base\n", "A228", 16);
    printf("\n");

    overfprintf(stdout, "Dump of int 1: %mi\n", 1);
    overfprintf(stdout, "Dump of uint INT_MAX + 2: %mu\n", ((unsigned int)INT_MAX + 2));
    overfprintf(stdout, "Dump of double 1.1: %md\n", (double)1.1);
    overfprintf(stdout, "Dump of float  1.2: %mf\n", (float)1.1);
    overfprintf(stdout, "Regular flags %d %s %.15f\n", 15, "hello", 1.23);
    printf("\n");
    
    printf("Oversprintf:\n");
    char a[50]; 
    oversprintf(a , "hello bro", 5);
    printf("%s\n", a);

    oversprintf(a, "Regular flags %d %s %.15f\n", 15, "hello", 1.23);
    printf("%s\n", a);  

    oversprintf(a, "5023 in Roman > 4000: %Ro\n", 5023);
    printf("%s\n", a);  
    
    oversprintf(a, "In 2 base 124: %CV", 124, 2);
    printf("%s\n", a);
    oversprintf(a, "In 10 base -52: %CV", -52, 10);
    printf("%s\n", a);  
    oversprintf(a, "In small 12 base 124: %Cv", 124, 12);
    printf("%s\n", a);  
    oversprintf(a, "In BIG 12 base 124: %CV", 124, 12);
    printf("%s\n", a);  
    oversprintf(a, "In 2 base 124: %CV", 124, 2);
    printf("%s\n", a);  
    
    FILE* file = fopen("result.txt", "w");
    if (!file) {
        printf("nt\n");
        return FILE_OPENNING_ERROR;
    }
    overfprintf(file, "155 in Roman: %Ro\n", 155);
    overfprintf(file, "-1124 in Roman: %Ro\n", -1124);
    overfprintf(file, "5023 in Roman >= 4000: %Ro\n", 5023);

    overfprintf(file, "100 in zerkendorf repr: %Zr\n", 100);

    overfprintf(file, "In 2 base 124: %CV\n", 124, 2);
    overfprintf(file, "In 10 base -52: %CV\n", -52, 10);
    overfprintf(file, "In small 12 base 124: %Cv\n", 124, 12);
    overfprintf(file, "In BIG 12 base 124: %CV\n", 124, 12);
    overfprintf(file, "In 2 base 124: %CV\n", 124, 2);

    overfprintf(file, "a228 in 13 base = %to in 10 base\n", "a228", 13);
    overfprintf(file, "A228 in 13 base = %TO in 10 base\n", "A228", 13);

    overfprintf(file, "Dump of int 1: %mi\n", 1);
    overfprintf(file, "Dump of uint 1: %mu\n", ((unsigned int)INT_MAX));
    overfprintf(file, "Dump of double 1.1: %md\n", (double)1.1);
    overfprintf(file, "Dump of float  1.2: %mf\n", (float)1.1);
    overfprintf(file, "Regular flags %d %s %.15f\n", 15, "hello", 1.23);

    fclose(file);
    return OK;
}
