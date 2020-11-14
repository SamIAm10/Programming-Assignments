#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Polynomial ADT. This data type uses two structures
 * Monomial: is used to represent a term  c * x^p
 *           where c is the coefficient and p is the exponent.
 * Polynomial: is used to capture an entire polynomial as a linked list
 *             of monomials, in decreasing exponent order.
 * Note that the representation is sparse and monomials with a coefficient
 * of zero should not be in the list. For instance, the polynomial
 * 7 x^10 - 4 x^3 - 2 x would be represented by the list of three monomials
 * [(7,10), (-4,3), (-2,1)]
 */

typedef struct Monomial {
    int coeff;     /* coefficient */
    int exp;       /* exponent    */
    struct Monomial *next;  /* next monomial */
} Mono;

typedef struct Polynomial {
    Mono* first;   /* first monomial */
    Mono* last;    /* last monomial  */
} Poly;

/*
 * This function creates a monomial with a given coefficient and exponent.
 * c : the coefficient
 * k : the exponent
 * return value : a pointer to the newly created monomial
 */
Mono* newMono(int c, int k)
{
    // TODO
  Mono* m = malloc(sizeof(Mono));
  m->coeff = c;
  m->exp = k;
  m->next = NULL;
  return m;
}

/*
 * This function creates and returns a new polynomial with no monomials.
 */
Poly* newPoly()
{
    // TODO
  Poly* p = malloc(sizeof(Mono));
  p->first = NULL;
  p->last = NULL;
  return p;
}

/*
 * This function deallocates a polynomial.
 * p : pointer to the polynomial to deallocate
 * Requirements:
 *  - the function deallocates not only the polynomial but also all the
 *    monomials comprising it
 */
void freePoly(Poly* p)
{
    // TODO
  if (p == NULL)
    return;
  Mono* first = p->first;
  while (first != NULL) {
    Mono* ptr = first->next;
    free(first);
    first = ptr;
  }
  free(p);
  return;
}

/*
 * This function adds a monomial to an existing polynomial
 * p : pointer to the polynomial to modify
 * m : pointer to the monomial to add
 * Requirements:
 * - the monomial should be added at the end of the monomial list
 */
void appendMono(Poly* p, Mono* m)
{
    // TODO
  if (m->coeff != 0) {
    if (p->last == NULL) {
      p->first = m;
      p->last = m;
      m->next = NULL;
    }
    else {
      p->last->next = m;
      m->next = NULL;
      p->last = m;
    }
  }
  return;
}

/*
 * This function builds the linked list representation of a
 * polynomial read from the standard input. It reads the
 * monomials as (coefficient,exponent) pairs of (whitespace separated)
 * integers as described in the assignment document
 * and constructs the linked list representation.
 * return value : pointer to the constructed polynomial
 * Assumptions:
 * - input monomials are given in decreasing exponent order
 * - the monomial with exponent 0 is always present as the last
 *   monomial of the input (even when the coefficient is 0)
 * Requirements:
 * - only monomials with non-zero coefficients get added to the list
 * - the constructed list has monomials in decreasing exponent order
 */
Poly* readPoly()
{
    // TODO
  int* arr = malloc(2 * sizeof(int));
  scanf("%d %d", &arr[0], &arr[1]);
  int i = 1;
  while (arr[i] != 0) {
    arr = realloc(arr, (i + 3) * sizeof(int));
    scanf("%d %d", &arr[i + 1], &arr[i + 2]);
    i += 2;
  }

  Poly* p = newPoly();
  for (int j = 0; j <= i; j += 2) {
    if (arr[j] != 0) {
      Mono* m = newMono(arr[j], arr[j + 1]);
      appendMono(p, m);
    }
  }

  free(arr);
  return p;
}

/*
 * This function computes the derivative of a given polynomial.
 * p  : pointer to the polynomial to be differentiated
 * returned value : pointer to a new polynomial filled with the monomials of the derivative
 * Assumptions:
 * - the given polynomial has only monomials with non-zero coefficients
 * - the given polynomial has the monomials linked in decreasing exponent order
 * Requirements:
 * - the given polynomial remains unchanged
 * - the result polynomial has only monomials with non-zero coefficients
 * - the result polynomial has the monomials linked in decreasing exponent order
 */
