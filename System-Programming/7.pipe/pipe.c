#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[]){

  int pipefd[2];
  pid_t pid;
  ssize_t len=0;
  size_t buflen = 0;
  char* buf = NULL;
  pipe_msg msg;

  if(pipe(pipefd)<0){
    printf("Cannot create pipe\n");
    exit(EXIT_FAILURE);
    }

  pid = fork();
  if(pid<0){
    printf("Cannot fork\n");
    exit(EXIT_FAILURE);
  }

}
