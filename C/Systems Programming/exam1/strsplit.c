#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* str_split
 * Input:
 *  s:  String to be split into fields. Cannot be NULL.
 *  delim: delmiter, e.g., ',' and '\t'
 * Return:
 *  An array of pointers to fields, 
 *  with a NULL as the last element to indicate the end of pointers 
 */    
char ** str_split(const char * s, char delim)
{
    // pointers to fields and number of fields
    char ** pf = NULL;
    size_t nf = 0;

    // TODO

    return pf;
}


/* Do NOT change the code below */
// free memory used by fields and pointers to fields.
void free_fields(char ** p) 
{
    char **q = p;

    if (p == NULL)
        return;
    while (*p)
        free(*p++);
    free(q);
}

// print all fields
void print_fields(char ** p) 
{
    size_t i;

    if (p == NULL)
        return;

    for (i = 0; p[i]; i++)
        printf("%2lu:\"%s\"\n", i, p[i]);
}

int main(int argc, char **argv)
{
    char * strs[] = {
        "Sun,Mon,Tue,Wed,Thu,Fri,Sat",
        "***2 4 fields ending with an empty one, 2, 3 ,", 
        "***3 5 fields,second,next field is empty,,next line is empty", 
        "",
        ",a,bb,ccc,dddd,",
        "***every other,,2,,4,,5,,This is a long field. Everything is working!!",
        NULL, // two NULLs.
        NULL
    };
    char **ps;

    // if argv[1] is avalable, append it to the end of existing test strings.
    if (argc >= 2) {
        ps = strs;
        while (*ps) ps++;
        *ps = argv[1];
    }

    for (ps = strs; *ps; ps ++) {
        char ** fields;

        printf("%s\n", *ps);
        fields = str_split(*ps, ',');

        print_fields(fields);
        free_fields(fields);
    }
    return 0;
}
