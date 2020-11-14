#include <stdio.h>

void print_result(int n1, int n2, int n3, int result)
// function to print values
{
  printf("%d ** %d mod %d = %d\n", n1, n2, n3, result);
}

int main()
{
  long n, e, m; // initialize long ints
  printf("Please enter n, e, and m: "); // print starting string
  scanf("%ld %ld %ld", &n, &e, &m); // read ints from user input
  int n1 = n, n2 = e, n3 = m; // save inputs
  int result = 1; // begin formula
  while (e > 0) {
    if (e % 2 != 0) result = (result * n) % m;
    e = e / 2;
    n = (n * n) % m;     
  };

  // call function to print values
  print_result(n1, n2, n3, result);

  // end of main function
  return 0;
}
