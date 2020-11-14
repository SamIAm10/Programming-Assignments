#define    _POSIX_C_SOURCE  1

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    // change 'vi' to your favorite editor
    char    *cmd = "emacs";
    char    *filename = "a.txt";

    if (argc >= 2)
        filename = argv[1];

    // TODO
    pid_t pid = fork();
    if (pid == 0) {
      execlp(cmd, filename);
      exit(0);
    }
    else {
      int x = 0;
      waitpid(pid, &x, 0);
      printf("pid=%d exited=%d exitstatus=%d\n", pid, WIFEXITED(x), WEXITSTATUS(x));
      
      FILE* fp = fopen(filename, "r");
      char *line = malloc(sizeof(char) * 1000);
      while (fgets(line, 1000, fp)) {
	if (line[0] == '#')
	  printf("%s", line);
      }
      free(line);
      fclose(fp);
    } 
    return 0;
}
