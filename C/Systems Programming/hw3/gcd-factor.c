#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define     MAX_INPUT       2000000000u


unsigned int * factor_integer (unsigned int n, unsigned int *nf_a)
{
    unsigned int *pf = NULL;
    unsigned int nf = 0;

    // TODO
    if (n < 2)
      return NULL;

    //first check if n is prime. if not, break this loop
    for (unsigned int i = 2; i <= 44722; i++) { //sqrt(2000000000) ~ 44722
      if (n % i == 0)
	break;
      else if (i == 44722) {
	nf++;
        pf = realloc(pf, nf * sizeof(unsigned int));
        pf[nf - 1] = n;
	*nf_a = nf;
	return pf;
      }
      else
	continue;
    }

    for (unsigned int i = 2; i <= n; i++)
      while (n % i == 0) {
	nf++;
	pf = realloc(pf, nf * sizeof(unsigned int));
	pf[nf - 1] = i;
	n /= i;
      }

    *nf_a = nf;
    return pf;
}

/* Find gcd of two integers
 * Return a pointer to gcd.
 * Note that gcd can be 1 if a and b are coprime or one of them is 1.
 *
 * Return NULL if pf1 or pf2 is NULL.
 */
unsigned int * find_gcd (
        unsigned int *pf1, unsigned int nf1,
        unsigned int *pf2, unsigned int nf2,
        unsigned int *nf)
{
    unsigned int *pf3 = NULL, nf3 = 0;
    
    // TODO
    if (pf1 == NULL || pf2 == NULL)
      return NULL;
    
    unsigned int i = 0, j = 0;
    while (i < nf1 && j < nf2) {
      if (pf1[i] < pf2[j])
	i++;
      else if (pf1[i] > pf2[j])
	j++;
      else {
	nf3++;
	pf3 = realloc(pf3, nf3 * sizeof(unsigned int));
        pf3[nf3 - 1] = pf1[i];
        i++;
	j++;
      }
    }

    *nf = nf3;
    return pf3;
}

/*==============================================*/
/* print an integer                             */
/* Do not change this function                  */
/*==============================================*/
void print_integer(unsigned int * pf, unsigned int nf)
{
    unsigned int i;

    if (pf == NULL) {
        printf("1");
        return;
    }

    for (i = 0; i < nf; i ++) {
        printf("%s%u", (i ? " * " : ""), pf[i]);
    }
}

/*==============================================*/
/* Do not change this function                  */
/*==============================================*/
unsigned int get_product(unsigned int *pf, unsigned int nf)
{
    unsigned int i, result = 1;

    if (pf == NULL)
        return result;

    for (i = 0; i < nf; i ++) {
        result *= pf[i];
    }
    return result;
}

/* only add clean up statements at the end. */
int main(int argc, char **argv)
{
    long n1, n2;

    if (argc == 3) {
        n1 = atol(argv[1]);
        n2 = atol(argv[2]);
    }
    else {
	printf("Usage: %s PositiveInteger1 PositiveInteger2\n", argv[0]);
	return -1;
    }

    if (n1 <= 1 || n2 <= 1 || n1 > MAX_INPUT || n2 > MAX_INPUT) {
        printf("Both integers must be > 1 and <= %d.\n", MAX_INPUT);
        return -2;
    }

    unsigned int * pf1, nf1;
    unsigned int * pf2, nf2;
    unsigned int * pf3, nf3;

    pf1 = factor_integer(n1, &nf1);
    pf2 = factor_integer(n2, &nf2);
    pf3 = find_gcd(pf1, nf1, pf2, nf2, &nf3);

    printf("%ld=", n1);
    print_integer(pf1, nf1);
    printf("\n%ld=", n2);
    print_integer(pf2, nf2);
    printf("\ngcd(%ld,%ld)=", n1, n2);
    print_integer(pf3, nf3);
    printf("=%u\n", get_product(pf3, nf3));

    // clean up
    // TODO
    free(pf1);
    free(pf2);
    free(pf3);

    return 0;
}
