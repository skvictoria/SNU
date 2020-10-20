#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define min(a,b) ((a)<(b)?(a):(b))

int main(int argc, char* argv[]){

  int n = min(argc>1? atoi(argv[1]):2, 16);
  pid_t pid = 0;

  for(int i=0;i<n ; i++){
    if((pid=fork())==0) break;
  }

  printf("%s: pid:%d, pgid:%d\n", pid>0? "Parent":"Child", getpid(), getpgrp());

  while(1);

  return EXIT_SUCCESS;
}
