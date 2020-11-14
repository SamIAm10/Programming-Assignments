#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *file_ptr;
    file_ptr = fopen("500_rand_int.txt", "r");
    int integer = 0;
    int max = 0;
    int min = 0;
    while (feof(file_ptr) == 0) {
        fscanf(file_ptr, "%d", &integer);
        if (integer > max)
            max = integer;
        if (integer < min)
            min = integer;
    }
    fclose(file_ptr);
    printf("Max int: %d\n", max);
    printf("Min int: %d\n", min);
	return 0;
}

