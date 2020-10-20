#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  int status;
  pid_t pid;

  printf("Hello\n");
  if((pid = fork())<0){
    perror("fork error");
    return pid;
  }
  printf("%d\n", !pid);
  if(pid!=0){
    if(waitpid(-1, &status, 0)){
        if(WIFEXITED(status)!=0){
          printf("%d\n", WEXITSTATUS(status));
        }
    }
  }
  printf("Bye\n");
  exit(2);
  }

