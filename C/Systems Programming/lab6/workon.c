#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#define     BUF_LEN     1024


int main(int argc, char ** argv)
{
    // change 'vim' to another editor if you like
    //char    * cmd_editor = "vim";
    // char    * cmd_editor = "nano";
    char    * cmd_editor = "emacs";
    char    * cmd_make = "make";
    char    * cmd_find_error = "./find-error.py";
    char    * fn_make = "make.out";   // output of make
    int     pFD[2];    // pipe FDs

    // Do not specify a line number initially
    int     linenumber = -1;

    // buffers
    char    fn_c[BUF_LEN];
    char    make_target[BUF_LEN];
    char    opt_linenumber[BUF_LEN];

    if (argc >= 2) {
        int len = strlen(argv[1]);
        if (len > BUF_LEN - 10) {
            fprintf(stderr, "file name or make target is too long.\n");
        }
        if (len > 2 && argv[1][len-1] == 'c' && argv[1][len-2] == '.') {
            strcpy(fn_c, argv[1]);
            strcpy(make_target, argv[1]);
            make_target[len-2] = 0;
        }
        else {
            strcpy(make_target, argv[1]);
            strcpy(fn_c, argv[1]);
            strcat(fn_c, ".c");
        }
    }
    else {
        strcpy(fn_c, "bugs.c");
        strcpy(make_target, "bugs");
    }

    // If you'd like to prepare more before getting into the loop,
    // do it here.
    // TODO

    int     done = 0;

    do {
        // invoke editor
      pid_t pid = fork();
      if (pid == 0) {
	if (linenumber > 0) {
	  char num[12];
	  sprintf(num, "+%d", linenumber);
	  execlp(cmd_editor, cmd_editor, num, fn_c, (char*)NULL);
	  exit(0);
	}
	else {
	  execlp(cmd_editor, cmd_editor, fn_c, (char*)NULL);
	  exit(0);
	}
      }
      else
	waitpid(pid, NULL, 0);

        // invoke make
      pid_t pid2 = fork();
      if (pid2 == 0) {
	int makeFD = open(fn_make, O_WRONLY|O_TRUNC|O_CREAT, 0600);
	dup2(makeFD, 1);
	dup2(makeFD, 2);
	close(makeFD);
	execlp(cmd_make, cmd_make, make_target, (char*)NULL);
	exit(0);
      }
      else
	waitpid(pid2, NULL, 0);
      
        // invoke ./find-error.py to find first error/warning
      pipe(pFD);
      pid_t pid3 = fork();
      if (pid3 == 0) {
	int makeFD = open(fn_make, O_RDONLY);
	dup2(makeFD, 0);
	close(makeFD);
	dup2(pFD[1], 1);
	dup2(pFD[1], 2);
	close(pFD[0]);
	close(pFD[1]);
	execlp(cmd_find_error, cmd_find_error, (char*)NULL);
	exit(0);
      }
      else
	waitpid(pid3, NULL, 0);       

        // read the linenumber that has error/warning
      memset(opt_linenumber, 0, BUF_LEN); //avoid valgrind errors
      read(pFD[0], opt_linenumber, 1000);
      if (opt_linenumber[0] == '\n') {
	printf("No error or warning found.\n");
      }
      else {
	printf("%s", opt_linenumber);
	char* p = strchr(opt_linenumber, ':');
	int i = p - opt_linenumber + 1; //index of first digit of line number
	char ln[10];
	memset(ln, 0, 10); //avoid valgrind errors
	int j = 0;
	while (isdigit(opt_linenumber[i])) {
	  ln[j] = opt_linenumber[i];
	  i++; j++;
	}
	linenumber = strtol(ln, (char**)NULL, 10);
      }
      close(pFD[1]);
      
        // TODO

        // ask if the user wants to continue
        char answer;
        printf("Would you like to continue?(y/n)\n");
        answer = getchar();
        if (answer == EOF || (answer != '\n'  && tolower(answer) != 'y'))
            done = 1;
        else {
            // skip to the end of the line
            while (answer != EOF && answer != '\n')
                answer = getchar();
        }
    } while (! done);

    // If you'd like to clean up after the loop,
    // do it here.
    // TODO

    return 0;
}
