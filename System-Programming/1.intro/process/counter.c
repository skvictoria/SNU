#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter = 0;
int main(int argc, char* argv[]){

  pid_t pid = getpid();
  printf("Process %5d: counter is located "
      "at address %p\n", pid, &counter);

  while(1){
    printf("Process %5d: counter=%3d\n",
        pid, counter++);
    sleep(1);
  }
  return EXIT_SUCCESS;
}
