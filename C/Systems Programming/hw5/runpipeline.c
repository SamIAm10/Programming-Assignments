#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include <errno.h>
#include <assert.h>

#define ERROR_MSG(x)  fprintf(stderr, "%s\n", (x))

#define BUF_SIZE    1024
#define MAX_TASKS   10

typedef struct program_tag {
    char**   args;      // array of pointers to arguments
    int      num_args;  // number of arguments
    int	     pid;	// process ID of this program
    int      fd_in;     // FD for stdin
    int      fd_out;    // FD for stdout
} Program;


/* start a program
 * The informaton about one or more programs is passed in.
 * parameters:
 *      progs:  array of pointers to Program. (should be: array of structures)
 *      total:  the number of valid programs in progs.
 *      cur:    the one that needs to be started.
 *
 *  You need fork and then turn child into the program.
 *  Create pipes or use the pipes already created.
 *  Close pipes that are not used.
 */
void start_program(Program *progs, int total, int cur)
{
    // TODO
  pid_t pid = fork();

  if (pid == 0) {
    char** args = progs[cur].args;
    int fd_in = progs[cur].fd_in;
    int fd_out = progs[cur].fd_out;

    //redirect stdin to this program's input (fd_in is output read from prev program)
    dup2(fd_in, 0);
    //redirect stdout to this program's output (fd_out is input written to next program)
    dup2(fd_out, 1);
    if (fd_in != -1)  //close fd's in use
      close(fd_in);
    if (fd_out != -1)
      close(fd_out);
    execvp(args[0], args); //exec
    exit(0);
  }
  
  if (progs[cur].fd_in != -1) //close any open fd's
    close(progs[cur].fd_in);
  if (progs[cur].fd_out != -1)
    close(progs[cur].fd_out);
  progs[cur].pid = pid; //set pid of program
}

/* Wait on a program.
 */
int wait_on_program(Program *prog)
{
    // TODO
  waitpid(prog->pid, NULL, 0);
  return 0;
}


/* create pipes to be used for communication
 * between processes.
 * you can create all pipes here.
 * Or you can create pipes when they are needed in start_program().
 * If you decided to create pipes in start_program(),
 * Leave this function empty.
 */
void prepare_pipes(Program *prog, int num_programs)
{
    // TODO
  for (int i = 1; i <= num_programs - 1; i++) { //spawn num_programs-1 pipes
    int pipeFD[2];
    pipe(pipeFD); //pipe b/w 2 programs
    prog[i-1].fd_out = pipeFD[1]; //stdout of prev program goes to write end
    prog[i].fd_in = pipeFD[0]; //stdin of cur program goes to read end
  }
}

/* clean up for all programs.
 */
void cleanup_programs(Program *prog, int num_programs)
{
  // TODO
  for (int i = 0; i < num_programs; i++)
    free(prog[i].args);
}


/*********************************************************/
/* Do not change code below                              */
/*********************************************************/
void init_program(Program *prog, int na)
{
    // allocate memory for array of arguments
    prog->args = malloc(na * sizeof(char *));
    assert(prog->args != NULL);
    prog->num_args = 0;

    prog->pid = prog->fd_in = prog->fd_out =  -1;
}

int main(int argc, char **argv)
{
    Program progs[MAX_TASKS];
    int     num_programs;

    if (argc <= 1) {
        ERROR_MSG("Specify at least one program to run. Multiple programs are separated by --");
        exit(-1);
    }

    fprintf(stderr, "Parent started. pid=%d\n", getpid());

    // Prepare programs and their arguments
    num_programs = 0;
    int     cur_arg = 1;
    while (cur_arg < argc) {

        init_program(&progs[num_programs], argc);

        int     ia;
        for (ia = 0; cur_arg < argc; cur_arg ++) {
            if (!strcmp(argv[cur_arg], "--")) {
                if (num_programs == MAX_TASKS -  1) {
                    ERROR_MSG("Too many programs.");
                    exit(-1);
                }
                if (cur_arg + 1 == argc) {
                    ERROR_MSG("The last program is empty.");
                    exit(-1);
                }
                cur_arg ++;
                break;
            }
            progs[num_programs].args[ia++] = argv[cur_arg];
        }
        if (ia == 0) {
            ERROR_MSG("Empty program.");
            exit(-1);
        }
        progs[num_programs].args[ia] = NULL;
        progs[num_programs].num_args = ia;
        num_programs ++;
    }

    // Prepare pipes
    prepare_pipes(progs, num_programs);

    // spawn children
    for (int i = 0; i < num_programs; i ++) {
        start_program(progs, num_programs, i);
    }

    // wait for children
    for (int i = 0; i < num_programs; i ++) {
        fprintf(stderr, "Waiting for child %2d (%5d)...\n", i, progs[i].pid);
        wait_on_program(&progs[i]);
    }

    // cleanup
    cleanup_programs(progs, num_programs);

    fprintf(stderr, "Everything is good.\n");
    return 0;
}
