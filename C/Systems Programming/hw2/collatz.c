#include <stdio.h>
#include <assert.h>

// add any functions you need here
int collatz_steps(unsigned int x)
{
  int counter = 0;
  while (x != 1)
    {
      if (x % 2 == 0)
	x /= 2;
      else
	x = 3*x + 1;
      counter++;
    }
  return counter;
}

int main()
{
    int a, b, x, max_steps = 0;
    // you can use additional variables if needed

    printf( "Enter a and b: ");
    assert( scanf("%d %d", &a, &b)==2 && a<=b);

    // add code to find x between a and b that needs
    // largest number of Collatz steps to reach 1
    for (int c = a; c <= b; c++)
      {
        int steps = collatz_steps(c);
        if (steps > max_steps)
	  {
            max_steps = steps;
            x = c;
	  }
      }

    printf( "Longest Collatz chain starts at %d and takes %d steps\n", x, max_steps );
    return 0;
}
