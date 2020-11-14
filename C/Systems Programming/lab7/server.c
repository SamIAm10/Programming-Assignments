#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <dirent.h>
#include <time.h>

void checkError(int status)
{
  if (status < 0) {
    printf("socket error: [%s]\n",strerror(errno));
    exit(-1);
  }
}

int main(int argc,char* argv[])
{
  int sid = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(3100);
  addr.sin_addr.s_addr = INADDR_ANY;
  //pairs the newly created socket with the requested address.
  int status = bind(sid,(struct sockaddr*)&addr,sizeof(addr));
  checkError(status);
  // listen on that socket for "Let's talk" message.
  status = listen(sid,10);
  checkError(status);

  while(1) {
    struct sockaddr_in client;
    socklen_t clientSize;
    int chatSocket = accept(sid,(struct sockaddr*)&client,&clientSize);
    checkError(chatSocket);
    printf("We accepted a socket: %d\n",chatSocket);
    pid_t child = fork();
    if (child == 0) {
      close(sid);
      int sum = 0;
      char buffer[35];
      int len = sprintf(buffer, "%d\n", sum);
      status = send(chatSocket, buffer, sizeof(buffer), 0); checkError(status);
      
      while(1) {
	char buffer[35];
	//repeat read numbers recv
	//if (string == "exit") {
	//write sum to client
	//exit 
	int len = recv(chatSocket, buffer, 35, 0); checkError(status);
	if (!strncmp(buffer, "exit", 4)) {
          char bye[4+31] = "Bye ";
          char sumstring[31];
          sprintf(sumstring, "%d\n", sum);
          strcat(bye, sumstring);
          status = send(chatSocket, bye, strlen(bye), 0); checkError(status);
          close(chatSocket);
          return -1;
        }
	int client_input;
        int input_status = sscanf(buffer, "%d", &client_input);
	if (len > 30) {
	  char errlong[16+31] = "Error LongLine ";
          char sumstring[31];
          sprintf(sumstring, "%d\n", sum);
          strcat(errlong, sumstring);
          send(chatSocket, errlong, strlen(errlong), 0);
	  continue;
	}
	else if (input_status <= 0 && len <= 30) {
	  char errnan[11+31] = "Error NaN ";
          char sumstring[31];
          sprintf(sumstring, "%d\n", sum);
          strcat(errnan, sumstring);
          send(chatSocket, errnan, strlen(errnan), 0);
	  continue;
	}
	else {
	  sum += client_input;
	  char sumstring[31];
          sprintf(sumstring, "%d\n", sum);
	  send(chatSocket, sumstring, strlen(sumstring), 0);
	  continue;
	}
      }
      close(chatSocket);
      return -1;
    }
    else if (child > 0) {
      printf("Created a child: %d\n",child);
      close(chatSocket);
      int status = 0;
      pid_t deadChild; // reap the dead children (as long as we find some)
      do {
	deadChild = waitpid(0,&status,WNOHANG);checkError(deadChild);
	if (deadChild > 0)
	  printf("Reaped %d\n",deadChild);
      } while (deadChild > 0);
    }
  }
  return 0;
}

