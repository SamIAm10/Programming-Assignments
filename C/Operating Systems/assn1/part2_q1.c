#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    FILE *file_ptr;
    file_ptr = fopen("500_rand_int.txt", "w+");
	int output = 0; //output integer
	int inv = 1; //used to randomly invert the integer b/w + and -
	srand(time(NULL)); //initialize RNG using time
    for (int i = 0; i < 500; i++) {
		inv = rand() % 2; //set inv to 0 or 1
		if (inv == 0)
			inv = -1;
		output = inv*rand();
		fprintf(file_ptr, "%d\n", output);
    }
	fclose(file_ptr);
	return 0;
}