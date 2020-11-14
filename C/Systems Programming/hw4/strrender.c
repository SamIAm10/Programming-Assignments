#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define     NUM_CHAR_PER_LINE       8
#define     FONT_WIDTH              8
#define     FONT_HEIGHT             8
#define     FONT_NBYTES_PER_ROW     1
#define     FONT_NBYTES_PER_CHAR    (FONT_NBYTES_PER_ROW * FONT_HEIGHT)
#define     PIXEL_FONT              '*'
#define     PIXEL_BACKGROUND        ' '

/* buf is the display buffer.
 * s is the string to be displayed on this 'line'.
 * fp points to the opened font file.
 *
 * The function retrieves font information for up to NUM_CHAR_PER_LINE characters
 * in s from fp, and updates the display buffer (buf). 
 *
 * The function returns the number of bytes that have been processed. 
 * Should be a number between 0 and NUM_CHAR_PER_LINE.
 * */
unsigned int str_render (char **buf, char *s, FILE *fp)
{
    unsigned int n = 0;
    // TODO
    for (int i = 0; i < NUM_CHAR_PER_LINE; i++) {
      int ascii = s[i];
      fseek(fp, ascii*8, SEEK_SET);
      for (int h = 0; h < FONT_HEIGHT; h++) {
	char val = fgetc(fp);
	buf[i][h] = val;
      }
      n++;
    }
    return n;
}

/* Clear the display buffer. 
 * If print_buffer() is called right after, only PIXEL_BACKGROUND will be displayed.
 * Try to type 'clear' in your bash.
 * */
void    clear_buffer(char **buf)
{
  // TODO
  for (int i = 0; i < NUM_CHAR_PER_LINE; i++)
    for (int h = 0; h < FONT_HEIGHT; h++)
      buf[i][h] = PIXEL_BACKGROUND;
}

/* shown the display buffer on the screen. */
void print_buffer(char ** buf)
{
    // TODO
  for (int h = 0; h < FONT_HEIGHT; h++) {
    for (int i = 0; i < NUM_CHAR_PER_LINE; i++) {
      int val = buf[i][h];

      int bits = 8; //convert val to 8 bit string
      char* binstring = malloc(bits * sizeof(char));
      unsigned int m = 1 << (bits - 1);
      for (int j = 0; j < bits; j++) {
	binstring[j] = ((val & m) != 0) + '0';
	m = m >> 1;
      } //end conversion

      char* binrev = malloc(bits * sizeof(char)); //reverse the binary string
      for(int k = 0; k < bits; k++)
	binrev[k] = binstring[bits - 1 - k]; //end reverse
      
      for (int l = 0; l < bits; l++) { // print '*' and ' '
	if (binrev[l] == '0')
	  printf("%c", PIXEL_BACKGROUND);
	else
	  printf("%c", PIXEL_FONT);
      }

      free(binstring); // free arrays
      free(binrev);
    }  

    printf("\n");
  }
}

int main(int argc, char **argv)
{

    char * font_filename = "font8x8.dat";

    if (argc != 2) {
	fprintf(stderr, "Usage: %s <a string>\n", argv[0]);
	return 1;
    }

    // open the font file

    FILE *fp;

    fp = fopen(font_filename, "r");
    if (fp == NULL) {
	fprintf(stderr, "Cannot open font file %s :", font_filename);
        perror("");
        fprintf(stderr, "Run ./generate-fontfile to create it. Do not add it to your repo.\n"); 
	return 2;
    }

    /* There are many ways to do it. 
     * 
     * One strategy can be:
     *
     *      1. Allocate a 'display' buffer, a 2-D array that has FONT_HEIGHT rows.
     *      2. Clear buffer.
     *      3. Call str_render() to render NUM_CHAR_PER_LINE characters into the display buffer.
     *      4. Print the buffer.
     *      5. If there are more characters to display, goto 2.
     *      6. Free buffer.
     * 
     * There are several ways to use buffer. Be consistent in your implementation. 
     */

    //TODO
    char* s = argv[1];
    int len = strlen(s);

    for (int i = 0; i < len; i += 8){
      char* s8 = malloc(NUM_CHAR_PER_LINE * sizeof(char));
      strncpy(s8, s, NUM_CHAR_PER_LINE);
      char** buf = malloc(NUM_CHAR_PER_LINE * sizeof(char*));
      for (int j = 0; j < NUM_CHAR_PER_LINE; j++)
        buf[j] = malloc(FONT_HEIGHT * sizeof(char));
      clear_buffer(buf);
      str_render(buf, s8, fp);
      print_buffer(buf);
      s += 8;

      for (int k = 0; k < NUM_CHAR_PER_LINE; k++)
        free(buf[k]);
      free(buf);
      free(s8);
    }

    fclose(fp);
    return 0;
}
