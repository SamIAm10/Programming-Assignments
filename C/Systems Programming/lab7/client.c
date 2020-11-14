#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>

void checkError(int status)
{
  if (status < 0) {
    printf("socket error: [%s]\n",strerror(errno));
    exit(-1);
  }
}

int main(int argc,char* argv[])
{
  int sid = socket(PF_INET,SOCK_STREAM,0);
  struct sockaddr_in srv;
  struct hostent *server = gethostbyname("localhost");
  srv.sin_family = AF_INET;
  srv.sin_port = htons(3100);
  memcpy(&srv.sin_addr.s_addr,server->h_addr,server->h_length);
  int status = connect(sid,(struct sockaddr*)&srv,sizeof(srv));
  checkError(status);
  char buf[32];
  recv(sid, buf, 32, 0);
  printf("%s", buf);
  int done = 0;
  do {
    char opcode[32];
    scanf("%s", opcode);
    if (!strncmp(opcode, "exit", 4)) {
      send(sid, opcode, strlen(opcode), 0);
      recv(sid, opcode, 30, 0);
      printf("%s", opcode);
      done = 1;
    }
    else {
      send(sid, opcode, strlen(opcode), 0);
      recv(sid, opcode, 30, 0);
      printf("%s", opcode);
    }
  } while(!done);
  
  return 0;
}