Poly* polyDer(Poly* p)
{
    // TODO
  Mono* first = p->first;
  Poly* pder = newPoly();
  while (first != NULL) {
    int c = first->coeff;
    int e = first->exp;
    if (e - 1 >= 0 && c*e != 0) {
      Mono* m = newMono(c*e, e - 1);
      appendMono(pder, m);
    }
    first = first->next;
  }

  return pder;
}

/*
 * This function computes a new polynomial that represent the difference
 * between two given polynomials.
 * p1  : pointer to first polynomial
 * p2  : pointer to second polynomial
 * returned value : pointer to a new polynomial filled with the monomials of the difference
 * Assumptions:
 * - the given polynomials have only monomials with non-zero coefficients
 * - the given polynomials have the monomials linked in decreasing exponent order
 * Requirements:
 * - the given polynomials remain unchanged
 * - the result polynomial has only monomials with non-zero coefficients
 * - the result polynomial has the monomials linked in decreasing exponent order
 * Notes:
 * - the result polynomial cannot include multiple monomials with the same exponent
 */
Poly* polyDiff(Poly* p1, Poly* p2)
{
    // TODO
  Mono* first1 = p1->first;
  Mono* first2 = p2->first;
  Poly* pdiff = newPoly();

  while(first1 != NULL && first2 != NULL) {
    int c1 = first1->coeff, c2 = first2->coeff, e1 = first1->exp, e2 = first2->exp;
    if (e1 > e2) {
      Mono* m = newMono(c1, e1);
      appendMono(pdiff, m);
      first1 = first1->next;
    }
    else if (e1 < e2) {
      Mono* m = newMono(0 - c2, e2);
      appendMono(pdiff, m);
      first2 = first2->next;
    }
    else {
      if (c1 - c2 == 0) {
	first1 = first1->next;
	first2 = first2->next;
      }
      else {
	Mono* m = newMono(c1 - c2, e1);
	appendMono(pdiff, m);
	first1 = first1->next;
	first2 = first2->next;
      }
    }
  }

  while (first1 != NULL || first2 != NULL) {
    if (first1 != NULL) {
      Mono* m = newMono(first1->coeff, first1->exp);
      appendMono(pdiff, m);
      first1 = first1->next;
    }
    if (first2 != NULL) {
      Mono* m = newMono(-1 * (first2->coeff), first2->exp);
      appendMono(pdiff, m);
      first2 = first2->next;
    }
  }
  
  return pdiff;
}

/*
 * This function prints the received polynomial to the standard output.
 * p  : pointer to the polynomial to print
 * DO NOT CHANGE THIS FUNCTION
 */
void printPoly(const char* msg, Poly* p)
{
    printf("%s\t", msg);
    if( !p || !p->first ) {
        printf( "empty polynomial\n" );
        return;
    } else {
        Mono* m = p->first;
        while( m != NULL ) {
            int c = m->coeff;
            int k = m->exp;
	    assert( m->coeff != 0 );
            if( m != p->first && c > 0 )  printf( " + " );
            if( c < 0 )  printf( " - " );
            if( c*c != 1 || k == 0 )
                printf( "%d ", (c > 0 ? c : -c) );
            if( k > 0 )  printf( "x" );
            if( k > 1 )  printf( "^%d", k );
            m = m->next;
        }
        /* end with newline character */
        printf( "\n" );
    }
    return;
}

/* Only add necessary clean up statements at the end  */
int main()
{
    printf( "Enter polynomial: " );
    Poly* p = readPoly();

    if( p ) printPoly( "P(x):", p );
    else printf( "Could not read P(x)\n" );

    Poly* deriv = polyDer( p );
    if( deriv ) printPoly( "P'(x):", deriv );
    else printf( "Could not compute P'(x)\n" );

    Poly* diff1 = polyDiff( p, deriv );
    if( diff1 ) printPoly( "P(x) - P'(x):", diff1 );
    else printf( "Could not compute P(x) - P'(x)\n" );

    Poly* diff2 = polyDiff(deriv,p);
    if( diff2 ) printPoly( "P'(x) - P(x):", diff2 );
    else printf( "Could not compute P'(x) - P(x)\n" );

    Poly* diff3 = polyDiff( p, p );
    if( diff3 ) printPoly( "P(x) - P(x):", diff3 );
    else printf("Could not compute P(x) - P(x)\n");

    freePoly(p);
    freePoly(deriv);
    freePoly(diff1);
    freePoly(diff2);
    freePoly(diff3);

    return 0;
}
