#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define     TElement    int

typedef struct Matrix {
    unsigned int nrow;
    unsigned int ncol;
    TElement **data;
} TMatrix;


/*
 * Creates and returns a matrix of size rows x cols
 * - rows : (non-negative value) giving the number of rows
 * - cols : (non-negative value) giving the number of columns
 * If the allocation is not successful, the function should return NULL
 * If the allocation is successful, the data field of the matrix should
 * point to an array of pointers (representing the rows) and each pointer
 * in that array should point to an array of TElement representing the values
 * in that row. 
 */
TMatrix * newMatrix(unsigned int nrow, unsigned int ncol) 
{
    // TODO
  TMatrix* m = malloc(sizeof(TMatrix));
  TElement** data = malloc(nrow * sizeof(TElement*));
  for (int i = 0; i < nrow; i++)
    data[i] = malloc(ncol * sizeof(TElement));
  m->nrow = nrow;
  m->ncol = ncol;
  m->data = data;
  return m;
}

/*
 * This function is responsible for deallocating the dynamic memory
 * currently used by a matrix. Check the newMatrix() function to see
 * what were allocated.
 */
void freeMatrix(TMatrix * m) 
{
    // TODO
  unsigned int nrow = m->nrow;
  for (int i = 0; i < nrow; i++)
    free(m->data[i]);
  free(m->data);
  free(m);
  return;
}

/* This function takes as input a filename, and read a matrix from the file.
 * The dimensions of the matrix and data are in the file. See the source code of 
 * the program that generates the matrix file for details.
 * Failure of file operatoins or memory allocations is a fatal error.
 * The function returns a matrix.
 */
TMatrix * readMatrix(char *filename)
{
    // TODO
  FILE* fp = fopen(filename, "r");
  unsigned int nrow, ncol;
  fread(&nrow, sizeof(nrow), 1, fp); //read nrow and ncol
  fread(&ncol, sizeof(ncol), 1, fp);
  TMatrix* m = newMatrix(nrow, ncol);

  for (int i = 0; i < nrow; i++) //read data from file
    fread(m->data[i], sizeof(TElement), ncol, fp);

  fclose(fp);
  return m;
}

/*
 * The transposeMatrix function takes as input a matrix m and returns a
 * new matrix that holds the transpose of m. Transposition should run in 
 * O(nrow x ncol)  (where n is the # of rows and m the # of columns). 
 * If memory allocation for the transpose failed or input is NULL, 
 * the function returns NULL.
 * Transposition follows the usual mathematical definition of transposition. 
 */
TMatrix * transposeMatrix(TMatrix * m) 
{
    // TODO
  if (m == NULL)
    return NULL;

  unsigned int nrow = m->nrow, ncol = m->ncol;
  TMatrix* m_tran = newMatrix(ncol, nrow);
  
  for (int i = 0; i < ncol; i++)
    for (int j = 0; j < nrow; j++)
      m_tran->data[i][j] = m->data[j][i];

  return m_tran;
}

/* Write the matrix to a file named filename.
 * If m is NULL, do nothing.
 * Failure on file operations is fatal.
 */ 
void writeMatrix(TMatrix *m, char *filename)
{
    if (m == NULL)
        return;
    
    // TODO
    FILE* fp = fopen(filename, "w");
    unsigned int nrow = m->nrow, ncol = m->ncol;
    fwrite(&nrow, sizeof(nrow), 1, fp); //write nrow and ncol
    fwrite(&ncol, sizeof(ncol), 1, fp);
    
    for (int i = 0; i < nrow; i++) //write data to file
      fwrite(m->data[i], sizeof(TElement), ncol, fp);

    fclose(fp);
    return;
} 

/************************************************************/
/* Do not change the code below                             */
/************************************************************/

/*
 * May be helpful if you want to see small matrices on screen.
 * Remember to undo the changes.
 *
 * The printMatrix function takes a matrix as input and produces, on the
 * standard output, a representation of the matrix in row-major format. For
 * instance, the 3x3 identity matrix should print on 3 lines as:
 * 1 0 0 
 * 0 1 0
 * 0 0 1
 */
void printMatrix(TMatrix * m) 
{
    if (m == NULL || m->data == NULL)
        return;
    for (unsigned int i = 0; i < m->nrow; i++) {
        for (unsigned int j = 0; j < m->ncol; j++) 
            printf("%10d", m->data[i][j]);
        printf("\n");
    }
}

#define     FN_LEN      128

int main(int argc, char ** argv) 
{
    char * filename = "matrix.out";
    char output_filename[FN_LEN];

    // Use the file specified if it is present
    if (argc >= 2) {
	filename = argv[1];
    }

    // Generate output file name 
    // Using 10 here is actually not a good practice
    if (strlen(filename) > FN_LEN - 10) {
        fprintf(stderr, "File name is too long:%s\n", filename);
        return 1;
    }

    strcpy(output_filename, filename);
    strcat(output_filename, ".out");

    TMatrix *a = readMatrix(filename);
    assert(a != NULL);

    TMatrix *t = transposeMatrix(a);

    writeMatrix(t, output_filename);

    freeMatrix(a);
    freeMatrix(t);

    return 0;
}
