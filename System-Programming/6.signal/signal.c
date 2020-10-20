#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

volatile int counter = 0;

void handler(int signum){
  int child_status;
  pid_t wpid;
  
  //wait for all kids to be dead
  while((wpid = waitpid(-1, &child_status, WNOHANG))>0){

    if(WIFEXITED(child_status))
      printf("child %d terminate exit status %d\n", wpid, WEXITSTATUS(child_status));
    else
      printf("child %d terminate abnormally\n", wpid);

    counter++;

  }
}
int main(int argc, char* argv[]){

  int N;
  if(argc>1) N = atoi(argv[1]);
  else N = 2;

  pid_t pid[N];

  if(signal(SIGCHLD, handler)==SIG_ERR){
    return EXIT_FAILURE;
  }

  printf("Creating %d child\n", N);
  for (int i=0; i< N; i++){
    if((pid[i]=fork())==0){
      sleep(i/2);
      printf("finishing sleeping!\n");
      return 100+i;
    }
  }


  for (int i=0; i< N; i+=2){
    printf("killing process %d\n", pid[i]);
    kill(pid[i], SIGINT);

  }

  printf("Waiting until all %d childeren have terminated \n", N);
  while(counter<N){
    sleep(1);
    printf("-->%d / %d terminated \n", counter, N);
  }

  return EXIT_SUCCESS;


}
