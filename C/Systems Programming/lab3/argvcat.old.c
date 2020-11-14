#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// return the length of a string
// For example,
// return 0 if s is ""
// return 3 if s is "abc"
unsigned long my_strlen(char *s)
{
    unsigned long    i = 0;

    while (*s ++)
        i ++;
    return i;
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // TODO
}

int main(int argc, char *argv[])
{
    int     i;
    char    *s;

    // initialize s to be ""
    s = malloc(1);
    assert(s != NULL);
    *s = 0;

    for  (i = 0; i < argc; i ++) {
        s = my_strcat(s, argv[i]);
    }

    printf("%s\n", s);

    return 0;
}
