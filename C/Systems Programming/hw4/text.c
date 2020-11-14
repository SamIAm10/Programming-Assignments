#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(int argc, char ** argv)
{
  char * filename = "matrix.out";

  // Use the file specified if it is present
  if (argc >= 2) {
    filename = argv[1];
  }

  FILE* fp = fopen(filename, "r");
  int x;
  int y;
  int k;
  int z;

  fread(&x, sizeof(x), 1, fp);
  fread(&y, sizeof(y), 1, fp);
  fread(&k, sizeof(k), 1, fp);
  fread(&z, sizeof(z), 1, fp);
  printf("%d %d %d %d\n", x, y, k, z);
}
