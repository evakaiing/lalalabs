#include "functions.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    int r = 3;
    int num = -9;
    int size = 0;
    char* ans;

    return_code rc = convert_to_base(num, r, &size, &ans);
    if (rc != OK) {
        return rc;
    }

    for (int i = bit_addition(size, -1); i >= 0; i = bit_addition(i, -1)) {
        printf("%c", ans[i]);
    }

    free(ans);
    return 0;
}
